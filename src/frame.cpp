#include "feature_matching/frame.h"

using namespace vo;
using namespace cv;

Frame::Frame(vo::Base* DataHub) : DataHub(DataHub)
{
    this->timeinterval_frame = 1000*(1/this->DataHub->getRateFrame());
}
Frame::~Frame() {}


void Frame::FrameCallback(const sensor_msgs::ImageConstPtr& msg)
{

    try
    {
        Mat frame_raw = cv_bridge::toCvShare(msg, "bgr8")->image;

        if (this->DataHub->queue_frame.size()<2)
        {
            printf("Origin frame recieved\n");
            this->DataHub->queue_frame.push(frame_raw);
            imshow("frame", frame_raw);
            waitKey(1);
        }

        else if (this->DataHub->queue_frame.size() == 2)
        {
            this->DataHub->queue_frame.push(frame_raw);
            imshow("frame", frame_raw);
            waitKey(1);
            this->DataHub->queue_frame.pop();
        }

        usleep(this->timeinterval_frame);
    
    }


    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }

}


void Frame::Run()
{

    image_transport::ImageTransport it(*(this->DataHub->getNodeHandler()));
    image_transport::Subscriber sub = it.subscribe(this->DataHub->getTopicNameFrame(),\
                                                   1,\
                                                   boost::bind(&Frame::FrameCallback, this, _1));

    ros::spin();

}
