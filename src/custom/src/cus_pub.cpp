#include "cus_msg/msg/custom_msg.hpp"
#include <chrono>
#include <functional>
#include <rclcpp/rclcpp.hpp>

class ExamMsgPublisher : public rclcpp::Node {
  public:
    ExamMsgPublisher() : Node("exam_msg_publisher") {
        publisher_ =
            this->create_publisher<cus_msg::msg::CustomMsg>("exam_topic", 10);
        timer_ = create_wall_timer(std::chrono::seconds(1),
                                   [this]() { publish_message(); });
    }

  private:
    void publish_message() {
        auto message = std::make_shared<cus_msg::msg::CustomMsg>();
        message->set__v(1);
        message->set__rad(1);
        publisher_->publish(*message);
        RCLCPP_INFO(this->get_logger(), "Publishing: v=%d,rad = %f", message->v,
                    message->rad);
    }
    rclcpp::Publisher<cus_msg::msg::CustomMsg>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ExamMsgPublisher>());
    rclcpp::shutdown();
    return 0;
}
