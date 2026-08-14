#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("I heard [%s]", msg->data.c_str());
}

int main(int argc, char **argv){
    ros::init(argc, argv, "listener");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

    // Eneters a loop, calling message callbacks as fast as possible. ros::spin()
    // will exit once ros::ok() returns false, which means ros::shutdown() has been 
    // called: Ctrl + C, master shutting it down, or it being called manually
    ros::spin();
    return 0;
}