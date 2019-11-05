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
        iPub = it.advertise("camera/image", QUEUE_SIZE);
        iSub = it.subscribe("camera/image", QUEUE_SIZE, &Undistort::imageCallback);
        
    }

    void Undistort:imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
        iPub.publish(msg);
    }