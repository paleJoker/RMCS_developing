#include <rclcpp/rclcpp.hpp>
#include <rmcs_executor/component.hpp>

namespace rmcs_core::controller::test{
class SignalInput :public rmcs_executor::Component,public rclcpp::Node
{   
    public:
    SignalInput():Node(get_component_name(),
        rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true))
        {
            register_input("sin",sin_add_);
            register_input("cos",cos_add_);
            register_output("add", add_);

        }
    void update() override
    {   
        *add_ =*sin_add_ + *cos_add_;
        RCLCPP_INFO(get_logger(),"add=%lf",*add_);
    }
    private:
        InputInterface<double> sin_add_;
        InputInterface<double> cos_add_;
        OutputInterface<double> add_;

};
}
#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rmcs_core::controller::test::SignalInput, rmcs_executor::Component)