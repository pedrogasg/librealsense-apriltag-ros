#include <undistort/undistort.hpp>

namespace undistort
{

    Undistort::Undistort()
    {
    }

    bool Undistort::init(ros::NodeHandle& nh)
    {
        int QUEUE_SIZE = 1;
        image_transport::ImageTransport it(nh);
        iPub = it.advertise("undistort/image1", QUEUE_SIZE);
        iSub = it.subscribe("/camera/fisheye1/image_raw", QUEUE_SIZE, &Undistort::imageCallback, this);
        return true;
    }

    void Undistort::imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
        iPub.publish(msg);
    }
}