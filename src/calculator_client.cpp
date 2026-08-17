#include "ros/ros.h"
#include "beginner_tutorials/Calculator.h"
#include <cstdlib>

int main(int argc, char **argv){
    ros::init(argc, argv, "calculator_client");
    ROS_INFO("+: 43");
    ROS_INFO("-: 45");
    ROS_INFO("*: 42");
    ROS_INFO("/: 47");
    if (argc != 3){
        ROS_INFO("usage: calculator_client X Y Z");

        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<beginner_tutorials::Calculator>("add_two_ints");

    beginner_tutorials::Calculator srv;
    srv.request.a = atoll(argv[1]);
    srv.request.b = atoll(argv[2]);
    srv.request.operation = atoll(argv[3]);

    if (client.call(srv)){
        ROS_INFO("Result: %ld", (long int)srv.response.result);
    }
    else{
        ROS_ERROR("Failed to call service calculator");
        return 1;
    }
    return 0;
}