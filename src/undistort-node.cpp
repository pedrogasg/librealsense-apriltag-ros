#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <distortion/undistort.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_undistortion");
  ros::NodeHandle nh;
  distortion::Undistort worker;
  if(!worker.init(nh))
  {
    ROS_ERROR("Could not initialize Undistort node!");
    return -1;
  }

}
