#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

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
int              num_keyframe;

cv::Mat          cammtx; 
cv::Mat          dst_coeff;

bool             FLAG_iskeyframe;
bool             FLAG_isframerecieved;


public:


Base(   const char* nodename_main,  \
        const char* topicname_frame,\
        const char* topicname_imu,  \
        int         rate_frame,     \
        int         rate_imu,       \
        int         queuesize_frame,\
        int         num_keyframe,   \
        cv::Mat     cammtx,         \
        cv::Mat     dst_coeff,      \
        ros::NodeHandle* node_main
    ) : \
        nodename_main       (nodename_main),     \
        topicname_frame     (topicname_frame),   \
        topicname_imu       (topicname_imu),     \
        rate_frame          (rate_frame),        \
        rate_imu            (rate_imu),          \
        queuesize_frame     (queuesize_frame),   \
        num_keyframe        (num_keyframe),      \
        cammtx              (cammtx),            \
        dst_coeff           (dst_coeff),         \
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
int getQueueSizeFrame()           {return this->queuesize_frame;}
int getNumberKeyFrame()           {return this->num_keyframe;}
cv::Mat getCamMatrix()            {return this->cammtx;}
cv::Mat getDistCoeff()            {return this->dst_coeff;}


bool getIsKeyFrame()              {return this->FLAG_iskeyframe;}
bool getIsFrameRecieved()         {return this->FLAG_isframerecieved;}
void setIsKeyFrame(bool on)       {this->FLAG_iskeyframe = on;}
void setIsFrameRecieved(bool on)  {this->FLAG_isframerecieved = on;}

ros::NodeHandle* getNodeHandler() {return this->node_main;}


};


};
