/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lbLogoHCMUT_2;
    QGroupBox *groupBox_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioRGB;
    QRadioButton *radioDepth;
    QLabel *label_60;
    QComboBox *cbFPS;
    QLabel *label_59;
    QPushButton *btnStart;
    QComboBox *cbResolution;
    QPushButton *btnDetect;
    QGroupBox *groupBox_4;
    QSlider *slider_Speed_Picking;
    QLabel *lb_Speed_Picking;
    QPushButton *btnStartProcess;
    QGroupBox *groupBox_test;
    QLabel *lb_WidthOfBold;
    QLabel *lb_PitchTest;
    QLabel *lb_lengthOfBold;
    QPushButton *btn_GetPitch;
    QLabel *lb_PitchTest_4;
    QLabel *lb_PitchTest_5;
    QLabel *lb_PitchTest_6;
    QWidget *gridLayoutWidget_11;
    QGridLayout *gridLayout_9;
    QLabel *label_53;
    QLabel *lb_DistanceCenter;
    QLabel *label_51;
    QLabel *lb_DistanceOffset;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_7;
    QLineEdit *timer;
    QLabel *label_36;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_45;
    QLineEdit *txt_homeSpeed;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_33;
    QLabel *lb_run_status;
    QGroupBox *MainDisplay;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_35;
    QLabel *displayRGB;
    QLabel *displayDepth;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_34;
    QLabel *statusDisplay;
    QLabel *statusMode;
    QGroupBox *groupBox_6;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLineEdit *txt_port;
    QLabel *label_2;
    QLineEdit *txt_ip;
    QLabel *label_3;
    QLineEdit *txt_filePort;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_connect;
    QPushButton *btn_servo;
    QPushButton *btn_Home;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_5;
    QLabel *label_29;
    QLabel *label_5;
    QLineEdit *txt_getY;
    QLabel *label_6;
    QLabel *label_30;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_32;
    QLineEdit *txt_getZ;
    QLineEdit *txt_getRoll;
    QLabel *label_27;
    QLabel *label_28;
    QLineEdit *txt_getX;
    QLineEdit *txt_getPitch;
    QLabel *label_10;
    QLineEdit *txt_getYaw;
    QLabel *label_31;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QLabel *label_47;
    QLabel *label_48;
    QComboBox *comboBox_COM;
    QLabel *lb_StatusServo_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btn_ConnectServo;
    QLabel *lb_StatusServo;
    QSlider *slider_Servo;
    QLabel *lbLogoDepartment;
    QGroupBox *YoloDetection;
    QLabel *displayYoloDectect;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_20;
    QLabel *timeProcessYolo;
    QLabel *fpsDetect;
    QLabel *numDetect;
    QGroupBox *groupBox_7;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_6;
    QLineEdit *txt_getB;
    QLineEdit *txt_getU;
    QLabel *label_37;
    QLineEdit *txt_getL;
    QLineEdit *txt_getS;
    QLineEdit *txt_getR;
    QLabel *label_38;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_39;
    QLabel *label_42;
    QLineEdit *txt_getT;
    QGroupBox *groupBox_8;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_3;
    QLabel *lbTimeTotal;
    QLabel *label_11;
    QLabel *label_4;
    QLabel *lbTimeProcessing;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1700, 964);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lbLogoHCMUT_2 = new QLabel(centralWidget);
        lbLogoHCMUT_2->setObjectName(QString::fromUtf8("lbLogoHCMUT_2"));
        lbLogoHCMUT_2->setGeometry(QRect(680, 0, 550, 80));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 210, 331, 181));
        gridLayoutWidget = new QWidget(groupBox_5);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 311, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioRGB = new QRadioButton(gridLayoutWidget);
        radioRGB->setObjectName(QString::fromUtf8("radioRGB"));

        gridLayout->addWidget(radioRGB, 2, 0, 1, 1);

        radioDepth = new QRadioButton(gridLayoutWidget);
        radioDepth->setObjectName(QString::fromUtf8("radioDepth"));

        gridLayout->addWidget(radioDepth, 2, 1, 1, 1);

        label_60 = new QLabel(gridLayoutWidget);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout->addWidget(label_60, 1, 0, 1, 1);

        cbFPS = new QComboBox(gridLayoutWidget);
        cbFPS->setObjectName(QString::fromUtf8("cbFPS"));

        gridLayout->addWidget(cbFPS, 1, 1, 1, 1);

        label_59 = new QLabel(gridLayoutWidget);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout->addWidget(label_59, 0, 0, 1, 1);

        btnStart = new QPushButton(gridLayoutWidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));

        gridLayout->addWidget(btnStart, 3, 0, 1, 1);

        cbResolution = new QComboBox(gridLayoutWidget);
        cbResolution->setObjectName(QString::fromUtf8("cbResolution"));

        gridLayout->addWidget(cbResolution, 0, 1, 1, 1);

        btnDetect = new QPushButton(gridLayoutWidget);
        btnDetect->setObjectName(QString::fromUtf8("btnDetect"));

        gridLayout->addWidget(btnDetect, 3, 1, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 610, 331, 101));
        slider_Speed_Picking = new QSlider(groupBox_4);
        slider_Speed_Picking->setObjectName(QString::fromUtf8("slider_Speed_Picking"));
        slider_Speed_Picking->setGeometry(QRect(110, 70, 201, 20));
        slider_Speed_Picking->setMinimum(1);
        slider_Speed_Picking->setMaximum(4);
        slider_Speed_Picking->setOrientation(Qt::Horizontal);
        lb_Speed_Picking = new QLabel(groupBox_4);
        lb_Speed_Picking->setObjectName(QString::fromUtf8("lb_Speed_Picking"));
        lb_Speed_Picking->setGeometry(QRect(18, 69, 81, 20));
        btnStartProcess = new QPushButton(groupBox_4);
        btnStartProcess->setObjectName(QString::fromUtf8("btnStartProcess"));
        btnStartProcess->setEnabled(false);
        btnStartProcess->setGeometry(QRect(10, 30, 311, 29));
        groupBox_test = new QGroupBox(centralWidget);
        groupBox_test->setObjectName(QString::fromUtf8("groupBox_test"));
        groupBox_test->setGeometry(QRect(1020, 780, 451, 91));
        lb_WidthOfBold = new QLabel(groupBox_test);
        lb_WidthOfBold->setObjectName(QString::fromUtf8("lb_WidthOfBold"));
        lb_WidthOfBold->setGeometry(QRect(420, 30, 141, 41));
        lb_WidthOfBold->setFrameShape(QFrame::Panel);
        lb_WidthOfBold->setAlignment(Qt::AlignCenter);
        lb_PitchTest = new QLabel(groupBox_test);
        lb_PitchTest->setObjectName(QString::fromUtf8("lb_PitchTest"));
        lb_PitchTest->setGeometry(QRect(80, 30, 161, 41));
        lb_PitchTest->setFrameShape(QFrame::Panel);
        lb_PitchTest->setAlignment(Qt::AlignCenter);
        lb_lengthOfBold = new QLabel(groupBox_test);
        lb_lengthOfBold->setObjectName(QString::fromUtf8("lb_lengthOfBold"));
        lb_lengthOfBold->setGeometry(QRect(250, 30, 161, 41));
        lb_lengthOfBold->setFrameShape(QFrame::Panel);
        lb_lengthOfBold->setAlignment(Qt::AlignCenter);
        btn_GetPitch = new QPushButton(groupBox_test);
        btn_GetPitch->setObjectName(QString::fromUtf8("btn_GetPitch"));
        btn_GetPitch->setGeometry(QRect(0, 30, 71, 41));
        lb_PitchTest_4 = new QLabel(groupBox_test);
        lb_PitchTest_4->setObjectName(QString::fromUtf8("lb_PitchTest_4"));
        lb_PitchTest_4->setGeometry(QRect(80, 80, 161, 41));
        lb_PitchTest_4->setFrameShape(QFrame::Panel);
        lb_PitchTest_4->setAlignment(Qt::AlignCenter);
        lb_PitchTest_5 = new QLabel(groupBox_test);
        lb_PitchTest_5->setObjectName(QString::fromUtf8("lb_PitchTest_5"));
        lb_PitchTest_5->setGeometry(QRect(250, 80, 161, 41));
        lb_PitchTest_5->setFrameShape(QFrame::Panel);
        lb_PitchTest_5->setAlignment(Qt::AlignCenter);
        lb_PitchTest_6 = new QLabel(groupBox_test);
        lb_PitchTest_6->setObjectName(QString::fromUtf8("lb_PitchTest_6"));
        lb_PitchTest_6->setGeometry(QRect(420, 80, 141, 41));
        lb_PitchTest_6->setFrameShape(QFrame::Panel);
        lb_PitchTest_6->setAlignment(Qt::AlignCenter);
        gridLayoutWidget_11 = new QWidget(groupBox_test);
        gridLayoutWidget_11->setObjectName(QString::fromUtf8("gridLayoutWidget_11"));
        gridLayoutWidget_11->setGeometry(QRect(100, 160, 331, 71));
        gridLayout_9 = new QGridLayout(gridLayoutWidget_11);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        label_53 = new QLabel(gridLayoutWidget_11);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setFrameShape(QFrame::Panel);
        label_53->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_53, 0, 0, 1, 1);

        lb_DistanceCenter = new QLabel(gridLayoutWidget_11);
        lb_DistanceCenter->setObjectName(QString::fromUtf8("lb_DistanceCenter"));
        lb_DistanceCenter->setFrameShape(QFrame::Panel);
        lb_DistanceCenter->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lb_DistanceCenter, 0, 1, 1, 1);

        label_51 = new QLabel(gridLayoutWidget_11);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setFrameShape(QFrame::Panel);
        label_51->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_51, 1, 0, 1, 1);

        lb_DistanceOffset = new QLabel(gridLayoutWidget_11);
        lb_DistanceOffset->setObjectName(QString::fromUtf8("lb_DistanceOffset"));
        lb_DistanceOffset->setFrameShape(QFrame::Panel);
        lb_DistanceOffset->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(lb_DistanceOffset, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 720, 331, 171));
        gridLayoutWidget_6 = new QWidget(groupBox_3);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(10, 30, 311, 94));
        gridLayout_7 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        timer = new QLineEdit(gridLayoutWidget_6);
        timer->setObjectName(QString::fromUtf8("timer"));
        timer->setFrame(true);
        timer->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(timer, 0, 1, 1, 1);

        label_36 = new QLabel(gridLayoutWidget_6);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setFrameShape(QFrame::Panel);

        gridLayout_7->addWidget(label_36, 1, 0, 1, 1);

        label_34 = new QLabel(gridLayoutWidget_6);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setFrameShape(QFrame::Panel);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_34, 0, 0, 1, 1);

        label_35 = new QLabel(gridLayoutWidget_6);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setFrameShape(QFrame::Panel);
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_35, 0, 2, 1, 1);

        label_45 = new QLabel(gridLayoutWidget_6);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setFrameShape(QFrame::Panel);
        label_45->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_45, 1, 2, 1, 1);

        txt_homeSpeed = new QLineEdit(gridLayoutWidget_6);
        txt_homeSpeed->setObjectName(QString::fromUtf8("txt_homeSpeed"));
        txt_homeSpeed->setFrame(true);
        txt_homeSpeed->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(txt_homeSpeed, 1, 1, 1, 1);

        horizontalLayoutWidget_4 = new QWidget(groupBox_3);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 130, 311, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_33 = new QLabel(horizontalLayoutWidget_4);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setFrameShape(QFrame::Panel);

        horizontalLayout_2->addWidget(label_33);

        lb_run_status = new QLabel(horizontalLayoutWidget_4);
        lb_run_status->setObjectName(QString::fromUtf8("lb_run_status"));
        lb_run_status->setFrameShape(QFrame::Panel);
        lb_run_status->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lb_run_status);

        MainDisplay = new QGroupBox(centralWidget);
        MainDisplay->setObjectName(QString::fromUtf8("MainDisplay"));
        MainDisplay->setGeometry(QRect(350, 80, 661, 561));
        horizontalLayoutWidget_3 = new QWidget(MainDisplay);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 30, 641, 481));
        horizontalLayout_35 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        horizontalLayout_35->setContentsMargins(0, 0, 0, 0);
        displayRGB = new QLabel(horizontalLayoutWidget_3);
        displayRGB->setObjectName(QString::fromUtf8("displayRGB"));
        displayRGB->setFrameShape(QFrame::Box);

        horizontalLayout_35->addWidget(displayRGB);

        displayDepth = new QLabel(horizontalLayoutWidget_3);
        displayDepth->setObjectName(QString::fromUtf8("displayDepth"));
        displayDepth->setFrameShape(QFrame::Box);

        horizontalLayout_35->addWidget(displayDepth);

        horizontalLayoutWidget_2 = new QWidget(MainDisplay);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 530, 661, 31));
        horizontalLayout_34 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(0, 0, 0, 0);
        statusDisplay = new QLabel(horizontalLayoutWidget_2);
        statusDisplay->setObjectName(QString::fromUtf8("statusDisplay"));
        statusDisplay->setFrameShape(QFrame::Panel);
        statusDisplay->setAlignment(Qt::AlignCenter);

        horizontalLayout_34->addWidget(statusDisplay);

        statusMode = new QLabel(horizontalLayoutWidget_2);
        statusMode->setObjectName(QString::fromUtf8("statusMode"));
        statusMode->setFrameShape(QFrame::Panel);
        statusMode->setAlignment(Qt::AlignCenter);

        horizontalLayout_34->addWidget(statusMode);

        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 20, 331, 181));
        gridLayoutWidget_3 = new QWidget(groupBox_6);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 30, 311, 100));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFrameShape(QFrame::Panel);

        gridLayout_4->addWidget(label, 1, 0, 1, 1);

        txt_port = new QLineEdit(gridLayoutWidget_3);
        txt_port->setObjectName(QString::fromUtf8("txt_port"));
        txt_port->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(txt_port, 1, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFrameShape(QFrame::Panel);

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        txt_ip = new QLineEdit(gridLayoutWidget_3);
        txt_ip->setObjectName(QString::fromUtf8("txt_ip"));
        txt_ip->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(txt_ip, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFrameShape(QFrame::Panel);

        gridLayout_4->addWidget(label_3, 2, 0, 1, 1);

        txt_filePort = new QLineEdit(gridLayoutWidget_3);
        txt_filePort->setObjectName(QString::fromUtf8("txt_filePort"));
        txt_filePort->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(txt_filePort, 2, 1, 1, 1);

        horizontalLayoutWidget_5 = new QWidget(groupBox_6);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 130, 311, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        btn_connect = new QPushButton(horizontalLayoutWidget_5);
        btn_connect->setObjectName(QString::fromUtf8("btn_connect"));
        btn_connect->setAutoFillBackground(true);

        horizontalLayout_3->addWidget(btn_connect);

        btn_servo = new QPushButton(horizontalLayoutWidget_5);
        btn_servo->setObjectName(QString::fromUtf8("btn_servo"));

        horizontalLayout_3->addWidget(btn_servo);

        btn_Home = new QPushButton(horizontalLayoutWidget_5);
        btn_Home->setObjectName(QString::fromUtf8("btn_Home"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_Home->sizePolicy().hasHeightForWidth());
        btn_Home->setSizePolicy(sizePolicy);
        btn_Home->setMaximumSize(QSize(10000, 16777215));
        btn_Home->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(btn_Home);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(350, 650, 291, 241));
        gridLayoutWidget_4 = new QWidget(groupBox_2);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(10, 34, 271, 205));
        gridLayout_5 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_29 = new QLabel(gridLayoutWidget_4);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setFrameShape(QFrame::Panel);

        gridLayout_5->addWidget(label_29, 0, 2, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFrameShape(QFrame::Panel);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        txt_getY = new QLineEdit(gridLayoutWidget_4);
        txt_getY->setObjectName(QString::fromUtf8("txt_getY"));
        txt_getY->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(txt_getY, 1, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFrameShape(QFrame::Panel);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_6, 1, 0, 1, 1);

        label_30 = new QLabel(gridLayoutWidget_4);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setFrameShape(QFrame::Panel);

        gridLayout_5->addWidget(label_30, 4, 2, 1, 1);

        label_9 = new QLabel(gridLayoutWidget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFrameShape(QFrame::Panel);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_9, 4, 0, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFrameShape(QFrame::Panel);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_7, 2, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFrameShape(QFrame::Panel);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_8, 3, 0, 1, 1);

        label_32 = new QLabel(gridLayoutWidget_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setFrameShape(QFrame::Panel);

        gridLayout_5->addWidget(label_32, 2, 2, 1, 1);

        txt_getZ = new QLineEdit(gridLayoutWidget_4);
        txt_getZ->setObjectName(QString::fromUtf8("txt_getZ"));
        txt_getZ->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(txt_getZ, 2, 1, 1, 1);

        txt_getRoll = new QLineEdit(gridLayoutWidget_4);
        txt_getRoll->setObjectName(QString::fromUtf8("txt_getRoll"));
        txt_getRoll->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(txt_getRoll, 3, 1, 1, 1);

        label_27 = new QLabel(gridLayoutWidget_4);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFrameShape(QFrame::Panel);

        gridLayout_5->addWidget(label_27, 3, 2, 1, 1);

        label_28 = new QLabel(gridLayoutWidget_4);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setFrameShape(QFrame::Panel);

        gridLayout_5->addWidget(label_28, 1, 2, 1, 1);

        txt_getX = new QLineEdit(gridLayoutWidget_4);
        txt_getX->setObjectName(QString::fromUtf8("txt_getX"));
        txt_getX->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(txt_getX, 0, 1, 1, 1);

        txt_getPitch = new QLineEdit(gridLayoutWidget_4);
        txt_getPitch->setObjectName(QString::fromUtf8("txt_getPitch"));
        txt_getPitch->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(txt_getPitch, 4, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFrameShape(QFrame::Panel);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(label_10, 5, 0, 1, 1);

        txt_getYaw = new QLineEdit(gridLayoutWidget_4);
        txt_getYaw->setObjectName(QString::fromUtf8("txt_getYaw"));
        txt_getYaw->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(txt_getYaw, 5, 1, 1, 1);

        label_31 = new QLabel(gridLayoutWidget_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setFrameShape(QFrame::Panel);

        gridLayout_5->addWidget(label_31, 5, 2, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 400, 331, 201));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 309, 61));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_47 = new QLabel(layoutWidget);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_2->addWidget(label_47, 1, 0, 1, 1);

        label_48 = new QLabel(layoutWidget);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_2->addWidget(label_48, 0, 0, 1, 1);

        comboBox_COM = new QComboBox(layoutWidget);
        comboBox_COM->setObjectName(QString::fromUtf8("comboBox_COM"));

        gridLayout_2->addWidget(comboBox_COM, 0, 1, 1, 1);

        lb_StatusServo_2 = new QLabel(layoutWidget);
        lb_StatusServo_2->setObjectName(QString::fromUtf8("lb_StatusServo_2"));
        lb_StatusServo_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lb_StatusServo_2, 1, 1, 1, 1);

        layoutWidget_2 = new QWidget(groupBox);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 100, 311, 91));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        btn_ConnectServo = new QPushButton(layoutWidget_2);
        btn_ConnectServo->setObjectName(QString::fromUtf8("btn_ConnectServo"));

        verticalLayout_4->addWidget(btn_ConnectServo);

        lb_StatusServo = new QLabel(layoutWidget_2);
        lb_StatusServo->setObjectName(QString::fromUtf8("lb_StatusServo"));
        lb_StatusServo->setFrameShape(QFrame::Box);

        verticalLayout_4->addWidget(lb_StatusServo);

        slider_Servo = new QSlider(layoutWidget_2);
        slider_Servo->setObjectName(QString::fromUtf8("slider_Servo"));
        slider_Servo->setEnabled(true);
        slider_Servo->setMaximum(100);
        slider_Servo->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(slider_Servo);

        lbLogoDepartment = new QLabel(centralWidget);
        lbLogoDepartment->setObjectName(QString::fromUtf8("lbLogoDepartment"));
        lbLogoDepartment->setGeometry(QRect(1240, -10, 111, 101));
        YoloDetection = new QGroupBox(centralWidget);
        YoloDetection->setObjectName(QString::fromUtf8("YoloDetection"));
        YoloDetection->setGeometry(QRect(1020, 80, 661, 561));
        displayYoloDectect = new QLabel(YoloDetection);
        displayYoloDectect->setObjectName(QString::fromUtf8("displayYoloDectect"));
        displayYoloDectect->setGeometry(QRect(10, 30, 640, 480));
        displayYoloDectect->setFrameShape(QFrame::Box);
        horizontalLayoutWidget = new QWidget(YoloDetection);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 530, 661, 31));
        horizontalLayout_20 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        timeProcessYolo = new QLabel(horizontalLayoutWidget);
        timeProcessYolo->setObjectName(QString::fromUtf8("timeProcessYolo"));
        timeProcessYolo->setFrameShape(QFrame::Panel);
        timeProcessYolo->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(timeProcessYolo);

        fpsDetect = new QLabel(horizontalLayoutWidget);
        fpsDetect->setObjectName(QString::fromUtf8("fpsDetect"));
        fpsDetect->setFrameShape(QFrame::Panel);
        fpsDetect->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(fpsDetect);

        numDetect = new QLabel(horizontalLayoutWidget);
        numDetect->setObjectName(QString::fromUtf8("numDetect"));
        numDetect->setFrameShape(QFrame::Panel);
        numDetect->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(numDetect);

        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(680, 650, 321, 241));
        gridLayoutWidget_5 = new QWidget(groupBox_7);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(10, 30, 301, 205));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        txt_getB = new QLineEdit(gridLayoutWidget_5);
        txt_getB->setObjectName(QString::fromUtf8("txt_getB"));
        txt_getB->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(txt_getB, 4, 1, 1, 1);

        txt_getU = new QLineEdit(gridLayoutWidget_5);
        txt_getU->setObjectName(QString::fromUtf8("txt_getU"));
        txt_getU->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(txt_getU, 2, 1, 1, 1);

        label_37 = new QLabel(gridLayoutWidget_5);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setFrameShape(QFrame::Panel);
        label_37->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_37, 0, 0, 1, 1);

        txt_getL = new QLineEdit(gridLayoutWidget_5);
        txt_getL->setObjectName(QString::fromUtf8("txt_getL"));
        txt_getL->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(txt_getL, 1, 1, 1, 1);

        txt_getS = new QLineEdit(gridLayoutWidget_5);
        txt_getS->setObjectName(QString::fromUtf8("txt_getS"));
        txt_getS->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(txt_getS, 0, 1, 1, 1);

        txt_getR = new QLineEdit(gridLayoutWidget_5);
        txt_getR->setObjectName(QString::fromUtf8("txt_getR"));
        txt_getR->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(txt_getR, 3, 1, 1, 1);

        label_38 = new QLabel(gridLayoutWidget_5);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setFrameShape(QFrame::Panel);
        label_38->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_38, 1, 0, 1, 1);

        label_40 = new QLabel(gridLayoutWidget_5);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setFrameShape(QFrame::Panel);
        label_40->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_40, 3, 0, 1, 1);

        label_41 = new QLabel(gridLayoutWidget_5);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setFrameShape(QFrame::Panel);
        label_41->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_41, 4, 0, 1, 1);

        label_39 = new QLabel(gridLayoutWidget_5);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setFrameShape(QFrame::Panel);
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_39, 2, 0, 1, 1);

        label_42 = new QLabel(gridLayoutWidget_5);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setFrameShape(QFrame::Panel);
        label_42->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_42, 5, 0, 1, 1);

        txt_getT = new QLineEdit(gridLayoutWidget_5);
        txt_getT->setObjectName(QString::fromUtf8("txt_getT"));
        txt_getT->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(txt_getT, 5, 1, 1, 1);

        groupBox_8 = new QGroupBox(centralWidget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(1020, 650, 661, 111));
        gridLayoutWidget_2 = new QWidget(groupBox_8);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 30, 641, 71));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        lbTimeTotal = new QLabel(gridLayoutWidget_2);
        lbTimeTotal->setObjectName(QString::fromUtf8("lbTimeTotal"));
        lbTimeTotal->setFrameShape(QFrame::Box);
        lbTimeTotal->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbTimeTotal, 1, 1, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFrameShape(QFrame::Box);

        gridLayout_3->addWidget(label_11, 1, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFrameShape(QFrame::Box);

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        lbTimeProcessing = new QLabel(gridLayoutWidget_2);
        lbTimeProcessing->setObjectName(QString::fromUtf8("lbTimeProcessing"));
        lbTimeProcessing->setFrameShape(QFrame::Box);
        lbTimeProcessing->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(lbTimeProcessing, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1700, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Motomini Server", nullptr));
        lbLogoHCMUT_2->setText(QCoreApplication::translate("MainWindow", "logo HCMUT", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Intel Realsense Control", nullptr));
        radioRGB->setText(QCoreApplication::translate("MainWindow", "RGB Camera", nullptr));
        radioDepth->setText(QCoreApplication::translate("MainWindow", "Depth Camera", nullptr));
        label_60->setText(QCoreApplication::translate("MainWindow", "FPS", nullptr));
        label_59->setText(QCoreApplication::translate("MainWindow", "Resolution", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        btnDetect->setText(QCoreApplication::translate("MainWindow", "DETECT", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Picking", nullptr));
        lb_Speed_Picking->setText(QCoreApplication::translate("MainWindow", "Speed:", nullptr));
        btnStartProcess->setText(QCoreApplication::translate("MainWindow", "START PROCESS", nullptr));
        groupBox_test->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        lb_WidthOfBold->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        lb_PitchTest->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        lb_lengthOfBold->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        btn_GetPitch->setText(QCoreApplication::translate("MainWindow", "GetPitch", nullptr));
        lb_PitchTest_4->setText(QCoreApplication::translate("MainWindow", "Pitch", nullptr));
        lb_PitchTest_5->setText(QCoreApplication::translate("MainWindow", "length", nullptr));
        lb_PitchTest_6->setText(QCoreApplication::translate("MainWindow", "width", nullptr));
        label_53->setText(QCoreApplication::translate("MainWindow", "Distance Center", nullptr));
        lb_DistanceCenter->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "Distance Offset", nullptr));
        lb_DistanceOffset->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Current Status", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Home speed:", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Timer: ", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", " ms ", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", " mm/s ", nullptr));
        txt_homeSpeed->setText(QCoreApplication::translate("MainWindow", "250", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "Robot Status :", nullptr));
        lb_run_status->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        MainDisplay->setTitle(QCoreApplication::translate("MainWindow", "Main Display", nullptr));
        displayRGB->setText(QCoreApplication::translate("MainWindow", "rgb", nullptr));
        displayDepth->setText(QCoreApplication::translate("MainWindow", "depth", nullptr));
        statusDisplay->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        statusMode->setText(QCoreApplication::translate("MainWindow", "RGB mode", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Robot Control", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        txt_port->setText(QCoreApplication::translate("MainWindow", "10040", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP address:", nullptr));
        txt_ip->setText(QCoreApplication::translate("MainWindow", "192.168.1.16", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "File Port:", nullptr));
        txt_filePort->setText(QCoreApplication::translate("MainWindow", "10041", nullptr));
        btn_connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        btn_servo->setText(QCoreApplication::translate("MainWindow", "Servo On", nullptr));
        btn_Home->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Current Position - Robot", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X ", nullptr));
        txt_getY->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Pitch", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", " Roll  ", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        txt_getZ->setText(QString());
        txt_getRoll->setText(QString());
        label_27->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        txt_getX->setText(QString());
        txt_getPitch->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "Yaw", nullptr));
        txt_getYaw->setText(QString());
        label_31->setText(QCoreApplication::translate("MainWindow", "deg", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Serial Setup", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "Baudrate:", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "COM Port:", nullptr));
        lb_StatusServo_2->setText(QCoreApplication::translate("MainWindow", "9600", nullptr));
        btn_ConnectServo->setText(QCoreApplication::translate("MainWindow", "CONNECT", nullptr));
        lb_StatusServo->setText(QString());
        lbLogoDepartment->setText(QCoreApplication::translate("MainWindow", "logo dept", nullptr));
        YoloDetection->setTitle(QCoreApplication::translate("MainWindow", "Yolo Detection", nullptr));
        displayYoloDectect->setText(QString());
        timeProcessYolo->setText(QCoreApplication::translate("MainWindow", "Time", nullptr));
        fpsDetect->setText(QCoreApplication::translate("MainWindow", "FPS", nullptr));
        numDetect->setText(QCoreApplication::translate("MainWindow", "Number of detect", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Current Position - Pulse", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "B", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "    U    ", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "T", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "Processing Time", nullptr));
        lbTimeTotal->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Total time", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Time to pick up 1 bolt", nullptr));
        lbTimeProcessing->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
