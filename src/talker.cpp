#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv){
    ros::init(argc, argv, "talker"); //talker is the name of the node

    ros::NodeHandle n;

    // Queue size stands for size of the queue used for publishing msgs,
    // if messages are published more quickly than we can send them, it 
    // specifies how many messages to buffer before throwing them away.
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    
    //loop rate allows us to specify a frequency to loop at.
    // it will keep track of how long it has been since the last call to 
    // Rate::sleep() and sleep for the corrct amount of time
    ros::Rate loop_rate(10);

    int count = 0;
    /*
    ros::ok() will return false if:
    1. Ctrl+C received
    2. kicked off by another node with the same name
    3. ros::shutdown called by another part of the application
    4. all ros::NodeHandles has been destroyed
    */
    while (ros::ok()){

        std_msgs::String msg;
        std::stringstream ss;
        ss << "hello world" << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());

        chatter_pub.publish(msg);
        
        // Actually not necessary here because there is no callback
        // but if there is a subscription to this application, and do not have a 
        // spinOnce(), the callbacks woule never get called.
        ros::spinOnce();

        // corresponding to ros::Rate loop_rate(10)
        loop_rate.sleep();
        ++count;
    }
    return 0;
}