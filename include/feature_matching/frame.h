#pragma once
#include "global.h"

namespace vo
{


class Frame
{

vo::Base*   DataHub;

double      timeinterval_frame;

public:

    Frame(vo::Base* DataHub);
    ~Frame();

    void FrameCallback(const sensor_msgs::ImageConstPtr &msg);

    void Run();

};


};