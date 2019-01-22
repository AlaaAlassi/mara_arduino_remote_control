cmake_minimum_required(VERSION 3.5)
project(mara_arduino_remote_control)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(hrim_actuator_rotaryservo_msgs REQUIRED)

add_executable(mara_arduino_remote_control src/mara_arduino_remote_control.cpp)
ament_target_dependencies(mara_arduino_remote_control sensor_msgs rclcpp hrim_actuator_rotaryservo_msgs)

install(TARGETS
  mara_arduino_remote_control
  DESTINATION lib/${PROJECT_NAME}
)

#install(
#  PROGRAMS
#  scripts/mara_minimal_subscriber.py
#  DESTINATION lib/${PROJECT_NAME})

ament_package()
