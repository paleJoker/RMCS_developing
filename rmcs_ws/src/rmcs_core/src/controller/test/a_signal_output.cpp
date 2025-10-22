#include <rclcpp/rclcpp.hpp>
#include <rmcs_executor/component.hpp>
#include <cmath>

namespace rmcs_core::controller::test{
class SignalOutput :public rmcs_executor::Component,public rclcpp::Node
{   
    public:
    SignalOutput():Node(get_component_name(),
        rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true))
        {
            register_output("sin",sin_);
            register_output("cos", cos_);


        }
    void update() override
    {
        double w = get_parameter("w").as_double();
        rclcpp::Time time = this->get_clock()->now();
        double t = time.seconds();
        *sin_ = sin(w * t);
        *cos_ = cos(w * t);
    }
    private:
        OutputInterface<double> sin_;
        OutputInterface<double> cos_;

};
}

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rmcs_core::controller::test::SignalOutput, rmcs_executor::Component)