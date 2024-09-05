#include "updaterobotposition.h"

updateRobotPosition::updateRobotPosition(QObject *parent)
    : QThread{parent}
{

}

void updateRobotPosition::run()
{
    qDebug()<< "Thread Update Robot Position is Running";
    connect(&timerStatus,SIGNAL(timeout()),this,SLOT(timerCallback()));
    connect(&yrc100micro_com_update, SIGNAL(dataUIRecieveSiUIgnal()),this, SLOT(updateUICallback()));
    connect(&timerPos, SIGNAL(timeout()), this, SLOT(positionUpdate()));
    connect(&timerPosPulse, SIGNAL(timeout()), this, SLOT(positionUpdatePulse()));
}

void updateRobotPosition::timerCallback()
{
    yrc100micro_com_update.YRC1000microReadStatus();
}

void updateRobotPosition::positionUpdate()
{
    yrc100micro_com_update.YRC1000microReadPosition();
}

void updateRobotPosition::positionUpdatePulse()
{
    yrc100micro_com_update.YRC1000microReadPositionPusle();
}

void updateRobotPosition::updateUICallback()
{
    // Update text
    QVector<double> position = yrc100micro_com_update.updateRobotPosition();
    emit setGetLabel(QString::number(position[0]), QString::number(position[1]), QString::number(position[2]),
                    QString::number(position[3]), QString::number(position[4]), QString::number(position[5]));
    quint16 status_code = yrc100micro_com_update.updateRobotStatus();
    status_code &= RES_VALUE_READING_RUNNING_MASK;
    if(status_code)
    {
        emit setLabelRun("Running");
    }
    else
    {
        emit setLabelRun("Stop");
    }
    // Update 3D Robot
    QVector<double> position_pulse = yrc100micro_com_update.updateRobotPositionPulse();
    emit setGetPulseLabel(QString::number(position_pulse[0]), QString::number(position_pulse[1]), QString::number(position_pulse[2]),
                    QString::number(position_pulse[3]), QString::number(position_pulse[4]), QString::number(position_pulse[5]));
}

void updateRobotPosition::ConnectClickTimerStart(bool flag)
{
    if (flag)
    {
        //      UDP connect
        QHostAddress udp_address;
        quint16 udp_port;
        quint16 udp_file_port;
        emit askForTextIp();
        QString ip_string = txt_ip;
        QStringList ip_list = ip_string.split(".");
        quint32 ip_int32 = (ip_list.at(0).toUInt() << 24) | (ip_list.at(1).toUInt() << 16)
                | (ip_list.at(2).toUInt() << 8) | ip_list.at(3).toUInt();
        udp_address.setAddress(ip_int32);
        udp_port = port;
        udp_file_port = fileport;
        yrc100micro_com_update.YRC1000microSetConnection(udp_address,udp_port,udp_file_port);
        bool connection_satus = yrc100micro_com_update.YRC1000microConnect();
        //  UDP connect done
        timerStatus.start(100);
        timerPos.start(140);
        timerPosPulse.start(120);

    }
    else
    {
        yrc100micro_com_update.YRC1000microDisConnect();
        timerStatus.stop();
        timerPos.stop();
        timerPosPulse.stop();
    }
}

void updateRobotPosition::textIpReceive(QString ip, short port_rcv, short fileport_rcv)
{
    txt_ip = ip;
    port = port_rcv;
    fileport = fileport_rcv;
}


