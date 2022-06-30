# Home Service Robot
This is a final project of a robotics software engineer nanodegree program from Udacity. The purpose of this project is to create a robot that can autonomously map an environment, localize itself and receive commands & navigate to that location to do some tasks.

<hr>

## 1. Installations
1. Update and upgrade.
```
$ sudo apt-get update && apt-get upgrade
```
2. Install Xterm
```
$ sudo apt-get install xterm
```
3. Go to home
```
$ cd ~
```
4. Create directory catkin_ws/src
```
$ mkdir -p catkin_ws/src
```
5. Change directory to ~/catkin_ws/src
```
$ cd catkin_ws/src
```
6. Inin catkin workspace
```
$ catkin_init_workspace
```
7. Change directory to home
```
$ cd ../
```
8. Build package
```
$ catkin_make
```

<hr>

## 2. Packages
### 2.1 External Packages
2.1.1 [Turtlebot](https://github.com/turtlebot/turtlebot)
```
$ git clone -b kinetic https://github.com/turtlebot/turtlebot.git
```

2.1.2 [Slam_gmapping](https://github.com/ros-perception/slam_gmapping)
```
$ git clone https://github.com/ros-perception/slam_gmapping.git
```

2.1.3 [Turtlebot interactions](https://github.com/turtlebot/turtlebot_interactions)
```
$ git clone https://github.com/turtlebot/turtlebot_interactions.git
```

2.1.4 [Turtlebot simulator](https://github.com/turtlebot/turtlebot_simulator)
```
$ git clone https://github.com/turtlebot/turtlebot_simulator.git
```
### 2.2 My Packages
<br>

2.2.1 pick_objects: this package sends the pick-up location and the drop-off location to the robot.     

<br>

2.2.2 add_markers: this package creates markers in the map. If the robot reaches the pick-up location, the marker will disappear and the robot will be paused for 5 seconds. After that, the robot will deliver the marker to the drop-off location, The marker will appear again.

<hr>

## 3. Scripts You can run 
1. Go to catkins workspace.
```
$ cd catkin_ws
```
2. Launch script: Test that gazebo and rviz can run properly.
```
$ ./src/scripts/launch.sh
```
3. Test slam: Test that the robot can do SLAM.
```
$ ./src/scripts/test_slam.sh
```
4. Test navigation: Test that the robot can localization and navigate itself.
```
$ ./src/scripts/test_navigation.sh
```
5. Pick objects script: This script will command the robot to drive to the pick-up and drop-off zones.
```
$ ./src/scripts/pick_objects.sh
```
6. Add markers script: Add markers in the map: Needed two locations 1. pickup location and 2. drop off
```
$ ./src/scripts/add_marker.sh
```
7. Home service script: This script commands a full home service robot to navigate to pick up and deliver the markers.
```
$ ./src/scripts/home_service.sh
```
