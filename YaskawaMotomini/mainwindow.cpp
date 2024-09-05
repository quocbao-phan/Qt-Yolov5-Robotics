#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QString>
#include <iostream>

using namespace std;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("image/logo/icon.png"));
    ui->lbLogoHCMUT_2->setPixmap(QPixmap("image/logo/bk_name_vi.png").scaled(550, 80, Qt::KeepAspectRatio));
    ui->lbLogoDepartment->setPixmap(QPixmap("image/logo/logo@3x.png"));

    ui->slider_Speed_Picking->setSliderPosition(3);

    ui->btn_connect->setAutoFillBackground(true);
    ui->btn_servo->setAutoFillBackground(true);
    ui->btn_ConnectServo->setAutoFillBackground(true);
    ui->btnStart->setAutoFillBackground(true);
    ui->btnDetect->setAutoFillBackground(true);
    ui->btnStartProcess->setAutoFillBackground(true);


    pal_green.setColor(QPalette::Button,QColor(Qt::green));
    pal_red.setColor(QPalette::Button,QColor(Qt::red));
    // Update Gui
    {
        updatePosition = NULL;
        updatePosition = new updateRobotPosition;
        updatePosition->start();
        connect(&yrc100micro_com, SIGNAL(dataUIRecieveSiUIgnal()),updatePosition, SLOT(updateUICallback()));

        //connect(&yrc100micro_com,SIGNAL(readRobotVari()),this,SLOT(setTextVariRead()));
        connect(this,SIGNAL(connectClickToUpdateThread(bool)),updatePosition,SLOT(ConnectClickTimerStart(bool)));
        connect(updatePosition,SIGNAL(askForTextIp()),this,SLOT(takeIpTextForThread()));
        connect(this,SIGNAL(textIpAnswer(QString,short,short)),updatePosition,SLOT(textIpReceive(QString,short,short)));
        connect(updatePosition,SIGNAL(setGetLabel(QString,QString,QString,QString,QString,QString)),
                this,SLOT(setGetLabelFromMain(QString,QString,QString,QString,QString,QString)));
        connect(updatePosition,SIGNAL(setGetPulseLabel(QString,QString,QString,QString,QString,QString)),
                this,SLOT(setGetPulseLabelFromMain(QString,QString,QString,QString,QString,QString)));
        connect(updatePosition,SIGNAL(setLabelRun(QString)),ui->lb_run_status,SLOT(setText(QString)));
        //Set text


        //
    }

    //Serial
    {
        serial = NULL;
        serial = new servoControl;
        serial->start();
        serial->mSerialScanTimer.start(5000);
        connect(ui->btn_ConnectServo,SIGNAL(clicked(bool)),serial,SLOT(on_btn_ConnectServo_clicked()));
        connect(ui->slider_Servo,SIGNAL(valueChanged(int)),serial,SLOT(getSliderValue(int)));
        connect(serial,SIGNAL(comboBoxDataRequest()),this,SLOT(take_comboBoxData_forThread()));
        connect(this,SIGNAL(comboBoxDataAnswer(QString,QString)),serial,SLOT(receiveComboBoxData(QString,QString)));
        connect(serial,SIGNAL(comboBoxClear()),ui->comboBox_COM,SLOT(clear()));
        connect(serial,SIGNAL(comboBoxAddItem(QString,QString)),this,SLOT(comboBoxAddItem(QString,QString)));
        connect(serial,SIGNAL(statusServoText(QString)),ui->lb_StatusServo,SLOT(setText(QString)));
        connect(serial,SIGNAL(btnServoText(QString)),this,SLOT(btnConnectSetText(QString)));
        connect(serial,SIGNAL(btnConnectEnable(bool)),ui->btn_ConnectServo,SLOT(setEnabled(bool)));
        connect(serial,SIGNAL(sliderEnable(bool)),ui->slider_Servo,SLOT(setEnabled(bool)));
    }
    //Thêm sau ****************************************************
    ui->displayDepth->hide();
    ui->displayRGB->setStyleSheet("background:grey");
    ui->displayYoloDectect->setStyleSheet("background:grey");

    camera = new Camera();
    connect(camera, SIGNAL(sendImage(QImage,QImage)), this, SLOT(receiveImage(QImage,QImage)));
    camera->start();

    yolov5 = new Yolov5();
    connect(yolov5, SIGNAL(sendFrame(QImage)), this, SLOT(receiveFrameYolo(QImage)));
    connect(yolov5, SIGNAL(sendTimeProcess(double)), this, SLOT(receiveTimeProcess(double)));
    connect(yolov5, SIGNAL(sendCmd(bool)), camera, SLOT(receiveCmdYolo(bool)));
    connect(yolov5, SIGNAL(sendQImagePCA(QImage,int)), this, SLOT(receiveFramePCA(QImage,int)));
    connect(camera, SIGNAL(sendFrametoYolo(QImage)), yolov5, SLOT(receivedFrame(QImage)));
    connect(this,SIGNAL(sendPCArequest(int)),yolov5,SLOT(receivedPCArequest(int)));
    yolov5->start(QThread::HighestPriority);

    ui->cbResolution->addItem("640x480");
    ui->cbResolution->addItem("640x360");
    ui->cbResolution->addItem("424x240");
    connect(this, SIGNAL(sendResolution(int,int)), camera, SLOT(resolutionChanged(int,int)));


    ui->cbFPS->addItem("30");
    ui->cbFPS->addItem("60");
    connect(this, SIGNAL(sendFps(int)), camera, SLOT(fpsChanged(int)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkCameraRunning()));
    connect(timer,SIGNAL(timeout()),this,SLOT(readStatus()));
    timer->start(50);
    ui->btnDetect->setEnabled(false);
    ui->radioRGB->setChecked(true);
    ui->statusDisplay->setText("Camera not working!");
    ui->timeProcessYolo->setText("");
    ui->fpsDetect->setText("");

    connect(camera,SIGNAL(sendDistance(double)),this,SLOT(recieveDistance(double)));

    /* *************************Process********************************* */

    timerProcess = new QTimer(this);
    connect(timerProcess,SIGNAL(timeout()),this,SLOT(process()));

    timerGoHome = new QTimer(this);
    connect(timerGoHome,SIGNAL(timeout()),this,SLOT(on_btn_Home_clicked()));

    timerFinish = new QTimer(this);
    connect(timerFinish,SIGNAL(timeout()),this,SLOT(FinishProcess()));

    timerClock = new QTimer(this);
    connect(timerClock,SIGNAL(timeout()),this,SLOT(TotalTimeClock()));
    /* *************************END Process********************************* */

    PCAimage = cv::Mat(480,640, CV_8UC3, cv::Scalar(0,0,0));
    //Xong thêm sau*****************************************************
    ui->timeProcessYolo->setText("Not Detect!");
    ui->fpsDetect->setText("Not Detect!");

    ui->groupBox_test->hide();
}

MainWindow::~MainWindow()
{
    camera->stop();
    yrc100micro_com.YRC1000microOffServo();
    yrc100micro_com.YRC1000microDisConnect();
    serial->terminate();
    yolov5->stop();
    delete ui;
}

void MainWindow::on_btn_connect_clicked()
{
    if(ui->btn_connect->text() == "Connect")
    {
        //      UDP connect
        QHostAddress udp_address;
        quint16 udp_port;
        quint16 udp_file_port;
        QString ip_string = ui->txt_ip->text();
        QStringList ip_list = ip_string.split(".");
        quint32 ip_int32 = (ip_list.at(0).toUInt() << 24) | (ip_list.at(1).toUInt() << 16)
                           | (ip_list.at(2).toUInt() << 8) | ip_list.at(3).toUInt();
        udp_address.setAddress(ip_int32);
        udp_port = ui->txt_port->text().toUShort();
        udp_file_port = ui->txt_filePort->text().toUShort();

        yrc100micro_com.YRC1000microSetConnection(udp_address,udp_port,udp_file_port);
        bool connection_satus = yrc100micro_com.YRC1000microConnect();

        ui->btn_connect->setText("Disconnect");
        ui->btn_connect->setPalette(pal_green);

        emit connectClickToUpdateThread(true);
    }
    else if(ui->btn_connect->text() == "Disconnect")
    {
        ui->btn_connect->setText("Connect");
        ui->btn_connect->setPalette(pal_red);

        yrc100micro_com.YRC1000microDisConnect();

        emit connectClickToUpdateThread(false);
    }
}

void MainWindow::on_btn_servo_clicked()
{
    if(ui->btn_servo->text() == "Servo On"){
        yrc100micro_com.YRC1000microOnServo();
        ui->btn_servo->setText("Servo Off");
        ui->btn_servo->setPalette(pal_green);
    }
    else if(ui->btn_servo->text() == "Servo Off"){
        yrc100micro_com.YRC1000microOffServo();
        ui->btn_servo->setText("Servo On");
        ui->btn_servo->setPalette(pal_red);
    }
}

void MainWindow::on_btn_Home_clicked()
{
    double set_speed = ui->txt_homeSpeed->text().toDouble();
    QVector<double> set_position;
    //    set_position.append(185);
    //    set_position.append(0);
    //    set_position.append(-42);
    //    set_position.append(180);
    //    set_position.append(0);
    //    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    yrc100micro_com.YRC1000microMovePulse(set_speed*10,&set_position );
    //    axisS = 0;
    //    axisL = 0;
    //    axisU = 0;
    //    axisR = 0;
    //    axisB = 0;
    //    axisT = 0;

    timerGoHome->stop();
}

void MainWindow::on_txt_homeSpeed_editingFinished()
{
    double  set_speed = ui->txt_homeSpeed->text().toDouble();
    if (set_speed > maxSpeed)
    {
        set_speed = maxSpeed;
        ui->txt_homeSpeed->setText(QString::number(maxSpeed));
    }
}

void MainWindow::take_comboBoxData_forThread()
{
    QString serialName =  ui->comboBox_COM->currentText();
    QString serialLoc  =  ui->comboBox_COM->currentData().toString();
    emit comboBoxDataAnswer(serialName,serialLoc);
}

void MainWindow::comboBoxAddItem(QString Name, QString Location)
{
    ui->comboBox_COM->addItem(Name,Location);
}

void MainWindow::btnConnectSetText(QString text)
{
    ui->btn_ConnectServo->setText(text);
    if(ui->btn_ConnectServo->text() == "CONNECT"){
        ui->btn_ConnectServo->setPalette(pal_red);
    }
    else if(ui->btn_ConnectServo->text() == "DISCONNECT"){
        ui->btn_ConnectServo->setPalette(pal_green);

    }
}

void MainWindow::takeIpTextForThread()
{
    emit textIpAnswer(ui->txt_ip->text(), ui->txt_port->text().toUShort(), (short) ui->txt_filePort->text().toUShort());
}

void MainWindow::setGetLabelFromMain(QString x, QString y, QString z, QString roll, QString pitch, QString yaw)
{
    ui->txt_getX->setText(x);
    ui->txt_getY->setText(y);
    ui->txt_getZ->setText(z);
    ui->txt_getRoll->setText(roll);
    ui->txt_getPitch->setText(pitch);
    ui->txt_getYaw->setText(yaw);
}

void MainWindow::setGetPulseLabelFromMain(QString s, QString l, QString u, QString r, QString b, QString t)
{
    ui->txt_getS->setText(s);
    ui->txt_getL->setText(l);
    ui->txt_getU->setText(u);
    ui->txt_getR->setText(r);
    ui->txt_getB->setText(b);
    ui->txt_getT->setText(t);
}

void MainWindow::receiveImage(QImage rgbImg, QImage depthImg)
{
    cv::Point a = cv::Point(332,170);
    cv::Point b = cv::Point(532,170);
    cv::Point c = cv::Point(332,350);
    cv::Point d = cv::Point(532,350);
    cv::Mat temp = convertQImagetoMat(rgbImg);

    cv::line(temp, a, b, BLUE, 3, cv::LINE_AA);
    cv::line(temp, a, c, BLUE, 3, cv::LINE_AA);
    cv::line(temp, b, d, BLUE, 3, cv::LINE_AA);
    cv::line(temp, c, d, BLUE, 3, cv::LINE_AA);

    //left
    a = cv::Point(332,170);
    b = cv::Point(382,170);
    c = cv::Point(332,350);
    d = cv::Point(382,350);
    cv::line(temp, a, b, RED , 1, cv::LINE_AA);
    cv::line(temp, a, c, RED , 1, cv::LINE_AA);
    cv::line(temp, b, d, RED , 1, cv::LINE_AA);
    cv::line(temp, c, d, RED , 1, cv::LINE_AA);
    //right
    a = cv::Point(482,170);
    b = cv::Point(532,170);
    c = cv::Point(482,350);
    d = cv::Point(532,350);
    cv::line(temp, a, b, RED , 1, cv::LINE_AA);
    cv::line(temp, a, c, RED , 1, cv::LINE_AA);
    cv::line(temp, b, d, RED , 1, cv::LINE_AA);
    cv::line(temp, c, d, RED , 1, cv::LINE_AA);
    //top
    a = cv::Point(332,170);
    b = cv::Point(532,170);
    c = cv::Point(332,220);
    d = cv::Point(532,220);
    cv::line(temp, a, b, GREEN , 1, cv::LINE_AA);
    cv::line(temp, a, c, GREEN , 1, cv::LINE_AA);
    cv::line(temp, b, d, GREEN , 1, cv::LINE_AA);
    cv::line(temp, c, d, GREEN , 1, cv::LINE_AA);
    //bottom
    a = cv::Point(332,300);
    b = cv::Point(532,300);
    c = cv::Point(332,350);
    d = cv::Point(532,350);
    cv::line(temp, a, b, GREEN , 1, cv::LINE_AA);
    cv::line(temp, a, c, GREEN , 1, cv::LINE_AA);
    cv::line(temp, b, d, GREEN , 1, cv::LINE_AA);
    cv::line(temp, c, d, GREEN , 1, cv::LINE_AA);

    cv::Mat cropped_image = temp(cv::Range(120,400), cv::Range(243,617));
    ui->displayRGB->setPixmap(QPixmap::fromImage(convertMattoQImage(cropped_image)).scaled(640, 480, Qt::KeepAspectRatio));
    //    cv::imshow("",temp);
//    ui->displayRGB->setPixmap(QPixmap::fromImage(convertMattoQImage(temp)));
    ui->displayDepth->setPixmap(QPixmap::fromImage(depthImg));
}

void MainWindow::receiveFrameYolo(QImage img)
{
    cv::Mat image;
    cv::addWeighted(convertQImagetoMat(img), 1, PCAimage, 1, 0, image);
    //cv::imshow("",image);
    //crop image
    cv::Mat cropped_image = image(cv::Range(120,400), cv::Range(243,617));//cv::Range(170,350), cv::Range(310,550)
    ui->displayYoloDectect->setPixmap(QPixmap::fromImage(convertMattoQImage(cropped_image)).scaled(640, 480, Qt::KeepAspectRatio));

    ui->numDetect->setText(QString::number(yolov5->numberDetect));
}

void MainWindow::receiveFramePCA(QImage img, int ID)
{

    PCAimage_main = img;
    classID = ID;
    static int i = 0;
    if (i == 0)
    {
        i++;
    }
    else if (!refillFlag)
    {
        timerProcess->start(200);
    }
    timerFinish->stop();
}

void MainWindow::receiveTimeProcess(double t)
{
    ui->timeProcessYolo->setText("Inference time : " + QString::number(t) + " ms");
    ui->fpsDetect->setText("FPS = " + QString().setNum(1000/t, 'g', 2) );
}

void MainWindow::checkCameraRunning(){
    if(camera->isCameraruning==true)
    {
        ui->cbFPS->setEnabled(false);
        ui->cbResolution->setEnabled(false);
    }
    else
    {
        ui->cbFPS->setEnabled(true);
        ui->cbResolution->setEnabled(true);
    }
}

void MainWindow::on_radioDepth_toggled(bool checked)
{
    if(checked == true){
        if(isCamStreaming){
            ui->displayDepth->show();
            ui->displayRGB->hide();
            ui->statusMode->setText("Depth mode");
        }
    }
}

void MainWindow::on_radioRGB_toggled(bool checked)
{
    if(checked == true){
        if(isCamStreaming){
            ui->displayRGB->show();
            ui->displayDepth->hide();
            ui->statusMode->setText("RGB mode");
        }
    }
}

void MainWindow::on_cbResolution_currentTextChanged(const QString &arg1)
{
    if (arg1 == "424x240") {
        emit sendResolution(424, 240);
    }
    else if (arg1 == "640x360") {
        emit sendResolution(640, 360);
    }
    else {
        emit sendResolution(640, 480);
    }
}

void MainWindow::on_cbFPS_currentTextChanged(const QString &arg1)
{
    if(arg1 =="60")
        emit sendFps(30);
    else
        emit sendFps(60);
}

void MainWindow::on_btnStart_clicked()
{
    if(ui->btnStart->text() == "START")
    {
        if(ui->radioRGB->isChecked()==true){
            ui->displayRGB->show();
        }else{
            ui->displayRGB->hide();
        }
        //ui->btnStart->setEnabled(false);
        //ui->btnStop->setEnabled(true);
        ui->btnDetect->setEnabled(true);
        ui->statusDisplay->setText("Camera is running!");
        camera->cmd();
        isCamStreaming = true;

        ui->btnStart->setText("STOP");
        ui->btnStart->setPalette(pal_green);
    }

    else if(ui->btnStart->text() == "STOP"){
        ui->displayRGB->hide();
        ui->displayDepth->hide();
        //ui->btnStop->setEnabled(false);
        //ui->btnStart->setEnabled(true);
        ui->btnDetect->setEnabled(false);
        camera->stop();
        yolov5->stop();
        isCamStreaming = false;
        ui->statusDisplay->setText("Camera was stopped!");
        ui->displayYoloDectect->hide();
        ui->timeProcessYolo->setText("Detect was stopped!");

        ui->btnStart->setText("START");
        ui->btnStart->setPalette(pal_red);
    }

}

void MainWindow::on_btnDetect_clicked()
{
    if(ui->btnDetect->text()== "DETECT"){
        ui->displayYoloDectect->show();
        yolov5->cmd();
        ui->btnStartProcess->setEnabled(true);

        ui->btnDetect->setText("STOP DETECT");
        ui->btnDetect->setPalette(pal_green);
    }
    else if(ui->btnDetect->text()== "STOP DETECT"){
        ui->timeProcessYolo->setText("Detect was stopped!");
        yolov5->stop();

        ui->btnDetect->setText("DETECT");
        ui->btnDetect->setPalette(pal_red);
    }
}

void MainWindow::on_btnStartProcess_clicked()
{
    if(ui->btnStartProcess->text() == "START PROCESS"){
        timerGoHome->stop();
        isRunningProcess = true;
        refillFlag = false;
        on_btn_Home_clicked();
        emit sendPCArequest(0);
        timerProcess->start(200);
        state = 0;

        ui->btnStartProcess->setText("STOP PROCESS");
        ui->btnStartProcess->setPalette(pal_green);
        totalTime = 0;
        timerClock->start(1000);
    }
    else if(ui->btnStartProcess->text() == "STOP PROCESS"){
        timerGoHome->start(2000);
        ui->slider_Servo->setValue(55);
        timerProcess->stop();
        isRunningProcess = false;
        timerFinish->stop();

        ui->btnStartProcess->setText("START PROCESS");
        ui->btnStartProcess->setPalette(pal_red);
        timerClock->stop();
    }

}

QImage MainWindow::convertMattoQImage(cv::Mat mat)
{
    return  QImage((const unsigned char*)(mat.data), mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_RGB888).rgbSwapped();
}

cv::Mat MainWindow::convertQImagetoMat(QImage img)
{
    img = img.convertToFormat(QImage::Format_RGB888, Qt::ColorOnly).rgbSwapped();
    return cv::Mat(img.height(), img.width(), CV_8UC3, img.bits(), img.bytesPerLine()).clone();
}

QPixmap MainWindow::cvMatToQPixmap(const cv::Mat &inMat)
{
    return QPixmap::fromImage(convertMattoQImage(inMat));

}

void MainWindow::drawAxis(cv::Mat &img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale)
{
    double angle = atan2( (double) p.y - q.y, (double) p.x - q.x ); // angle in radians
    double hypotenuse = sqrt( (double) (p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));
    // Here we lengthen the arrow by a factor of scale
    q.x = (int) (p.x - scale * hypotenuse * cos(angle));
    q.y = (int) (p.y - scale * hypotenuse * sin(angle));
    cv::line(img, p, q, colour, 1, cv::LINE_AA);
    // create the arrow hooks
    p.x = (int) (q.x + 9 * cos(angle + CV_PI / 4));
    p.y = (int) (q.y + 9 * sin(angle + CV_PI / 4));
    cv::line(img, p, q, colour, 1, cv::LINE_AA);
    p.x = (int) (q.x + 9 * cos(angle - CV_PI / 4));
    p.y = (int) (q.y + 9 * sin(angle - CV_PI / 4));
    cv::line(img, p, q, colour, 1, cv::LINE_AA);
}

double MainWindow::getOrientation(const std::vector<cv::Point> &pts, cv::Mat &img)
{
    //Construct a buffer used by the pca analysis
    int sz = static_cast<int>(pts.size());
    cv::Mat data_pts = cv::Mat(sz, 2, CV_64F);
    for (int i = 0; i < data_pts.rows; i++)
    {
        data_pts.at<double>(i, 0) = pts[i].x;
        data_pts.at<double>(i, 1) = pts[i].y;
    }
    //Perform PCA analysis
    cv::PCA pca_analysis(data_pts, cv::Mat(), cv::PCA::DATA_AS_ROW);
    //Store the center of the object
    cv::Point cntr = cv::Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
                               static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
    //Store the eigenvalues and eigenvectors
    std::vector<cv::Point2d> eigen_vecs(2);
    std::vector<double> eigen_val(2);
    for (int i = 0; i < 2; i++)
    {
        eigen_vecs[i] = cv::Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
                                    pca_analysis.eigenvectors.at<double>(i, 1));
        eigen_val[i] = pca_analysis.eigenvalues.at<double>(i);
    }



    // p1 theo chieu doc
    cv::Point p1 = cntr + 0.5 * cv::Point(static_cast<int>(eigen_vecs[0].x * eigen_val[0]), static_cast<int>(eigen_vecs[0].y * eigen_val[0]));
    // p2 theo chieu ngang
    cv::Point p2 = cntr - 0.5 * cv::Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));

    double a,b;

    a = (double)((double)(cntr.y - p1.y)/(double)(cntr.x - p1.x));
    b = cntr.y - a*cntr.x;




    double dMax = 0;
    double xMax = pts[0].x;
    double yMax = pts[0].y;

    for (int i = 0; i < sz; i++)
    {
        double temp = (double)((double)abs(pts[i].y - a*pts[i].x - b)/(double)(sqrt(pow(a,2)+pow(b,2))));
        if (temp > dMax)
        {
            dMax = temp;
            xMax = pts[i].x;
            yMax = pts[i].y;
        }
    }


    point_ctr_vertical = cntr;


    // vector cntr to p1
    double x_cntr2p1 = p1.x - cntr.x;
    double y_cntr2p1 = p1.y - cntr.y;

    // vector cntr to Max
    double x_cntr2Max = xMax - cntr.x;
    double y_cntr2Max = yMax - cntr.y;

    double arg;

    arg = std::acos((double)((double)(x_cntr2Max*x_cntr2p1)+(double)(y_cntr2Max*y_cntr2p1))/
                    (double)((double)(sqrt(pow(x_cntr2Max,2)+pow(y_cntr2Max,2))*sqrt(pow(x_cntr2p1,2)+pow(y_cntr2p1,2)))))*180/CV_PI;
    //std::cout << "arg" << arg << std::endl;

    cv::Point new_p1;

    if (arg > 90)
    {
        new_p1 = cv::Point(2*cntr.x - p1.x, 2*cntr.y-p1.y);
    }
    else
    {
        new_p1 = cv::Point(p1.x, p1.y);
    }

    //create direction vector ctr_newp1
    a_ctr_newp1 = new_p1.x - cntr.x;
    b_ctr_newp1 = new_p1.y - cntr.y;
    // Calculate offset point
    //create new point_ctr
    point_ctr.x = cntr.x - a_ctr_newp1*0.03;
    point_ctr.y = cntr.y - b_ctr_newp1*0.03;

    point_head.x = cntr.x + a_ctr_newp1*0.01;
    point_head.y = cntr.y + b_ctr_newp1*0.01;

    point_tail.x = cntr.x - a_ctr_newp1*0.08;
    point_tail.y = cntr.y - b_ctr_newp1*0.08;




    // Draw the principal components
    cv::circle(img, point_ctr, 3, BLACK, 2);
    cv::circle(img, point_head, 3, RED, 2);
    cv::circle(img, point_tail, 3, BLUE, 2);


    //drawAxis(img, cntr, p1, cv::Scalar(0, 255, 0), 1);
    drawAxis(img, point_ctr, new_p1, cv::Scalar(0, 0, 255), 1);
    drawAxis(img, point_ctr, p2, cv::Scalar(255, 255, 0), 1);

    double angle = atan2(new_p1.y - cntr.y, new_p1.x - cntr.x); // orientation in radians
    rotateAngle =  angle*180/CV_PI;

    //********************Xác định ốc nằm trong các vùng riêng biệt*******************
    top_L= false;
    top_R = false;
    left_T = false;
    left_B = false;
    bottom_L = false;
    bottom_R = false;
    right_T = false;
    right_B = false;
    if(cntr.y < 220){//top
        if((rotateAngle >= -180 && rotateAngle <= -150) || (rotateAngle >= 150 && rotateAngle <= 180) ){
            top_L = true;
        }else if((rotateAngle >= -30 && rotateAngle <= 30)){
            top_R = true;
        }
        //chổ này là xét cho những con ốc nằm trong góc nên lặp lại
        else if(cntr.x < 382){//left
            if((rotateAngle >= -120 && rotateAngle <= -60)){
                left_T = true;
            }else if((rotateAngle >= 60 && rotateAngle <= 120))
            {
                left_B = true;
            }
        }else if(cntr.x > 480){//right
            if((rotateAngle >= -120 && rotateAngle <= -60)){
                right_T = true;
            }else if((rotateAngle >= 60 && rotateAngle <= 120))
            {
                right_B = true;
            }
        }

    }else if(cntr.y > 300){//bottom
        if((rotateAngle >= -180 && rotateAngle <= -150) || (rotateAngle >= 150 && rotateAngle <= 180) ){
            bottom_L = true;
        }else if((rotateAngle >= -30 && rotateAngle <= 30)){
            bottom_R = true;
        }
        else if(cntr.x < 382){//left
            if((rotateAngle >= -120 && rotateAngle <= -60)){
                left_T = true;
            }else if((rotateAngle >= 60 && rotateAngle <= 120))
            {
                left_B = true;
            }
        }else if(cntr.x > 482){//right
            if((rotateAngle >= -120 && rotateAngle <= -60)){
                right_T = true;
            }else if((rotateAngle >= 60 && rotateAngle <= 120))
            {
                right_B = true;
            }
        }
    }else if(cntr.x < 382){//left
        if((rotateAngle >= -120 && rotateAngle <= -60)){
            left_T = true;
        }else if((rotateAngle >= 60 && rotateAngle <= 120))
        {
            left_B = true;
        }
    }else if(cntr.x > 482){//right
        if((rotateAngle >= -120 && rotateAngle <= -60)){
            right_T = true;
        }else if((rotateAngle >= 60 && rotateAngle <= 120))
        {
            right_B = true;
        }
    }

    //**************Xác định điểm đầu cuối con ốc*****************
    // vector cntr to new_p1
    double cntr_p1new_x = new_p1.x - cntr.x;
    double cntr_p1new_y = new_p1.y - cntr.y;
    double degmax = 0, degmin = 180;
    x1 = pts[0].x; //đầu
    y1 = pts[0].y;
    x2 = pts[0].x; //cuối
    y2 = pts[0].y;

    for (int i = 0; i < sz; i++)
    {
        double cntr_pi_x = pts[i].x - cntr.x;
        double cntr_pi_y = pts[i].y - cntr.y;
        double arg = std::acos((double)((double)(cntr_p1new_x*cntr_pi_x)+(double)(cntr_p1new_y*cntr_pi_y))/
                               (double)((double)(sqrt(pow(cntr_p1new_x,2)+pow(cntr_p1new_y,2))*sqrt(pow(cntr_pi_x,2)+pow(cntr_pi_y,2)))))*180/CV_PI;
        if(arg < degmin){
            degmin = arg;
            x1 = pts[i].x;
            y1 = pts[i].y;
        }

        if(arg > degmax){
            degmax = arg;
            x2 = pts[i].x;
            y2 = pts[i].y;
        }
    }
    lengthOfBold = (double)(sqrt(pow(x1-x2, 2)+ pow(y1-y2, 2)));

    //**************Xác định điểm trái phải con ốc*****************
    // vector cntr to p2
    double cntr_p2_x = p2.x - cntr.x;
    double cntr_p2_y = p2.y - cntr.y;
    double degmax2 = 0, degmin2 = 180;
    x3 = pts[0].x; //đầu
    y3 = pts[0].y;
    x4 = pts[0].x; //cuối
    y4 = pts[0].y;

    for (int i = 0; i < sz; i++)
    {
        double cntr_pi_x2 = pts[i].x - cntr.x;
        double cntr_pi_y2 = pts[i].y - cntr.y;
        double arg = std::acos((double)((double)(cntr_p2_x*cntr_pi_x2)+(double)(cntr_p2_y*cntr_pi_y2))/
                               (double)((double)(sqrt(pow(cntr_p2_x,2)+pow(cntr_p2_y,2))*sqrt(pow(cntr_pi_x2,2)+pow(cntr_pi_y2,2)))))*180/CV_PI;
        if(arg < degmin2){
            degmin2 = arg;
            x3 = pts[i].x;
            y3 = pts[i].y;
        }

        if(arg > degmax2){
            degmax2 = arg;
            x4 = pts[i].x;
            y4 = pts[i].y;
        }
    }
    widthOfBold = (double)(sqrt(pow(x3-x4, 2)+ pow(y3-y4, 2)));
    return angle;
}

cv::Mat MainWindow::PCA(cv::Mat img)
{
    cv::Mat src = img;
    // Check if image is loaded successfully
    if(src.empty())
    {
        std::cout << "Problem loading image!!!" << std::endl;
    }
    //cv::imshow("src", src);
    // Convert image to grayscale
    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    // Convert image to binary
    //cv::imshow("gray", gray);

    cv::Mat bw;
    cv::threshold(gray, bw, 50, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    // Find all the contours in the thresholded image
    //cv::imshow("bw", bw);

    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(bw, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    //std::cout<<"contour size: " << contours[0].size() << std::endl;

    for (size_t i = 0; i < contours.size(); i++)
    {
        // Calculate the area of each contour
        double area = cv::contourArea(contours[i]);
        // Ignore contours that are too small or too large
        if (area < 1e2 || 1e5 < area) continue;
        // Draw each contour only for visualisation purposes
        cv::drawContours(src, contours, static_cast<int>(i), cv::Scalar(0, 0, 255), 2);
        // Find the orientation of each shape
        getOrientation(contours[i], src);
    }
    return src;
}

void MainWindow::readResultTextFile(QString fileName, cv::Mat &Tsai, cv::Mat &Park, cv::Mat &Horaud, cv::Mat &Daniilidis, cv::Mat &Andreff)
{
    QFile file(fileName);

    if (!file.exists())
    {
        qDebug()<<"File not found";
    }

    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical()<< file.errorString();
    }

    QTextStream stream(&file);

    while (!stream.atEnd())
    {

        QString line =  file.readLine();
        QStringList tag;
        tag.append("CALIB_HAND_EYE_TSAI\n");
        tag.append("CALIB_HAND_EYE_PARK\n");
        tag.append("CALIB_HAND_EYE_HORAUD\n");
        tag.append("CALIB_HAND_EYE_DANIILIDIS\n");
        tag.append("CALIB_HAND_EYE_ANDREFF\n");


        switch (tag.indexOf(line))
        {
        case 0:
        {
            if (file.readLine() == "R_cam2base\n")
            {
                cv::Mat temp = cv::Mat::eye(4,4,CV_64F);
                QList<QString> row1,row2,row3;
                //read row 1
                line = file.readLine();
                row1 = line.split(";");
                //read row 2
                line = file.readLine();
                row2 = line.split(";");
                //read row 3
                line = file.readLine();
                row3 = line.split(";");
                // remove "\n"
                row1.removeLast();
                row2.removeLast();
                row3.removeLast();

                //row 1
                temp.row(0).col(0) = row1[0].toDouble();
                temp.row(0).col(1) = row1[1].toDouble();
                temp.row(0).col(2) = row1[2].toDouble();
                //row 2
                temp.row(1).col(0) = row2[0].toDouble();
                temp.row(1).col(1) = row2[1].toDouble();
                temp.row(1).col(2) = row2[2].toDouble();
                //row 3
                temp.row(2).col(0) = row3[0].toDouble();
                temp.row(2).col(1) = row3[1].toDouble();
                temp.row(2).col(2) = row3[2].toDouble();
                if (file.readLine() == "t_cam2base\n")
                {
                    QList<QString> col4;

                    line = file.readLine();
                    col4 = line.split(";");
                    col4.removeLast();
                    temp.row(0).col(3) = col4[0].toDouble();
                    temp.row(1).col(3) = col4[1].toDouble();
                    temp.row(2).col(3) = col4[2].toDouble();

                    temp.copyTo(Tsai);
                    //std::cout << "Tsai matrix: " <<std::endl;
                    //std::cout << Tsai <<std::endl;

                }
            }
            break;
        }
        case 1:
        {
            if (file.readLine() == "R_cam2base\n")
            {
                cv::Mat temp = cv::Mat::eye(4,4,CV_64F);
                QList<QString> row1,row2,row3;
                //read row 1
                line = file.readLine();
                row1 = line.split(";");
                //read row 2
                line = file.readLine();
                row2 = line.split(";");
                //read row 3
                line = file.readLine();
                row3 = line.split(";");
                // remove "\n"
                row1.removeLast();
                row2.removeLast();
                row3.removeLast();

                //row 1
                temp.row(0).col(0) = row1[0].toDouble();
                temp.row(0).col(1) = row1[1].toDouble();
                temp.row(0).col(2) = row1[2].toDouble();
                //row 2
                temp.row(1).col(0) = row2[0].toDouble();
                temp.row(1).col(1) = row2[1].toDouble();
                temp.row(1).col(2) = row2[2].toDouble();
                //row 3
                temp.row(2).col(0) = row3[0].toDouble();
                temp.row(2).col(1) = row3[1].toDouble();
                temp.row(2).col(2) = row3[2].toDouble();
                if (file.readLine() == "t_cam2base\n")
                {
                    QList<QString> col4;

                    line = file.readLine();
                    col4 = line.split(";");
                    col4.removeLast();
                    temp.row(0).col(3) = col4[0].toDouble();
                    temp.row(1).col(3) = col4[1].toDouble();
                    temp.row(2).col(3) = col4[2].toDouble();

                    temp.copyTo(Park);
                    //std::cout << "Park matrix: " <<std::endl;
                    //std::cout << Park <<std::endl;

                }
            }
            break;
        }
        case 2:
        {
            if (file.readLine() == "R_cam2base\n")
            {
                cv::Mat temp = cv::Mat::eye(4,4,CV_64F);
                QList<QString> row1,row2,row3;
                //read row 1
                line = file.readLine();
                row1 = line.split(";");
                //read row 2
                line = file.readLine();
                row2 = line.split(";");
                //read row 3
                line = file.readLine();
                row3 = line.split(";");
                // remove "\n"
                row1.removeLast();
                row2.removeLast();
                row3.removeLast();

                //row 1
                temp.row(0).col(0) = row1[0].toDouble();
                temp.row(0).col(1) = row1[1].toDouble();
                temp.row(0).col(2) = row1[2].toDouble();
                //row 2
                temp.row(1).col(0) = row2[0].toDouble();
                temp.row(1).col(1) = row2[1].toDouble();
                temp.row(1).col(2) = row2[2].toDouble();
                //row 3
                temp.row(2).col(0) = row3[0].toDouble();
                temp.row(2).col(1) = row3[1].toDouble();
                temp.row(2).col(2) = row3[2].toDouble();
                if (file.readLine() == "t_cam2base\n")
                {
                    QList<QString> col4;

                    line = file.readLine();
                    col4 = line.split(";");
                    col4.removeLast();
                    temp.row(0).col(3) = col4[0].toDouble();
                    temp.row(1).col(3) = col4[1].toDouble();
                    temp.row(2).col(3) = col4[2].toDouble();

                    temp.copyTo(Horaud);
                    //std::cout << "Horaud matrix: " <<std::endl;
                    //std::cout << Horaud <<std::endl;

                }
            }
            break;
        }
        case 3:
        {
            if (file.readLine() == "R_cam2base\n")
            {
                cv::Mat temp = cv::Mat::eye(4,4,CV_64F);
                QList<QString> row1,row2,row3;
                //read row 1
                line = file.readLine();
                row1 = line.split(";");
                //read row 2
                line = file.readLine();
                row2 = line.split(";");
                //read row 3
                line = file.readLine();
                row3 = line.split(";");
                // remove "\n"
                row1.removeLast();
                row2.removeLast();
                row3.removeLast();

                //row 1
                temp.row(0).col(0) = row1[0].toDouble();
                temp.row(0).col(1) = row1[1].toDouble();
                temp.row(0).col(2) = row1[2].toDouble();
                //row 2
                temp.row(1).col(0) = row2[0].toDouble();
                temp.row(1).col(1) = row2[1].toDouble();
                temp.row(1).col(2) = row2[2].toDouble();
                //row 3
                temp.row(2).col(0) = row3[0].toDouble();
                temp.row(2).col(1) = row3[1].toDouble();
                temp.row(2).col(2) = row3[2].toDouble();
                if (file.readLine() == "t_cam2base\n")
                {
                    QList<QString> col4;

                    line = file.readLine();
                    col4 = line.split(";");
                    col4.removeLast();
                    temp.row(0).col(3) = col4[0].toDouble();
                    temp.row(1).col(3) = col4[1].toDouble();
                    temp.row(2).col(3) = col4[2].toDouble();

                    temp.copyTo(Daniilidis);
                    //std::cout << "Daniilidis matrix: " <<std::endl;
                    //std::cout << Daniilidis <<std::endl;

                }
            }
            break;
        }
        case 4:
        {
            if (file.readLine() == "R_cam2base\n")
            {
                cv::Mat temp = cv::Mat::eye(4,4,CV_64F);
                QList<QString> row1,row2,row3;
                //read row 1
                line = file.readLine();
                row1 = line.split(";");
                //read row 2
                line = file.readLine();
                row2 = line.split(";");
                //read row 3
                line = file.readLine();
                row3 = line.split(";");
                // remove "\n"
                row1.removeLast();
                row2.removeLast();
                row3.removeLast();

                //row 1
                temp.row(0).col(0) = row1[0].toDouble();
                temp.row(0).col(1) = row1[1].toDouble();
                temp.row(0).col(2) = row1[2].toDouble();
                //row 2
                temp.row(1).col(0) = row2[0].toDouble();
                temp.row(1).col(1) = row2[1].toDouble();
                temp.row(1).col(2) = row2[2].toDouble();
                //row 3
                temp.row(2).col(0) = row3[0].toDouble();
                temp.row(2).col(1) = row3[1].toDouble();
                temp.row(2).col(2) = row3[2].toDouble();
                if (file.readLine() == "t_cam2base\n")
                {
                    QList<QString> col4;

                    line = file.readLine();
                    col4 = line.split(";");
                    col4.removeLast();
                    temp.row(0).col(3) = col4[0].toDouble();
                    temp.row(1).col(3) = col4[1].toDouble();
                    temp.row(2).col(3) = col4[2].toDouble();

                    temp.copyTo(Andreff);
                    //std::cout << "Andreff matrix: "<<std::endl;
                    //std::cout <<  Andreff <<std::endl;
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
    file.close();
}

void MainWindow::recieveDistance(double dist)
{
    distance_fromCam = dist;
}

void MainWindow::moveToTarget(QVector<double> position)
{
    double speed = Speed_Picking;
    yrc100micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                              CMD_HEADER_MOVE_INSTANCE_LINK_ABSOLUTE,CMD_DATA_MOVE_SPEED_TYPE_V_SPEED,speed,&position);
}

void MainWindow::moveDown1(int clsid)
{
    double set_speed = 60;
    QVector<double> set_position;
    set_position.append(0);
    set_position.append(0);
    if (clsid == 0)
    {
        set_position.append(-30);
    }
    else
    {
        set_position.append(0);
    }
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    yrc100micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                              CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_V_SPEED,set_speed,&set_position);
}

void MainWindow::moveDown2(int clsid, int typid)
{
    double set_speed = 30;
    QVector<double> set_position;
    set_position.append(0);
    set_position.append(0);
    if (clsid == 0)
    {
        if (typid == 3){
            set_position.append(-20);
        }
        else{
            set_position.append(-15);
        }
    }
    else
    {
        set_position.append(-27);
    }
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    yrc100micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                              CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_V_SPEED,set_speed,&set_position);
}

void MainWindow::moveToPlacePoint(int clssid,int typid)
{
    double set_speed = Speed_Picking;
    QVector<double> set_position;
    if(clssid == 0){
        if(typid == 1){
            set_position.append(27885);
            set_position.append(39958);
            set_position.append(16630);
            set_position.append(-2960);
            set_position.append(3730);
            set_position.append(19538);

        }
        else if(typid == 2){
            set_position.append(30524);
            set_position.append(22260);
            set_position.append(3248);
            set_position.append(-4298);
            set_position.append(7059);
            set_position.append(19597);

        }
        else{
            set_position.append(36974);
            set_position.append(7821);
            set_position.append(-5686);
            set_position.append(-4147);
            set_position.append(8448);
            set_position.append(17900);

        }

        yrc100micro_com.YRC1000microMovePulse(set_speed*10,&set_position );
    }
    else
    {
        set_position.append(190);
        set_position.append(-100);
        set_position.append(-22);
        set_position.append(-115);
        set_position.append(2);
        set_position.append(-2);

        yrc100micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                                  CMD_HEADER_MOVE_INSTANCE_LINK_ABSOLUTE,CMD_DATA_MOVE_SPEED_TYPE_V_SPEED,set_speed,&set_position);
    }


}

void MainWindow::moveUp()
{
    double set_speed = Speed_Picking;
    QVector<double> set_position;
    set_position.append(0);
    set_position.append(0);
    if (classID == 0)
    {
        set_position.append(50);
    }
    else
    {
        set_position.append(20);
    }
    set_position.append(0);
    set_position.append(0);
    set_position.append(0);
    yrc100micro_com.YRC1000microMoveCartesian(CMD_DATA_MOVE_COORDINATE_ROBOT,
                                              CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT,CMD_DATA_MOVE_SPEED_TYPE_V_SPEED,set_speed,&set_position);
}

double MainWindow::getPitchAngel(std::vector<arma::vec3> points){
    int N = points.size();
    int negative_value = 0;
    if(points[0].at(2) < points[2].at(2)){
        negative_value = -1;
    }else {
        negative_value = 1;
    }
    std::cout << "N = " << N << std::endl;
    arma::vec3 mean = {0, 0, 0};
    arma::mat33 corr(arma::fill::zeros);
    for(auto p : points)
    {
        mean += p;
        for(int i = 0; i < 3; i++)
            for(int j = i; j < 3; j++)
                corr(i, j) += p(i) * p(j);
    }

    corr /= N;
    mean /= N;

    arma::mat33 cov {{
        {corr(0, 0) - mean(0) * mean(0), corr(0, 1) - mean(0) * mean(1), corr(0, 2) - mean(0) * mean(2)},
        {corr(0, 1) - mean(0) * mean(1), corr(1, 1) - mean(1) * mean(1), corr(1, 2) - mean(1) * mean(2)},
        {corr(0, 2) - mean(0) * mean(2), corr(1, 2) - mean(2) * mean(1), corr(2, 2) - mean(2) * mean(2)}
    }};

    arma::vec3 eigval; arma::mat33 eigvec;
    eig_sym(eigval, eigvec, cov);

    arma::vec3 DirectionVector = eigvec.col(eigval.index_max());
    DirectionVector.print("This is Direction: ");
    double x, y, z, pitch;
    x = DirectionVector.at(0);
    y = DirectionVector.at(1);
    z = DirectionVector.at(2);


    pitch = std::atan2(sqrt(x*x + y*y), z);
    //pitch = asin(y / sqrt(x*x+y*y+z*z));
    return (90 - pitch*180/CV_PI)*negative_value;
}

arma::vec3 MainWindow::convert2Dto3D(cv::Point point, int n){
    cv::Mat pixel(4,1,CV_64F);

    if(n==4){
        distance_fromCam = 0.35;
    }
    else{
        //n=1:head, 2:cntr, 3:tail
        camera->getDistance(point.x, point.y);
        while(distance_fromCam == 0){
            if(n==1){
                point_head.x = point_head.x + a_ctr_newp1*0.002;
                point_head.y = point_head.y + b_ctr_newp1*0.002;
                point = point_head;
            }
            if(n==2){
                point_ctr.x = point_ctr.x - a_ctr_newp1*0.002;
                point_ctr.y = point_ctr.y - b_ctr_newp1*0.002;
                point = point_ctr;
            }
            if(n==3){
                point_tail.x = point_tail.x - a_ctr_newp1*0.002;
                point_tail.y = point_tail.y - b_ctr_newp1*0.002;
                point = point_tail;
            }
            camera->getDistance(point.x, point.y);
        }
        if(n==1){
            std::cout <<"distance Head = " << distance_fromCam <<std::endl;
        }
        if(n==2){
            std::cout <<"distance Central = " << distance_fromCam <<std::endl;
        }
        if(n==3){
            std::cout <<"distance Tail = " << distance_fromCam <<std::endl;
        }
    }
    if(distance_fromCam > 0.361){
        distance_fromCam = 0.35;
    }

    pixel.at<double>(0,0) = point.x*distance_fromCam;
    pixel.at<double>(1,0) = point.y*distance_fromCam;
    pixel.at<double>(2,0) = 1*distance_fromCam;
    pixel.at<double>(3,0) = 1;

    camera->cameraMatrix.copyTo(In);
    Ex = Park(cv::Rect(0,0,4,3));
    temp = In*Ex;
    temp.copyTo(Matrix(cv::Rect(0,0,4,3)));
    Result = Matrix.inv()*pixel;
    arma::vec3 vec3_result = {Result.at<double>(0,0)*10, Result.at<double>(1,0)*10, Result.at<double>(2,0)*10};
    vec3_result.print("This is a point: ");
    return vec3_result;
}

void MainWindow::PCAMoving(QImage img, int clssid)
{
    if(isRunningProcess)
    {
        timerProcess->stop();

        PCAimage = PCA(convertQImagetoMat(img));
        YawAngle = rotateAngle - 90;// rotateAngle inside getOrientation
        if(YawAngle > 180){
            YawAngle = YawAngle - 360;
        }else if(YawAngle < -180){
            YawAngle = 360 + YawAngle;
        }
        readResultTextFile("Result/Result Test.txt",Tsai,Park,Horaud,Daniilidis,Andreff);

        //With class horizontal
        if(clssid == 0){
            // get coordinate offset point
            head3D = convert2Dto3D(point_head, 1);
            tail3D = convert2Dto3D(point_tail, 3);
            // get coordinate central point
            cntr3D = convert2Dto3D(point_ctr, 2);
            //xác địn loại bu lông, typeID = 1:normal, 2:thin, 3:fat/ lấy khoảng cách đến trung tâm
            if(distance_fromCam > 0.343){
                if(widthOfBold > 20){
                    typeID = 3;
                }
                else if(lengthOfBold > 60){
                    typeID = 2;
                }
                else{
                    typeID = 1;
                }
            }
            else
            {
                if(widthOfBold > 21){
                    typeID = 3;
                }
                else if(lengthOfBold > 61){
                    typeID = 2;
                }
                else{
                    typeID = 1;
                }
            }
            std::vector<arma::vec3> point3Ds {{
                head3D,
                cntr3D,
                tail3D
            }};
            PitchAngle = getPitchAngel(point3Ds);
            std::cout << "pitch = " << PitchAngle << std::endl;

            targetPosition.clear();
            targetPosition.append(Result.at<double>(0,0)*1000);
            targetPosition.append(Result.at<double>(1,0)*1000);
            targetPosition.append(Result.at<double>(2,0)*1000+40);

            if(left_T || bottom_L || right_B || top_R){
                targetPosition.append(160);
            }else if(left_B || bottom_R || right_T || top_L){
                targetPosition.append(-160);
            }
            else{
                targetPosition.append(180);
            }
            targetPosition.append(PitchAngle);
            targetPosition.append(YawAngle);
        }
        else{
            cntr3D = convert2Dto3D(point_ctr_vertical, 4);

            targetPosition.clear();
            targetPosition.append(Result.at<double>(0,0)*1000 );
            targetPosition.append(Result.at<double>(1,0)*1000);
            targetPosition.append(Result.at<double>(2,0)*1000+40);
            targetPosition.append(180);
            targetPosition.append(-10); //-40
            targetPosition.append(3.0029); //3.0029
        }

        /* ************************************* Move to target ************************************* */
        {
            if(targetPosition[2] < -32){
                targetPosition[2] = -32;
            }
            if(targetPosition[4] == 0){
                targetPosition[4] = 10;
            }
            else if(targetPosition[4] > 40){
                targetPosition[4] = 40;
            }

            moveToTarget(targetPosition);
            ui->slider_Servo->setValue(20);
            timerProcess->start(200);
            timerFinish->stop();
            state = 1;
        }
    }
}

void MainWindow::readStatus()
{
    yrc100micro_com.YRC1000microReadStatus();

    quint16 status_code = yrc100micro_com.updateRobotStatus();
    status_code &= RES_VALUE_READING_RUNNING_MASK;
    if(status_code)
    {
        ui->lb_run_status->setText("Running");
        ui->lb_run_status->setStyleSheet("background:green");
    }
    else
    {
        ui->lb_run_status->setText("Stop");
        ui->lb_run_status->setStyleSheet("background:white");
    }
}

void MainWindow::process()
{
    if (ui->lb_run_status->text() == "Running")
    {

    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 0))
    {
        time_start_process = std::clock();
        PCAMoving(PCAimage_main, classID);
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 1))
    {
        state = 2;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 2))
    {
        moveDown1(classID);
        state = 3;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 3))
    {
        state = 4;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 4))
    {
        if(classID == 0){
            if(left_T || bottom_L || right_B || top_R || left_B || bottom_R || right_T || top_L){
                if (typeID == 3)
                {
                    ui->slider_Servo->setValue(56);
                }
                else
                {
                    ui->slider_Servo->setValue(48);
                }
            }else{
                if (typeID == 3)
                {
                    ui->slider_Servo->setValue(52);
                }
                else
                {
                    ui->slider_Servo->setValue(45);
                }
            }
        }else
        {
            ui->slider_Servo->setValue(52);
        }
        moveDown2(classID, typeID);
        state = 5;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 5))
    {

        state = 6;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 6))
    {
        ui->slider_Servo->setValue(15);
        state = 7;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 7))
    {
        state = 8;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 8))
    {
        moveUp();
        state = 9;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 9))
    {
        state = 10;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 10))
    {
        moveToPlacePoint(classID, typeID);
        state = 11;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 11))
    {
        if(classID == 1){
            on_btn_Home_clicked();
        }
        ui->slider_Servo->setValue(55);
        state = 12;
    }
    else if ((ui->lb_run_status->text() == "Stop")&&(state == 12))
    {
        timerProcess->stop();
        emit sendPCArequest(0);
        state = 0;
        timerFinish->start(10000);
        time_end_process = std::clock();
        timeProcessPicking = (double(time_end_process - time_start_process) / double(CLOCKS_PER_SEC))*1000.0;
        ui->lbTimeProcessing->setText(QString::number(timeProcessPicking) + " ms");
    }
}

void MainWindow::FinishProcess()
{
    refillFlag = true;

    timerProcess->stop();
    timerClock->stop();

    QMessageBox msgBox;
    QPushButton *StopProcess = msgBox.addButton(tr("Stop Process"), QMessageBox::ActionRole);
    QPushButton *WaitForRefill = msgBox.addButton(tr("Wait For Refill"), QMessageBox::ActionRole);
    //QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);
    msgBox.setText("There is no more screw in the work space !");
    msgBox.setInformativeText("What do you want to do next ?");
    msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    msgBox.exec();

    if (msgBox.clickedButton() == StopProcess) {
        on_btnStartProcess_clicked();
    } else if (msgBox.clickedButton() == WaitForRefill) {
        QMessageBox msgBox1;
        QPushButton *Done = msgBox1.addButton(tr("Done"), QMessageBox::ActionRole);
        QPushButton *Cancel = msgBox1.addButton(tr("Cancel"), QMessageBox::ActionRole);
        msgBox1.setText("Waiting for refill !");
        msgBox1.setInformativeText("Refilling done ?");
        msgBox1.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        msgBox1.exec();
        if (msgBox1.clickedButton() == Done) {
            on_btn_Home_clicked();

            timerProcess->start(200);

            refillFlag = false;
            timerClock->start(1000);
        }else if(msgBox1.clickedButton() == Cancel){
            on_btnStartProcess_clicked();
        }
    }
    //std::cout << msgBox.clickedButton() << std::endl;

    timerFinish->stop();
    std::cout << "Dung timer trong ham finishprocess " << std::endl;
}

void MainWindow::on_slider_Speed_Picking_valueChanged(int value)
{
    if (value == 1)
    {
        ui->lb_Speed_Picking->setText("Very low");
        Speed_Picking = 80;
    }
    else if (value == 2)
    {
        ui->lb_Speed_Picking->setText("Low");
        Speed_Picking = 120;
    }
    else if (value == 3)
    {
        ui->lb_Speed_Picking->setText("Medium");
        Speed_Picking = 200;
    }
    else if (value == 4)
    {
        ui->lb_Speed_Picking->setText("High");
        Speed_Picking = 250;
    }
}

//******************************************Thêm sau sau *******************************************
void MainWindow::on_btn_GetPitch_clicked()
{

    //    PCAimage = PCA(convertQImagetoMat(PCAimage_main));
    //    cv::Mat Tsai,Park,Horaud,Daniilidis,Andreff;
    //    cv::Mat target2cam = cv::Mat::eye(4,4,CV_64F);
    //    cv::Mat Check;
    //    readResultTextFile("Result/Result Test.txt",Tsai,Park,Horaud,Daniilidis,Andreff); //co duoc ma tran Park
    //    camera->getDistance(u,v); //lấy khoảng cách đến tâm, u v là biến global, trả về giá trị tại biến distance

    //    cv::Mat pixel(4,1,CV_64F);
    //    cv::Mat In;
    //    cv::Mat Ex;
    //    cv::Mat temp;
    //    cv::Mat Matrix = cv::Mat::eye(4,4,CV_64F);
    //    cv::Mat Result;
    //    double depth = distance;
    //    std::cout << "distance: " << distance <<" length:"<<lengthOfBold << " width:" << widthOfBold << std::endl;

    //    if(distance > 0.361){
    //        distance = 0.361;
    //    }
    //    pixel.at<double>(0,0) = u*depth;
    //    pixel.at<double>(1,0) = v*depth;
    //    pixel.at<double>(2,0) = 1*depth;
    //    pixel.at<double>(3,0) = 1;

    //    camera->cameraMatrix.copyTo(In);//lấy hàm ma trận nội từ camera, được lấy từ thư viện có sẵn
    //    Ex = Park(cv::Rect(0,0,4,3));

    //    temp = In*Ex;

    //    temp.copyTo(Matrix(cv::Rect(0,0,4,3)));

    //    Result = Matrix.inv()*pixel;
    //    // get coordinate offset point
    //    cv::Mat offset_point;
    //    camera->getDistance(u_offset,v_offset);
    //    //ui->distance_offsetPoint->setText(QString::number(distance));
    //    double depth_offset;

    //    depth_offset = distance;
    //    //std::cout << "distance = " << distance << std::endl;
    //    pixel.at<double>(0,0) = u_offset*depth_offset;
    //    pixel.at<double>(1,0) = v_offset*depth_offset;
    //    pixel.at<double>(2,0) = 1*depth_offset;
    //    pixel.at<double>(3,0) = 1;

    //    offset_point = Matrix.inv()*pixel;

    //    // Calculate vertical angle
    //    double d = sqrt(pow(Result.at<double>(0,0) - offset_point.at<double>(0,0),2)+pow(Result.at<double>(1,0) - offset_point.at<double>(1,0),2));
    //    double vertical_angle = atan(((depth_offset-depth))/d)*180/CV_PI;
    //    ui->lb_DistanceCenter->setText(QString::number(depth));
    //    ui->lb_DistanceOffset->setText(QString::number(depth_offset));
    //    ui->lb_PitchTest->setText(QString::number(vertical_angle));
    //    ui->lb_lengthOfBold->setText(QString::number(lengthOfBold));
    //    ui->lb_WidthOfBold->setText(QString::number(widthOfBold));

    //    emit sendPCArequest(0);

}

void MainWindow::TotalTimeClock()
{
    totalTime++;
    ui->lbTimeTotal->setText(QString::number(totalTime) + " s");
}

