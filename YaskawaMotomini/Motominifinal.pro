#-------------------------------------------------
#
# Project created by QtCreator 2019-10-23T14:34:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = motomini
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _AMD_
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        camera.cpp \
        main.cpp \
        mainwindow.cpp \
        servocontrol.cpp \
        udp.cpp \
        updaterobotposition.cpp \
        yolov5.cpp \
        yrc1000micro_com.cpp \
        yrc1000micro_command.cpp

HEADERS += \
        camera.h \
        mainwindow.h \
        servocontrol.h \
        stdc++.h \
        udp.h \
        updaterobotposition.h \
        yolov5.h \
        yrc1000micro_com.h \
        yrc1000micro_command.h

FORMS += \
        mainwindow.ui

#LIBS += -L$$PWD/../assimp-3.3.1/lib/ -lassimp-vc140-mt
#LIBS+= -lopengl32
#INCLUDEPATH += $$PWD/../assimp-3.3.1/include
#DEPENDPATH += $$PWD/../assimp-3.3.1/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders.qrc

#OpenCV 4.7.0 (debug)
INCLUDEPATH += C:\OpenCV470\build\install\include
DEPENDPATH += C:\OpenCV470\build\install\include

LIBS += -LC:\OpenCV470\build\install\x64\vc16\lib \
        -lopencv_aruco470d  \
        -lopencv_bgsegm470d \
        -lopencv_bioinspired470d  \
        -lopencv_calib3d470d  \
        -lopencv_ccalib470d \
        -lopencv_core470d \
        -lopencv_cudaarithm470d \
        -lopencv_cudabgsegm470d \
        -lopencv_cudacodec470d  \
        -lopencv_cudafeatures2d470d \
        -lopencv_cudafilters470d  \
        -lopencv_cudaimgproc470d  \
        -lopencv_cudalegacy470d \
        -lopencv_cudaobjdetect470d  \
        -lopencv_cudaoptflow470d  \
        -lopencv_cudastereo470d \
        -lopencv_cudawarping470d  \
        -lopencv_cudev470d  \
        -lopencv_cvv470d  \
        -lopencv_datasets470d \
        -lopencv_dnn470d  \
        -lopencv_dnn_objdetect470d  \
        -lopencv_dnn_superres470d \
        -lopencv_dpm470d  \
        -lopencv_face470d \
        -lopencv_features2d470d \
        -lopencv_flann470d  \
        -lopencv_fuzzy470d  \
        -lopencv_gapi470d \
        -lopencv_hfs470d  \
        -lopencv_highgui470d  \
        -lopencv_imgcodecs470d  \
        -lopencv_imgproc470d  \
        -lopencv_img_hash470d \
        -lopencv_intensity_transform470d  \
        -lopencv_line_descriptor470d  \
        -lopencv_mcc470d  \
        -lopencv_ml470d \
        -lopencv_objdetect470d  \
        -lopencv_optflow470d  \
        -lopencv_phase_unwrapping470d \
        -lopencv_photo470d  \
        -lopencv_plot470d \
        -lopencv_quality470d  \
        -lopencv_rapid470d  \
        -lopencv_reg470d  \
        -lopencv_rgbd470d \
        -lopencv_saliency470d \
        -lopencv_shape470d  \
        -lopencv_stereo470d \
        -lopencv_stitching470d  \
        -lopencv_structured_light470d \
        -lopencv_superres470d \
        -lopencv_surface_matching470d \
        -lopencv_text470d \
        -lopencv_tracking470d \
        -lopencv_video470d  \
        -lopencv_videoio470d  \
        -lopencv_videostab470d  \
        -lopencv_wechat_qrcode470d  \
        -lopencv_xfeatures2d470d  \
        -lopencv_ximgproc470d \
        -lopencv_xobjdetect470d \
        -lopencv_xphoto470d \


#Realsense
win32: LIBS += -L'C:/Program Files (x86)/Intel RealSense SDK 2.0/lib/x64/' -lrealsense2

INCLUDEPATH += 'C:/Program Files (x86)/Intel RealSense SDK 2.0/include'
DEPENDPATH += 'C:/Program Files (x86)/Intel RealSense SDK 2.0/include'

#Armadillo
INCLUDEPATH += C:\armadillo\include
LIBS += \
    -LC:\armadillo\examples\lib_win64 \
    -llibopenblas
