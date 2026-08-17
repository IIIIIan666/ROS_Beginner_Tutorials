#include "ros/ros.h"
#include "beginner_tutorials/Calculator.h"

bool operate(beginner_tutorials::Calculator::Request &req,
beginner_tutorials::Calculator::Response &res){

    switch(req.operation){
        case '+':
            res.result = req.a + req.b;
            res.success = true;
            break;
        case '-':
            res.result = req.a - req.b;
            res.success = true;
            break;
        case '*':
            res.result = req.a * req.b;
            res.success = true;
            break;
        case '/':
            if (req.b == 0){
                res.success = false;
                ROS_WARN("Division by zero error");
                break;
            }
            res.result = req.a / req.b;
            res.success = true;
            break;
        default:
            res.success = false;
            ROS_WARN("Unknown operation!");
            break;
    }
    

    ROS_INFO("request: x=%ld, y=%ld, z=%c", (long int)req.a, (long int)req.b, (char)req.operation);
    ROS_INFO("sending back response: x=%ld, y=%d", (long int)res.result, (bool)res.success);
    return true;
}

int main(int argc, char **argv){
    ros::init(argc, argv, "calculator_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("calculator", operate);
    ROS_INFO("Ready to operate.");
    ros::spin();

    return 0;
}