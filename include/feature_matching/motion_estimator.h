#pragma once
#include "global.h"

namespace vo
{

struct ExtractedPoint
{
int index;
int depth;
cv::Point point;
};


struct Patch
{
vo::ExtractedPoint keypoint;
cv::Mat patch;
};


class MotionEstimator
{

vo::Base*  DataHub;                         // DataHub for data sharing

cv::Ptr<cv::Feature2D> FDetector;           // Feature Detector instance
cv::Ptr<cv::DescriptorMatcher> FMatcher;    // Feature Matcher instance

public:

// Datas
std::vector<cv::KeyPoint> keypoints_curr;   // keypoints extracted from k'th frame
std::vector<cv::KeyPoint> keypoints_prev;   // keypoints extracted from k-1'th frame
std::map<int,cv::Point*>  points_matched;   // Points matched between adjacent key frame
std::map<int,cv::Mat>     patches;          // Patches croped arround the feature points 
std::list<int>            list_matchedidx;  // List containing indeces of matched points
cv::Mat                   position;


ros::Publisher            pub_position;
sensor_msgs::PointCloud   msg_pointcloud;


MotionEstimator(vo::Base* DataHub);
~MotionEstimator();

// Feature detection & matching
std::vector<cv::DMatch> ExtractFeature(cv::Mat frame_curr); 

// Patch cropping
void CropPatches(cv::Mat frame_curr);

// Depth filter updating
void UpdateDepth();

void Run(); // Main loop


// Test Functions //
void testEpipolarGeometry(cv::Mat img_curr, cv::Mat img_prev);


};


};