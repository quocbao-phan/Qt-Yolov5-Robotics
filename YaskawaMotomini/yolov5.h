#ifndef YOLOV5_H
#define YOLOV5_H

#include <QThread>
#include <QObject>
#include <QtCore>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QThread>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <fstream>


class Yolov5 : public QThread
{
    Q_OBJECT

public:
    void run();
    explicit Yolov5(QObject *parent = nullptr);

    void delay(int milliseconds);

    bool isYoloruning = false;
    bool cmdYolo;
    cv::dnn::Net net;
    cv::Mat frame, frameYolo;
    std::vector<std::string> class_name;
    void stop();
    void cmd();
    QImage convertMattoQImage(cv::Mat);
    cv::Mat convertQImagetoMat(QImage);
    QImage imageToMain;
    double timeToMain;
    void getDataPCA();
    cv::Mat post_process(cv::Mat& image, std::vector<cv::Mat>& outputs, const std::vector<std::string>& class_name, cv::Vec4d& params);
    int numberDetect = 0;
private:
    std::vector<cv::Mat> detections;
    cv::Vec4d params;
public slots:
    void receivedFrame(QImage);

    void receivedPCArequest(int flag);
signals:
    void sendFrame(QImage);
    void sendCmd(bool);
    void sendTimeProcess(double);
    void sendQImagePCA(QImage img, int ID);
};

#endif // YOLOV5_H
