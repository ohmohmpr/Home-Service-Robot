#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick_objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  float positions_x_w[2][2] = {
    { 4.0, 1.0 },
    { 0.0 ,1.0 }
  };

  int size = sizeof(positions_x_w) / sizeof(positions_x_w[0]);
  for (int i = 0; i < size; i++) {
      // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = positions_x_w[i][0];
    goal.target_pose.pose.orientation.w = positions_x_w[i][1];

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO_STREAM("Hooray, the base moved forward");
    else
      ROS_INFO_STREAM("The base failed to move for some reason");
    
    ros::Duration(5.0).sleep();
  }
  return 0;
}
