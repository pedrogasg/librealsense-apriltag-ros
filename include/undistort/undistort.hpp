#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>


namespace undistort
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
            void infoCallback(const sensor_msgs::CameraInfo::ConstPtr& msg);
        
        private:
            image_transport::Subscriber imageSubscriber;
            image_transport::Publisher imagePublisher;
            ros::Subscriber cameraInfoSubscriber;
            cv::Size image_size;
            cv::Mat undist;
            cv::Mat D = cv::Mat(4, 1, CV_64F);
            cv::Mat K = cv::Mat(3, 3, CV_64F);
            cv::Mat R = cv::Mat(3, 3, CV_64F);
            cv::Mat P = cv::Mat(3, 4, CV_64F);
            cv::Mat mapx, mapy;
            cv_bridge::CvImagePtr cvBridgeImage;
            cv_bridge::CvImage imgBridge;
            bool infoAdquired = false;
    };
}