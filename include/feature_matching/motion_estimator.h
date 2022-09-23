#pragma once
#include "global.h"

namespace vo
{

struct MatchedPoints
{
int index;
int depth;
cv::Point point;
};


class MotionEstimator
{

vo::Base*  DataHub;                         // DataHub for data sharing

cv::Ptr<cv::Feature2D> FDetector;           // Feature Detector instance
cv::Ptr<cv::DescriptorMatcher> FMatcher;    // Feature Matcher instance

public:

// Datas
std::map<int,cv::Point*> points_matched;    // Points matched between adjacent key frame
std::map<int,cv::Mat>    patches;           // Patches croped arround the feature points 
std::list<int>           list_matchedidx;   // List containing indeces of matched points


MotionEstimator(vo::Base* DataHub);
~MotionEstimator();

// Feature detection & matching
std::vector<cv::DMatch> MatchFeature(cv::Mat frame_curr,cv::Mat frame_prev, int slice_num); 

// Patch cropping
void CropPatches(cv::Mat frame_curr);

// Depth filter updating
void UpdateDepth();

void Run(); // Main loop

};


};