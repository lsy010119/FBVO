#include "feature_matching/motion_estimator.h"

using namespace vo;
using namespace cv;
using namespace std;

MotionEstimator::MotionEstimator(vo::Base* DataHub) : DataHub(DataHub) 
{

    this->FDetector = cv::ORB::create(1000,1.2,8,31,0,2,cv::ORB::FAST_SCORE,31,20);
    this->FMatcher = cv::BFMatcher::create(NORM_HAMMING);

}
MotionEstimator::~MotionEstimator() {}





    // map<int,Point*> matched_points_set;

    // for (DMatch mp : matched_slieced)
    // {

    //     Point matched_point_curr(   keypoints_curr[mp.queryIdx].pt.x,
    //                                 keypoints_curr[mp.queryIdx].pt.y);
        
    //     Point matched_point_prev(   keypoints_prev[mp.trainIdx].pt.x,
    //                                 keypoints_prev[mp.trainIdx].pt.y);
        
    //     Point matched_points_pair[] = { matched_point_curr,
    //                                     matched_point_prev};
        
    //     matched_points_set[mp.queryIdx] = matched_points_pair;

    //     Point pt(   cvRound(keypoints_curr[mp.queryIdx].pt.x),
    //                 cvRound(keypoints_curr[mp.queryIdx].pt.y));

    //     // circle(frame_curr, pt, 2, Scalar(0,255,0),1);
    //     // line(frame_curr, matched_point_curr, matched_point_prev, Scalar(0,0,255),1);

    // }

    // // imshow("frame", frame_curr);
    // // waitKey(1);

    // this->points_matched = matched_points_set;


vector<DMatch> MotionEstimator::MatchFeature(cv::Mat frame_curr, cv::Mat frame_prev, int slice_num)
{

    vector<KeyPoint> keypoints_curr,keypoints_prev;

    Mat desc_curr, desc_prev;

    this->FDetector->detectAndCompute(frame_curr, Mat(), keypoints_curr, desc_curr);
    this->FDetector->detectAndCompute(frame_prev, Mat(), keypoints_prev, desc_prev);

    vector<DMatch> matched;

    this->FMatcher->match(desc_curr, desc_prev, matched);

    // filtering well matched points ( points with low distance )
    sort(matched.begin(),matched.end());
    vector<DMatch> matched_slieced(matched.begin(),matched.begin()+slice_num);

    return matched_slieced;    

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

        
        if (this->DataHub->getIsKeyFrame())
        {
            // Turn off FLAGs
            this->DataHub->setIsKeyFrame(false);
            this->DataHub->setIsFrameRecieved(false);

            Mat keyframe_prev = this->DataHub->queue_frame.front(); // load previous key frame
            Mat keyframe_curr = this->DataHub->queue_frame.back();  // load current key frame


            //////////////////////////////////////////////////////
            /// Key frame : Point matching & Init Depth filter ///
            //////////////////////////////////////////////////////


            // Feature Extraction and Matching

            // Crop and save patches

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

        usleep(1000*1);

    }

    else {usleep(1000*1);}
}
    
}