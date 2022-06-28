#!/bin/sh
export TURTLEBOT_GAZEBO_WORLD_FILE="/home/robond/catkin_ws/src/my_robot/worlds/Ohmpyw.world"
xterm  -e  " source /home/robond/catkin_ws/devel/setup.bash; " &
sleep 1
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch; " & 
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch;  " &
sleep 5
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch; " & 
sleep 5
xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch" 
