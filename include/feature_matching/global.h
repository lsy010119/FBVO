#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <thread>
#include <unistd.h>
#include <stdio.h>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <opencv4/opencv2/opencv.hpp>


namespace vo 
{


class Base
{

ros::NodeHandle* node_main;

const char*      nodename_main;

const char*      topicname_frame;
const char*      topicname_imu;

int              rate_frame;
int              rate_imu;

int              queuesize_frame;



public:


Base(   const char* nodename_main,  \
        const char* topicname_frame,\
        const char* topicname_imu,  \
        int         rate_frame,     \
        int         rate_imu,       \
        int         queuesize_frame,\
        ros::NodeHandle* node_main
    ) : \
        nodename_main       (nodename_main),     \
        topicname_frame     (topicname_frame),   \
        topicname_imu       (topicname_imu),     \
        rate_frame          (rate_frame),        \
        rate_imu            (rate_imu),          \
        queuesize_frame     (queuesize_frame),   \
        node_main           (node_main)

{

printf("\nBase Initialized\n");

}
~Base() {}


std::queue<cv::Mat> queue_frame;
Eigen::Matrix2d imu_raw;


const char* getNodeName()         {return this->nodename_main;}
const char* getTopicNameFrame()   {return this->topicname_frame;}
const char* getTopicNameIMU()     {return this->topicname_imu;}
int getRateFrame()                {return this->rate_frame;}
int getRateIMU()                  {return this->rate_imu;}
int getQueueFrame()               {return this->rate_imu;}
int getQueueSizeFrame()           {return this->queuesize_frame;}
ros::NodeHandle* getNodeHandler() {return this->node_main;}


};


};
