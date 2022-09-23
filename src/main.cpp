#include "feature_matching/frame.h"
#include "feature_matching/motion_estimator.h"

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

    const char* topicname_frame = "/camera_up/image_raw";
    // const char* topicname_frame = "/camera_down/image_raw";
    const char* topicname_imu = "/imu_raw";
    
    int rate_frame = 60;
    int rate_imu = 10;

    int queuesize_frame = 2;

    int num_keyframe = 1;

    cv::Mat cammtx = (cv::Mat_<double>(3,3) <<  347.344668, 0.00000000, 317.843671,
                	                0.00000000, 346.900900, 255.698665,
                	                0.00000000, 0.00000000, 1.00000000);

    cv::Mat dstcoeff = (cv::Mat_<double>(5,1) << -0.279997, 0.058631, 0.002795, -0.000103, 0.000000);


    ros::init(argc,argv,nodename_main);

    ros::NodeHandle node_main;

    vo::Base DataHub(   nodename_main,  \
                        topicname_frame,\
                        topicname_imu,  \
                        rate_frame,     \
                        rate_imu,       \
                        queuesize_frame,\
                        num_keyframe,   \  
                        cammtx,         \
                        dstcoeff,       \      
                        &node_main      );


    vo::Frame FU(&DataHub);
    vo::MotionEstimator FP(&DataHub);


    thread THREAD_updateFrame( [&FU] () {FU.SubscribeFrame();} );
    thread THREAD_estimateMotion( [&FP] () {FP.Run();} );
    thread THREAD_main( main_loop, &DataHub) ;

    THREAD_updateFrame.join();
    THREAD_estimateMotion.join();
    THREAD_main.join();

    return 0;
}