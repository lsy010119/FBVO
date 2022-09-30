#include "feature_matching/motion_estimator.h"

using namespace vo;
using namespace cv;
using namespace ros;
using namespace std;


MotionEstimator::MotionEstimator(vo::Base* DataHub) : DataHub(DataHub) 
{

    this->FDetector = cv::ORB::create(500,1.2,8,31,0,2,cv::ORB::FAST_SCORE,31,20);
    this->FMatcher = cv::BFMatcher::create(NORM_HAMMING);

    this->position = (Mat_<double>(3,1) << 0,0,10);
    this->pub_position = (this->DataHub->getNodeHandler())->advertise<sensor_msgs::PointCloud>("position",1);
    this->msg_pointcloud.header.frame_id = "map";
    this->msg_pointcloud.header.stamp = ros::Time::now();

}
MotionEstimator::~MotionEstimator() {}



void MotionEstimator::testEpipolarGeometry(Mat img_curr, Mat img_prev)
{
    vector<KeyPoint> keypoints_prev,keypoints_curr;
    Mat disc_prev,disc_curr;
    this->FDetector->detectAndCompute(img_curr,Mat(),keypoints_curr,disc_curr);
    this->FDetector->detectAndCompute(img_prev,Mat(),keypoints_prev,disc_prev);

    vector<DMatch> matched;
    this->FMatcher->match(disc_curr,disc_prev,matched);

    sort(matched.begin(),matched.end());
    vector<DMatch> matched_filtered(matched.begin(), matched.begin()+300);

    vector<Point2f> points_prev(matched_filtered.size());
    vector<Point2f> points_curr(matched_filtered.size());


    map<int,Point*> matched_points_set;

    for (DMatch mp : matched_filtered)
    {

        Point matched_point_curr(   keypoints_curr[mp.queryIdx].pt.x,
                                    keypoints_curr[mp.queryIdx].pt.y);
        
        Point matched_point_prev(   keypoints_prev[mp.trainIdx].pt.x,
                                    keypoints_prev[mp.trainIdx].pt.y);
        
        Point matched_points_pair[] = { matched_point_curr,
                                        matched_point_prev};
        
        matched_points_set[mp.queryIdx] = matched_points_pair;

        Point pt(   cvRound(keypoints_curr[mp.queryIdx].pt.x),
                    cvRound(keypoints_curr[mp.queryIdx].pt.y));

        circle(img_curr, pt, 2, Scalar(0,255,0),1);
        line(img_curr, matched_point_curr, matched_point_prev, Scalar(0,0,255),1);

    }

    imshow("frame", img_curr);
    waitKey(1);

    // this->points_matched = matched_points_set;



    // for (int i = 0;i < matched_filtered.size();i++)
    // {
    //     DMatch mp = matched_filtered[i];

    //     Point2f matched_point_curr(   keypoints_curr[mp.queryIdx].pt.x,
    //                                 keypoints_curr[mp.queryIdx].pt.y);
        
    //     Point2f matched_point_prev(   keypoints_prev[mp.trainIdx].pt.x,
    //                                 keypoints_prev[mp.trainIdx].pt.y);
        
    //     points_curr[i] = matched_point_curr;
    //     points_prev[i] = matched_point_prev;
    // }

    // Mat E = findEssentialMat(points_curr,points_prev,this->DataHub->getCamMatrix(),FM_LMEDS);

    // Mat R1,R2,t;
    // decomposeEssentialMat(E,R1,R2,t);

    // this->position = this->position + t;    

    // cout << position.at<double>(0) << " " << position.at<double>(1) << " " << position.at<double>(2) << endl;

    // geometry_msgs::Point32 msg_point;

    // msg_point.x = this->position.at<double>(0);
    // msg_point.y = this->position.at<double>(1);
    // msg_point.z = this->position.at<double>(2);

    // msg_pointcloud.points.push_back(msg_point);

    // this->pub_position.publish(msg_pointcloud);
}




vector<DMatch> MotionEstimator::ExtractFeature(cv::Mat frame_curr)
{

    vector<KeyPoint> keypoints_curr;

    FAST(frame_curr,keypoints_curr,60);

    this->keypoints_curr = keypoints_curr;

}



void MotionEstimator::CropPatches(cv::Mat frame_curr)
{



}



void MotionEstimator::Run()
{




while (ros::ok())

{


    if (this->DataHub->getIsFrameRecieved()) 
    {

        Mat keyframe_prev = this->DataHub->queue_frame.front(); // load previous key frame
        Mat keyframe_curr = this->DataHub->queue_frame.back();  // load current key frame

        if (this->DataHub->getIsKeyFrame())
        {

            // Turn off FLAGs
            this->DataHub->setIsKeyFrame(false);
            this->DataHub->setIsFrameRecieved(false);


            //////////////////////////////////////////////////////
            /// Key frame : Point matching & Init Depth filter ///
            //////////////////////////////////////////////////////


            // Feature Extraction and Matching

            // Crop and save patches

            this->testEpipolarGeometry(keyframe_curr,keyframe_prev);


            // imshow("curr",keyframe_curr);
            // imshow("prev",keyframe_prev);
            // waitKey(1);


        } 

        else
        {
            // Turn off FLAGs
            this->DataHub->setIsFrameRecieved(false);

            //////////////////////////////////////////////////////
            ////////// Normal frame : Update Depth filter ////////
            //////////////////////////////////////////////////////

            // Direct VO

        }

        usleep(10);

    }

    else {usleep(10);}
}
    
}