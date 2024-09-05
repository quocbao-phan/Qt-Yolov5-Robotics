#include "camera.h"

rs2::colorizer colorMap;

Camera::Camera()
{
    fps = 30;
    width = 640; height = 480;
    try
    {
        //Read matrix
        std::string serial;

        !device_with_streams({RS2_STREAM_COLOR}, serial);
        if (!serial.empty())
            cfg.enable_device(serial);
        cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_BGR8, 30);

        auto profile = pipe.start(cfg);
        intr = profile.get_stream(RS2_STREAM_COLOR).as<rs2::video_stream_profile>().get_intrinsics();
        pipe.stop();
        cfg.disable_all_streams();

        cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
        cameraMatrix.at<double>(0,0) = intr.fx;
        cameraMatrix.at<double>(0,2) = intr.ppx;
        cameraMatrix.at<double>(1,1) = intr.fy;
        cameraMatrix.at<double>(1,2) = intr.ppy;

        distCoeffs.resize(5,0);
        for(int i = 0; i < 5; i++)
            distCoeffs.at(i) = intr.coeffs[i];

        // pipe.start(cfg);
        // read matrix done
        cfg.enable_stream(RS2_STREAM_DEPTH, width, height, RS2_FORMAT_Z16, fps);
        cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_RGB8, fps);
    }
    catch(const rs2::error & e){
        std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
        //qDebug()<<e.what();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}
cv::Mat convertQImagetoMat(QImage img)
{
    img = img.convertToFormat(QImage::Format_RGB888, Qt::ColorOnly).rgbSwapped();
    return cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine()).clone();
}

void Camera::run()
{
    while(true)
    {
        if(isCameraruning)
        {
            data = pipe.wait_for_frames();
            frameDepth = data.get_depth_frame().apply_filter(colorMap);
            frameRgb = data.get_color_frame();
            depthImage = realsenseFrameToQImage(frameDepth);
            rgbImage = realsenseFrameToQImage(frameRgb);
            //cv::imshow("da",convertQImagetoMat(rgbImage));
            emit sendImage(rgbImage, depthImage);
            if(yoloCmd)
            {
                emit sendFrametoYolo(rgbImage);
            }
        }
    }
}

void Camera::stop()
{
    isCameraruning = false;
    pipe.stop();
    qDebug()<<"Da dung";
}

void Camera::receiveCmdYolo(bool cmd)
{
    yoloCmd = cmd ;
}
QImage Camera::realsenseFrameToQImage(rs2::frame frames)
{
    auto vf = frames.as<rs2::video_frame>();
    const int w = vf.get_width();
    const int h = vf.get_height();
    if (frames.get_profile().format() == RS2_FORMAT_RGB8)
    {
        auto r = QImage((uchar*) frames.get_data(), w, h, w*3, QImage::Format_RGB888);
        return r;
    }
    else if (frames.get_profile().format() == RS2_FORMAT_Z16)
    {
        auto r = QImage((uchar*) frames.get_data(), w, h, w*2, QImage::Format_RGB888);
        return r;
    }
    throw std::runtime_error("Frame format is not supported yet!");
}

bool Camera::device_with_streams(std::vector<rs2_stream> stream_requests, std::string &out_serial)
{
    rs2::context ctx;
    auto devs = ctx.query_devices();
    std::vector <rs2_stream> unavailable_streams = stream_requests;
    for (auto dev : devs)
    {
        std::map<rs2_stream, bool> found_streams;
        for (auto& type : stream_requests)
        {
            found_streams[type] = false;
            for (auto& sensor : dev.query_sensors())
            {
                for (auto& profile : sensor.get_stream_profiles())
                {
                    if (profile.stream_type() == type)
                    {
                        found_streams[type] = true;
                        unavailable_streams.erase(std::remove(unavailable_streams.begin(), unavailable_streams.end(), type), unavailable_streams.end());
                        if (dev.supports(RS2_CAMERA_INFO_SERIAL_NUMBER))
                            out_serial = dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER);
                    }
                }
            }
        }
        // Check if all streams are found in current device
        bool found_all_streams = true;
        for (auto& stream : found_streams)
        {
            if (!stream.second)
            {
                found_all_streams = false;
                break;
            }
        }
        if (found_all_streams)
            return true;
    }
    // After scanning all devices, not all requested streams were found
    for (auto& type : unavailable_streams)
    {
        switch (type)
        {
        case RS2_STREAM_POSE:
        case RS2_STREAM_FISHEYE:
            std::cerr << "Connect T26X and rerun the demo" << std::endl;
            break;
        case RS2_STREAM_DEPTH:
            std::cerr << "The demo requires Realsense camera with DEPTH sensor" << std::endl;
            break;
        case RS2_STREAM_COLOR:
            std::cerr << "The demo requires Realsense camera with RGB sensor" << std::endl;
            break;
        default:
            throw std::runtime_error("The requested stream: " + std::to_string(type) + ", for the demo is not supported by connected devices!"); // stream type
        }
    }
    return false;
}

void Camera::resolutionChanged(int w, int h){

    width = w;
    height = h;
    cfg.disable_all_streams();
    cfg.enable_stream(RS2_STREAM_DEPTH, width, height, RS2_FORMAT_Z16, fps);
    cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_RGB8, fps);
}
void Camera::fpsChanged(int f)
{
    fps = f;
    cfg.disable_all_streams();
    cfg.enable_stream(RS2_STREAM_DEPTH, width, height, RS2_FORMAT_Z16, fps);
    cfg.enable_stream(RS2_STREAM_COLOR, width, height, RS2_FORMAT_RGB8, fps);
}

void Camera::cmd()
{
    pipe.start(cfg);
    isCameraruning = true;
}

void Camera::getDistance(double u, double v)
{
    rs2::align align(RS2_STREAM_COLOR);
    auto aligned_frames = align.process(data);
    rs2::video_frame color_frame = aligned_frames.first(RS2_STREAM_COLOR);
    rs2::depth_frame aligned_depth_frame = aligned_frames.get_depth_frame();
    float distance;
    int count = 0;
    distance = aligned_depth_frame.get_distance(u, v);

    while(distance == 0)
    {
        distance = aligned_depth_frame.get_distance(u, v);
        count ++;
        if(count > 50000)
            break;
    }
    emit sendDistance(distance);
    //std::cout << "(" << u << "," << v << ") = " << distance << "; " << std::endl;
}

