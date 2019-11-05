#ifndef DISTORTION_UNDISTORT_H
#define DISTORTION_UNDISTORT_H

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>


namespace distortion
{
    class Undistort
    {
        public:
            Undistort();
            ~Undistort() = default;

            bool init(ros::NodeHandle& nh);
            bool undistort();

        private:
            void imageCallback(const sensor_msgs::ImageConstPtr& msg);
        
        private:
            image_transport::ImageTransport it;
            image_transport::Subscriber iSub;
            image_transport::Publisher iPub;
    };
}
#endif