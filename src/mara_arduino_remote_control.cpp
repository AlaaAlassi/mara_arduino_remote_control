#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "hrim_actuator_rotaryservo_msgs/msg/goal_rotary_servo.hpp"
#include "sensor_msgs/msg/range.hpp"
#include "math.h"

class mara_arduino_remote_control : public rclcpp::Node
{
public:
  mara_arduino_remote_control():Node("mara_arduino_remote_control")
  {
    //labda experssion that defines our callback 
    auto teleopCallback = [this](sensor_msgs::msg::Range::UniquePtr msg) {

      // pass the range reading from ultrasonic sensor as a
      // commnded position in the joint_cmd_msg
      this->joint_cmd_msg.position = msg->range* M_PI/180.0;

      // limit the commanded angle to avoid hitting the table
      double Joint_limit = M_PI/2;

      if(this->joint_cmd_msg.position > Joint_limit )
      {
        this->joint_cmd_msg.position = Joint_limit;
      }

      if(this->joint_cmd_msg.position < -Joint_limit )
      {
        this->joint_cmd_msg.position = -Joint_limit;
      }

       // Determin joint vilocity 
       this->joint_cmd_msg.velocity = 0.9;

       // Determin control type (position control in our case)
       this->joint_cmd_msg.control_type = 1;

      // Publish the joint_cmd_msg message
      this->joint_publisher_->publish(joint_cmd_msg);

      // Print range readings 
      RCLCPP_INFO(this->get_logger(), "Range: %.5f", msg->range);
    };

    //subscribe to /arduino_ranger topic and bind with teleopCallback
    subscription_ = this->create_subscription<sensor_msgs::msg::Range>("/arduino_ranger",teleopCallback);

    // define a publisher that publishes joint_cmd_msg on 
    //Tpic : "/hros_actuation_servomotor_000000000001/goal"
    // with quality of service profile: rmw_qos_profile_sensor_data
    joint_publisher_ = this->create_publisher<hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>("/hros_actuation_servomotor_000000000001/goal", rmw_qos_profile_sensor_data);
    
  }

// definition of private mebers 
private:

  // definition of the subscriber
  rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr subscription_;

  // definition of the publisher
  rclcpp::Publisher <hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo>::SharedPtr joint_publisher_;

  // definition of the joint_cmd_msg 
  hrim_actuator_rotaryservo_msgs::msg::GoalRotaryServo joint_cmd_msg;
  
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<mara_arduino_remote_control>());
  rclcpp::shutdown();
  return 0;
}
