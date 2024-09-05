#ifndef YRC1000MICRO_COM_H
#define YRC1000MICRO_COM_H

#include <QObject>
#include <QFile>
#include "udp.h"
#include "yrc1000micro_command.h"

class YRC1000micro_com : public QObject
{
    Q_OBJECT
public:
    explicit YRC1000micro_com(QObject *parent = nullptr);
    ~YRC1000micro_com();
    bool YRC1000microConnect();
    void YRC1000microDisConnect();
    bool YRC1000microFileTransferConnect();
    void YRC1000microFileTransferDisConnect();
    void YRC1000microSetConnection(QHostAddress address,quint16 port,quint16 file_port);
    void YRC1000microOnServo();
    void YRC1000microOffServo();
    void YRC1000microReadPosition();
    void YRC1000microReadPositionPusle();
    void YRC1000microReadPositionResponse(QByteArray data);
    void YRC1000microReadPositionResponsePulse(QByteArray data);
    void YRC1000microMoveCartesian(quint8 coordinate,quint8 move_type,
          quint8 speed_type, double speed, QVector<double>* position);
    void YRC1000microMovePulse(double speed, QVector<double>* position);
    void YRC1000microMoveJog(double speed, QVector<double>* position);

    QVector<double> updateRobotPosition();
    //
    QVector<double> updateRobotPositionPulse();
    //
    QVector<double> updateRobotPositionVariable();

    void YRC1000microReadStatus();
    void YRC1000microReadStatusResponse(QByteArray data);
    quint16 updateRobotStatus();

    void YRC1000microSaveJob(quint32 block_num,QString send_data);
    quint32 YRC1000microSaveJobResponse(QByteArray data);

    void YRC1000microLoadJob(QString send_data);
    quint32 YRC1000microLoadJobResponse(QByteArray data, quint32 block_num);

    void YRC1000microReadRobotVariable(int variableNumber, int dataType);
    void YRC1000microReadRobotVariableResponse(QByteArray data);

    void YRC1000microSaveRobotVariable(int variableNumber, int dataType, double x, double y, double z, double roll, double pitch, double yaw);

    QVector<double> robot_position_variable;
signals:
    void dataUIRecieveSiUIgnal();

    void readRobotVari();
public slots:
    void YRC1000microDataCallback();

private:
    UDP udp_server;
    UDP udp_file_control;
    YRC1000micro_command yrc1000micro_command;

    quint8 request_id_index;
    quint8 response_id_index;
    char request_code[256] = {};

    QHostAddress udp_address;
    quint16 udp_port;

    quint16 udp_file_port;

    QByteArray header_to_send;
    QByteArray data_to_send;
    QVector<double> robot_position;
    QVector<double> robot_position_pulse;


    quint16 status_code;
    QString str_load_file;
    quint32 load_file_block_num;
    bool load_data_status;


};

#endif // YRC1000MICRO_COM_H
