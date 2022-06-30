#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <iostream>
#include <cmath>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

float x_pos = INT_MAX, y_pos = INT_MAX;
ros::Publisher marker_pub;
visualization_msgs::Marker marker;
bool pick_up = false;
float start[2] = { 4.0, 0.0 };
float stop[2] = { 0.0, 0.0 };

bool is_in_the_area(float center_x, float center_y, float desti_x, float desti_y, float radius)
{
    float distance = INT_MAX;
    bool is_in_the_area = false;
    distance = std::sqrt(std::pow((center_x - desti_x), 2.0) + std::pow((center_y - desti_y), 2.0));
    if (distance <= radius)
    {
        is_in_the_area = true;
        return is_in_the_area;
    }
    return is_in_the_area;
}

void amcl_pose_call_back(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    x_pos = msg->pose.pose.position.x;
    y_pos = msg->pose.pose.position.y;
    bool is_in_the_area_pickup = is_in_the_area(start[0], start[1], x_pos, y_pos, 0.25);
    bool is_in_the_area_dropoff = is_in_the_area(stop[0], stop[1], x_pos, y_pos, 0.25);
    if ((!is_in_the_area_pickup) && (!pick_up))
    {
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
    }
    else if (is_in_the_area_pickup)
    {
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        ros::Duration(5.0).sleep();
        pick_up = true;
    }
    else if (is_in_the_area_dropoff && (pick_up == true))
    {
        marker.pose.position.x = stop[0];
        marker.pose.position.y = stop[1];
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
    }
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "add_markers_amcl_odom");
    ros::NodeHandle n;
    ros::Rate r(1);
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Subscriber amcl_pose_sub = n.subscribe("amcl_pose", 1, amcl_pose_call_back);

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers_amcl_odom";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header


    // Define a position and orientation for the robot to reach
    marker.pose.position.x = start[0];
    marker.pose.position.y = start[1];
    marker.pose.position.z = 0;
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
    ros::spin();

}
