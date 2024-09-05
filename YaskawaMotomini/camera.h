#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <QThread>
#include <QObject>
#include <librealsense2/rs.hpp>
#include <QtCore>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QThread>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <fstream>

//using namespace std;

//using namespace cv;


class Camera : public QThread
{
    Q_OBJECT
protected:
    void run();
public:
    Camera();
    void stop();
    QImage rgbImage,depthImage;
    int width, height, fps;
    int X,Y;
    bool isCameraruning = false;
    void cmd();
    bool yoloCmd;
    cv::Mat frameYolo;

    cv::Mat cameraMatrix;

    std::vector<double> distCoeffs;
    void getDistance(double u, double v);
    bool isGetDistance = false;
public slots:
    void resolutionChanged(int, int);
    void fpsChanged(int);
    void receiveCmdYolo(bool);
private:
    rs2::config cfg;
    rs2::pipeline pipe;
    rs2::frameset data;
    rs2::frame frameRgb;
    rs2::frame frameDepth;

    QImage realsenseFrameToQImage(rs2::frame);
    bool device_with_streams(std::vector <rs2_stream> stream_requests, std::string& out_serial);

    rs2_intrinsics intr;

signals:
    void sendImage(QImage, QImage);
    void sendFrametoYolo(QImage);
    void sendDistance(double dist);



};

//Mat FrametoYolo(frame);
#endif // CAMERA_H
