#include "cus_msg/msg/custom_msg.hpp"
#include <functional>
#include <geometry_msgs/msg/twist.hpp>
#include <rclcpp/rclcpp.hpp>

class Exam : public rclcpp::Node {
  public:
    Exam() : Node("exam") {
        subscription_ = this->create_subscription<cus_msg::msg::CustomMsg>(
            "exam_topic", 10,
            [this](const cus_msg::msg::CustomMsg::SharedPtr message) {
                topic_callback(message);
            });
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "turtle1/cmd_vel", 10);
    }

  private:
    void topic_callback(const cus_msg::msg::CustomMsg::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Received: v=%d , rad = %f", msg->v,
                    msg->rad);

        auto twist_msg = std::make_shared<geometry_msgs::msg::Twist>();

        twist_msg->linear.x = msg->v;
        twist_msg->angular.z = msg->rad;

        publisher_->publish(*twist_msg);
    }
    rclcpp::Subscription<cus_msg::msg::CustomMsg>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Exam>());
    rclcpp::shutdown();
    return 0;
}
