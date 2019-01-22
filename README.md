# mara_arduino_remote_control
A Ros2 package to control mara robotic arm remotely using an Arduino based ultrasonic sensor

## Installation 
Firs follow the step described in
[MARA-Repo](https://github.com/AcutronicRobotics/MARA).
 
 clone this repo 
 then, clone its dependancy into your mara ROS 2.0 workspace
 ```bash
cd ~/ros2_mara_ws/src
git clone https://github.com/AlaaAlassi/mara_arduino_remote_control.git
git clone https://github.com/ros2/common_interfaces.git
```
 
 ## Compile
 


```bash
source /opt/ros/crystal/setup.bash
source ~/ros2_mara_ws/install/setup.bash
cd ~/ros2_mara_ws && colcon build --merge-install  
```

