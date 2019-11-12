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
        imagePublisher = it.advertise("undistort/image1", QUEUE_SIZE);
        imageSubscriber = it.subscribe("/camera/fisheye1/image_raw", QUEUE_SIZE, &Undistort::imageCallback, this);
        cameraInfoSubscriber = nh.subscribe("/camera/fisheye1/camera_info", QUEUE_SIZE, &Undistort::infoCallback, this);
        return true;
    }

    void Undistort::imageCallback(const sensor_msgs::ImageConstPtr& msg)
    {
        if(infoAdquired){
            try
            {
                cvBridgeImage = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_32FC1);
            }
            catch (cv_bridge::Exception& e)
            {
                ROS_ERROR("cv_bridge exception: %s", e.what());
                return;
            }
            cv::Mat output;
            cvBridgeImage->image.convertTo(output, CV_32F);
            //undist.create( cvBridgeImage->image.size(), cvBridgeImage->image.type() );
            undist.create( output.size(), output.type() );
            cv::remap(output, undist, mapx, mapy, cv::INTER_LINEAR);
            
            //cv::fisheye::undistortImage (cvBridgeImage->image, undist, K, D);

            //cv::line(undist, cv::Point(0, 0), cv::Point(100, msg->header.seq % 200), cv::Scalar(255));
            std_msgs::Header header;
            header.stamp = ros::Time::now();
            header.seq = msg->header.seq;
            imgBridge = cv_bridge::CvImage(header, msg->encoding, undist);
            imagePublisher.publish(imgBridge.toImageMsg());
            ROS_INFO_STREAM_ONCE("The image was encoded in :" << msg->encoding);

        }
    }

    void Undistort::infoCallback(const sensor_msgs::CameraInfo::ConstPtr& msg){
        image_size.height = msg->height;
        image_size.width = msg->width;
        std::vector<double> temp(5);
        memcpy(&temp[0],  msg->D.data(), msg->D.size()*sizeof(double));
        temp.resize(4);
        memcpy(D.data,  temp.data(), temp.size()*sizeof(double));
        memcpy(K.data,  msg->K.data(), msg->K.size()*sizeof(double));
        memcpy(R.data,  msg->R.data(), msg->R.size()*sizeof(double));
        memcpy(P.data,  msg->P.data(), msg->P.size()*sizeof(double));
        ROS_INFO_STREAM("Camera information adquired");
        cv::fisheye::initUndistortRectifyMap(K, D, cv::Mat(), K, image_size, CV_32F, mapx, mapy);
        //cv::fisheye::initUndistortRectifyMap(K, D, R, P, image_size, CV_32F, mapx, mapy);
        ROS_INFO_STREAM("Map X and Map Y where created");
        cameraInfoSubscriber.shutdown();
        infoAdquired = true;
    }
}