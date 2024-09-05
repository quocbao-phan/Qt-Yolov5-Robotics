#ifndef UPDATEROBOTPOSITION_H
#define UPDATEROBOTPOSITION_H

#include <QThread>
#include <QTimer>
#include <iostream>
#include "yrc1000micro_com.h"
class updateRobotPosition : public QThread
{
    Q_OBJECT
public:
    explicit updateRobotPosition(QObject *parent = nullptr);
protected:
    void run();
private slots:
    void timerCallback();

    void positionUpdate();

    void positionUpdatePulse();

    void updateUICallback();

    void ConnectClickTimerStart(bool flag);

    void textIpReceive(QString ip, short port_rcv, short fileport_rcv);
signals:
    void askForTextIp();

    void setGetLabel(QString x, QString y, QString z, QString roll, QString pitch, QString yaw);

    void setGetPulseLabel(QString s, QString l, QString u, QString r, QString b, QString t);

    void setGetVariLabel(QString s, QString l, QString u, QString r, QString b, QString t);

    void setLabelRun(QString text);
private:
    QTimer timerStatus;
    QTimer timerPos;
    QTimer timerPosPulse;
    YRC1000micro_com yrc100micro_com_update;

    QString txt_ip;
    short port;
    short fileport;
};

#endif // UPDATEROBOTPOSITION_H
