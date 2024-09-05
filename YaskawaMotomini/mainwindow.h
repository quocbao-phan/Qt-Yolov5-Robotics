#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "yrc1000micro_com.h"
#include <QTimer>
#include "servocontrol.h"
#include "updaterobotposition.h"
#include <librealsense2/rs.hpp>
#include <QDebug>
#include "camera.h"
#include "yolov5.h"
#include <armadillo>
#include <vector>
#include <cmath>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
#define ROBOT_MODE 1
#define CARTESIAN_MODE 2
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double maxSpeed = 250;
    Camera *camera;
    Yolov5 *yolov5;
    QTimer *timer;
    bool isCamStreaming;
    bool refillFlag = false;
    cv::Mat PCAimage;

    QImage PCAimage_main, PCAimage_1, PCAimage_2;
//    double u = 0 ,v = 0;
//    double u_offset = 0, v_offset = 0;
    cv::Point point_ctr, point_head, point_tail, point_ctr_vertical;
    double a_ctr_newp1;
    double b_ctr_newp1;

    bool top_L,top_R, left_T,left_B, bottom_L, bottom_R, right_T, right_B;
    //for 2D, get length and width of Bolt
    double x1, y1, x2, y2, x3, y3, x4, y4; //điểm đầu cuối và trái phải con ốc
    double lengthOfBold, widthOfBold;
    int typeID; //loại bu lông
    int classID, classID_1, classID_2;
    bool isBlueBox = false;
    bool isGreenBox = false;
    double distance_fromCam;
    double rotateAngle;
    QVector<double> targetPosition;

    QTimer *timerProcess, *timerGoHome;
    QTimer *timerFinish;
    QTimer *timerClock;

    int state = 0;
    bool isRunningProcess = false;
    int Speed_Picking = 80;

    std::clock_t time_start_process, time_end_process;
    double timeProcessPicking;

    //for convert 2D to 3D
    cv::Mat Tsai,Park,Horaud,Daniilidis,Andreff;
    cv::Mat target2cam = cv::Mat::eye(4,4,CV_64F);
    cv::Mat In;
    cv::Mat Ex;
    cv::Mat temp;
    cv::Mat Result;
    cv::Mat Matrix = cv::Mat::eye(4,4,CV_64F);
    double YawAngle, PitchAngle;
    arma::vec3 head3D, cntr3D, tail3D;

    int totalTime = 0;

    //color in OpenCV
    cv::Scalar GREEN = cv::Scalar(0, 255, 0);
    cv::Scalar RED =  cv::Scalar(0, 0, 255);
    cv::Scalar BLUE =  cv::Scalar(255, 0, 0);
    cv::Scalar VULCAN =  cv::Scalar(12, 21, 140);
    cv::Scalar PINK =  cv::Scalar(255, 0, 255);
    cv::Scalar PURPLE =  cv::Scalar(255, 51, 51);
    cv::Scalar CYAN =  cv::Scalar(255, 255, 0);
    cv::Scalar YELLOW =  cv::Scalar(0, 255, 255);
    cv::Scalar FOREST_GREEN =  cv::Scalar(0, 102, 51);
    cv::Scalar ORANGE =  cv::Scalar(0, 128, 255);

    cv::Scalar WHITE =  cv::Scalar(255, 255, 255);
    cv::Scalar BLACK =  cv::Scalar(0, 0, 0);
    cv::Scalar GRAY =  cv::Scalar(96, 96, 96);

    cv::Scalar PASTEL_RED =  cv::Scalar(204, 204, 255);
    cv::Scalar PASTEL_YELLOW =  cv::Scalar(204, 255, 255);
    cv::Scalar PASTEL_GREEN =  cv::Scalar(204, 255, 204);
    cv::Scalar PASTEL_BLUE =  cv::Scalar(255, 255, 204);
    cv::Scalar PASTEL_PURPLE =  cv::Scalar(255, 204, 204);
    cv::Scalar PASTEL_PINK =  cv::Scalar(229, 204, 255);
private:
    Ui::MainWindow *ui;
    QPalette pal_red = palette();
    QPalette pal_green = palette();
    YRC1000micro_com yrc100micro_com;
    servoControl *serial;
    updateRobotPosition *updatePosition;

public slots:
    void receiveImage(QImage, QImage);
    void checkCameraRunning();
    void receiveFrameYolo(QImage);
    void receiveFramePCA(QImage img, int ID);
    void receiveTimeProcess(double);

private slots:
    //      Serial //////////////
    void take_comboBoxData_forThread();
    void comboBoxAddItem(QString Name, QString Location);
    void btnConnectSetText(QString text);
    void on_btn_connect_clicked();
    void on_btn_servo_clicked();
    void on_btn_Home_clicked();
    void on_txt_homeSpeed_editingFinished();


    void takeIpTextForThread();
    void setGetLabelFromMain(QString x, QString y, QString z, QString roll, QString pitch, QString yaw);
    void setGetPulseLabelFromMain(QString s, QString l, QString u, QString r, QString b, QString t);

    void on_radioDepth_toggled(bool checked);
    void on_radioRGB_toggled(bool checked);
    void on_cbResolution_currentTextChanged(const QString &arg1);
    void on_btnStart_clicked();
    void on_cbFPS_currentTextChanged(const QString &arg1);
    void on_btnDetect_clicked();

    cv::Mat convertQImagetoMat(QImage img);
    QImage convertMattoQImage(cv::Mat mat);
    QPixmap cvMatToQPixmap(const cv::Mat &inMat);
    void drawAxis(cv::Mat& img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale = 0.2);
    double getOrientation(const std::vector<cv::Point> &pts, cv::Mat &img);
    cv::Mat PCA(cv::Mat img);

    void readResultTextFile(QString fileName, cv::Mat &Tsai, cv::Mat &Park, cv::Mat &Horaud, cv::Mat &Daniilidis, cv::Mat &Andreff);
    void recieveDistance(double dist);
    void moveToTarget(QVector<double> position);
    void moveDown1(int clsid);
    void moveDown2(int clsid, int typid);
    void moveToPlacePoint(int clssid, int typid);
    void moveUp();
    double getPitchAngel(std::vector<arma::vec3> points);
    arma::vec3 convert2Dto3D(cv::Point, int n);
    void PCAMoving(QImage img, int classid);
    void readStatus();
    void process();
    void FinishProcess();
    void on_btnStartProcess_clicked();
    void on_slider_Speed_Picking_valueChanged(int value);
    void on_btn_GetPitch_clicked();

    void TotalTimeClock();
signals:
    void sendResolution(int, int);
    void sendFps(int);
    void sendPCArequest(int flag);

    void connectClickToUpdateThread(bool flag);
    void textIpAnswer(QString ip, short port, short fileport);
    void comboBoxDataAnswer(QString serialName,QString serialLoc);
};

#endif // MAINWINDOW_H
