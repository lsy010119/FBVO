#include "feature_matching/frame.h"
using std::thread;


void main_loop(vo::Base* DataHub)
{

while (ros::ok())
{
    usleep(5000*1000);

    printf("main thread running...\n");

}

}



int main(int argc, char** argv) 
{
    const char* nodename_main = "vo_main";

    const char* topicname_frame = "/camera_down/image_raw";
    const char* topicname_imu = "/imu_raw";
    
    int rate_frame = 10;
    int rate_imu = 10;

    int queuesize_frame = 2;

    ros::init(argc,argv,nodename_main);

    ros::NodeHandle node_main;


    vo::Base DataHub(   nodename_main,  \
                        topicname_frame,\
                        topicname_imu,  \
                        rate_frame,     \
                        rate_imu,       \
                        queuesize_frame,\
                        &node_main      );


    vo::Frame FrameUpdater(&DataHub);


    thread thread_frame( [&FrameUpdater] () {FrameUpdater.Run();} );
    thread thread_main( main_loop, &DataHub) ;

    thread_frame.join();
    thread_main.join();


return 0;
}