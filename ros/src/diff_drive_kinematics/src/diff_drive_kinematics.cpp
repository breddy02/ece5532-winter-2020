#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <ros/ros.h>

ros::Publisher left_wheel_pub;
ros::Publisher right_wheel_pub;
const double WHEEL_DISTANCE = 1;
const double WHEEL_RADIUS = 0.2;



void recvTwist(const geometry_msgs::TwistConstPtr &msg){
    double v = msg->linear.x;
    double psi_dot = msg->angular.z;
    
    std_msgs::Float64 left_wheel_speed;
    std_msgs::Float64 right_wheel_speed;
    
    left_wheel_speed.data = (1/WHEEL_RADIUS)*(v - WHEEL_DISTANCE*psi_dot/2);
    right_wheel_speed.data = (1/WHEEL_RADIUS)*(v + WHEEL_DISTANCE*psi_dot/2);
    
    left_wheel_pub.publish(left_wheel_speed);
    right_wheel_pub.publish(right_wheel_speed);
    
}

int main(int argc, char** argv){
    ros::init(argc,argv,"diff_drive_node");
    ros::NodeHandle nh;
    
    ros::Subscriber sub_twist = nh.subscribe("cmd_vel", 1, recvTwist);
    left_wheel_pub = nh.advertise<std_msgs::Float64>("/roundbot/left_speed_cmd",1);
    right_wheel_pub = nh.advertise<std_msgs::Float64>("/roundbot/right_speed_cmd",1);
    
    ros::spin();
}
