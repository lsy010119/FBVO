cmake_minimum_required(VERSION 3.0.2)
project(feature_matching)

set(OpenCV_INCLUDE_DIRS /usr/local/include/opencv4)
set(EIGEN3_INCLUDE_DIRS /usr/include/eigen3)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS thread system)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  cv_bridge
  image_transport
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES feature_matching
 CATKIN_DEPENDS roscpp rospy std_msgs
 DEPENDS EIGEN3 OpenCV Boost
)


# include dirs
include_directories(
  include 
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)


# Set link libraries
list(APPEND LINK_LIBS 
  ${OpenCV_LIBS}
  ${EIGEN3_LIBS}
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)


# Set sourcefiles
list(APPEND SOURCEFILES
  src/frame.cpp
)


# Create library
add_library(${PROJECT_NAME} SHARED ${SOURCEFILES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})


### test nodes ###
add_executable(runtest src/main.cpp)
target_link_libraries(runtest ${PROJECT_NAME})


