#include <distortion/undistort.hpp>

namespace distortion
{

    Undistort::Undistort()
    {
    }

    bool Undistort::init(ros::NodeHandle& nh)
    {
        int QUEUE_SIZE = 1
        it(nh);
        iPub = it.advertise("undistort/image1", QUEUE_SIZE);
        iSub = it.subscribe("/camera/fisheye1/image_raw", QUEUE_SIZE, &Undistort::imageCallback);
        return 0;
    }

    void Undistort:imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
        iPub.publish(msg);
    }