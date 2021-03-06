#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;
    ros::Time start_time = ros::Time::now();

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    // marker.action = visualization_msgs::Marker::ADD;
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    float pose_positions[2][3] = {
        { 4.0, 0.0, 0.0 },
        { 0.0, 0.0, 0.0 },
    };
    int size = sizeof(pose_positions) / sizeof(pose_positions[0]);

    // Define a position and orientation for the robot to reach
    marker.pose.position.x = pose_positions[0][0];
    marker.pose.position.y = pose_positions[0][1];
    marker.pose.position.z = pose_positions[0][2];
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
        if (!ros::ok())
        {
            return 0;
        }
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
    }

    marker_pub.publish(marker);
    ROS_INFO("SHOW Goal1");
    ros::Duration(5.0).sleep();

    // Delete obj1
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ros::Duration(5.0).sleep();
    ROS_INFO("HIDE Goal1");

    // Define a position and orientation for the robot to reach
    marker.pose.position.x = pose_positions[1][0];
    marker.pose.position.y = pose_positions[1][1];
    marker.pose.position.z = pose_positions[1][2];
    // Add another 
    marker.action = visualization_msgs::Marker::ADD;
    marker_pub.publish(marker);
    ROS_INFO("SHOW Goal2");
    ros::Duration(0.5).sleep();

    r.sleep();
}
