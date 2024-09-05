#include "yrc1000micro_com.h"
#include "yrc1000micro_command.h"
#include <iostream>
#include <QMessageBox>


YRC1000micro_com::YRC1000micro_com(QObject *parent) : QObject(parent)
{
    request_id_index = 0;
    response_id_index = 0;
    status_code = 0;
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);
    robot_position.append(0);

    robot_position_pulse.append(0);
    robot_position_pulse.append(0);
    robot_position_pulse.append(0);
    robot_position_pulse.append(0);
    robot_position_pulse.append(0);
    robot_position_pulse.append(0);

    robot_position_variable.append(0);
    robot_position_variable.append(0);
    robot_position_variable.append(0);
    robot_position_variable.append(0);
    robot_position_variable.append(0);
    robot_position_variable.append(0);
    connect(&udp_server, SIGNAL(dataRecieveSignal()), this, SLOT(YRC1000microDataCallback()));
}
YRC1000micro_com::~YRC1000micro_com(){
    udp_server.~UDP();
}

bool YRC1000micro_com::YRC1000microConnect(){
    bool connect_satus = udp_server.udpConnect(udp_address,udp_port);
    return connect_satus;
}

void YRC1000micro_com::YRC1000microDisConnect(){
    udp_server.udpDisConnect();
}

bool YRC1000micro_com::YRC1000microFileTransferConnect(){
    bool connect_satus = udp_file_control.udpConnect(udp_address,udp_file_port);
    return connect_satus;
}

void YRC1000micro_com::YRC1000microFileTransferDisConnect(){
    udp_file_control.udpDisConnect();
}

void YRC1000micro_com::YRC1000microSetConnection(QHostAddress address,quint16 port,quint16 file_port){
    udp_address = address;
    udp_port = port;
    udp_file_port = file_port;
}

void YRC1000micro_com::YRC1000microDataCallback(){
    QByteArray data = udp_server.getUdpData();
    //qDebug() << "Received Data: " << data;

    quint8 res_id_index = (quint8)data[CMD_REQUEST_ID];
    char response_id = request_code[res_id_index];
    //qDebug() << "response_id: " << response_id;
    //
    qint32 dataType = 0;

    quint8 status = (quint8)data[31];

    //qDebug() << "status: " << status;


    if((response_id == CMD_ID_READ_ROBOT_POS))
    {
        dataType = ((quint32)(quint8)data[DATA_TYPE+3])<<24 | ((quint32)(quint8)data[DATA_TYPE+2])<<16 |
                        ((quint32)(quint8)data[DATA_TYPE+1])<<8 | (quint32)(quint8)data[DATA_TYPE];
        if (dataType == 16)
        {
            YRC1000microReadPositionResponse(data);
        }
        else if (dataType == 0)
        {
            YRC1000microReadPositionResponsePulse(data);
        }
    }
    else if(response_id == CMD_ID_STATUS_READING)
    {
        YRC1000microReadStatusResponse(data);
    }
    else if(response_id == CMD_ID_SAVE_JOB_TO_PC)
    {
        YRC1000microSaveJobResponse(data);
    }
    else if(response_id == CMD_ID_LOAD_JOB_TO_YRC)
    {
        load_file_block_num ++;
        qDebug() << "load_file_block_num: " << load_file_block_num;
        YRC1000microLoadJobResponse(data,load_file_block_num);
    }
    else if((response_id == CMD_ID_READ_WRITE_ROBOT_VARIABLE)&&((quint8)data[CMD_SERVICE_REPLY]==(quint8)CMD_HEADER_READ_ROBOT_VARIABLE_SERVICE_REPLY))
    {
        YRC1000microReadRobotVariableResponse(data);
    }
//    else if ()
//    {

//    }
    emit dataUIRecieveSiUIgnal();
}

void YRC1000micro_com::YRC1000microOnServo(){
    QByteArray data = yrc1000micro_command.setServoOn(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_SERVO_ON;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microOffServo(){
    QByteArray data = yrc1000micro_command.setServoOff(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_SERVO_ON;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microReadPosition()
{
    QByteArray data = yrc1000micro_command.readRobotPosition(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_READ_ROBOT_POS;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microReadPositionPusle()
{
    QByteArray data = yrc1000micro_command.readRobotPositionPulse(request_id_index);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_READ_ROBOT_POS;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microReadPositionResponse(QByteArray data)
{
    qint32 x_axis = 0;
    qint32 y_axis = 0;
    qint32 z_axis = 0;
    qint32 roll_angle = 0;
    qint32 pitch_angle = 0;
    qint32 yaw_angle = 0;
    x_axis = ((quint32)(quint8)data[DATA_X_AXIS+3])<<24 | ((quint32)(quint8)data[DATA_X_AXIS+2])<<16 |
                    ((quint32)(quint8)data[DATA_X_AXIS+1])<<8 | (quint32)(quint8)data[DATA_X_AXIS];

    y_axis = ((quint32)(quint8)data[DATA_Y_AXIS+3])<<24 | ((quint32)(quint8)data[DATA_Y_AXIS+2])<<16 |
                    ((quint32)(quint8)data[DATA_Y_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Y_AXIS];

    z_axis = ((quint32)(quint8)data[DATA_Z_AXIS+3])<<24 | ((quint32)(quint8)data[DATA_Z_AXIS+2])<<16 |
                    ((quint32)(quint8)data[DATA_Z_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Z_AXIS];

    roll_angle = ((quint32)(quint8)data[DATA_ROLL_ANGLE+3])<<24 | ((quint32)(quint8)data[DATA_ROLL_ANGLE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROLL_ANGLE+1])<<8 | (quint32)(quint8)data[DATA_ROLL_ANGLE];

    pitch_angle = ((quint32)(quint8)data[DATA_PITCH_ANGLE+3])<<24 | ((quint32)(quint8)data[DATA_PITCH_ANGLE+2])<<16 |
                    ((quint32)(quint8)data[DATA_PITCH_ANGLE+1])<<8 | (quint32)(quint8)data[DATA_PITCH_ANGLE];

    yaw_angle = ((quint32)(quint8)data[DATA_YAW_ANGLE+3])<<24 | ((quint32)(quint8)data[DATA_YAW_ANGLE+2])<<16 |
                    ((quint32)(quint8)data[DATA_YAW_ANGLE+1])<<8 | (quint32)(quint8)data[DATA_YAW_ANGLE];

//    QVector<double> pos;
    robot_position[0]=(x_axis/1000.0);
    robot_position[1]=(y_axis/1000.0);
    robot_position[2]=(z_axis/1000.0);
    robot_position[3]=(roll_angle/10000.0);
    robot_position[4]=(pitch_angle/10000.0);
    robot_position[5]=(yaw_angle/10000.0);
}

void YRC1000micro_com::YRC1000microReadPositionResponsePulse(QByteArray data)
{
    qint32 S_axis = 0;
    qint32 L_axis = 0;
    qint32 U_axis = 0;
    qint32 R_axis = 0;
    qint32 B_axis = 0;
    qint32 T_axis = 0;
    S_axis = ((quint32)(quint8)data[DATA_X_AXIS+3])<<24 | ((quint32)(quint8)data[DATA_X_AXIS+2])<<16 |
                    ((quint32)(quint8)data[DATA_X_AXIS+1])<<8 | (quint32)(quint8)data[DATA_X_AXIS];

    L_axis = ((quint32)(quint8)data[DATA_Y_AXIS+3])<<24 | ((quint32)(quint8)data[DATA_Y_AXIS+2])<<16 |
                    ((quint32)(quint8)data[DATA_Y_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Y_AXIS];

    U_axis = ((quint32)(quint8)data[DATA_Z_AXIS+3])<<24 | ((quint32)(quint8)data[DATA_Z_AXIS+2])<<16 |
                    ((quint32)(quint8)data[DATA_Z_AXIS+1])<<8 | (quint32)(quint8)data[DATA_Z_AXIS];

    R_axis = ((quint32)(quint8)data[DATA_ROLL_ANGLE+3])<<24 | ((quint32)(quint8)data[DATA_ROLL_ANGLE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROLL_ANGLE+1])<<8 | (quint32)(quint8)data[DATA_ROLL_ANGLE];

    B_axis = ((quint32)(quint8)data[DATA_PITCH_ANGLE+3])<<24 | ((quint32)(quint8)data[DATA_PITCH_ANGLE+2])<<16 |
                    ((quint32)(quint8)data[DATA_PITCH_ANGLE+1])<<8 | (quint32)(quint8)data[DATA_PITCH_ANGLE];

    T_axis = ((quint32)(quint8)data[DATA_YAW_ANGLE+3])<<24 | ((quint32)(quint8)data[DATA_YAW_ANGLE+2])<<16 |
                    ((quint32)(quint8)data[DATA_YAW_ANGLE+1])<<8 | (quint32)(quint8)data[DATA_YAW_ANGLE];
//    QVector<double> pos;
    robot_position_pulse[0]=S_axis;
    robot_position_pulse[1]=L_axis;
    robot_position_pulse[2]=U_axis;
    robot_position_pulse[3]=R_axis;
    robot_position_pulse[4]=B_axis;
    robot_position_pulse[5]=T_axis;
}

QVector<double> YRC1000micro_com::updateRobotPosition()
{
    return robot_position;
}

QVector<double> YRC1000micro_com::updateRobotPositionPulse()
{
    return robot_position_pulse;
}

QVector<double> YRC1000micro_com::updateRobotPositionVariable()
{
    return robot_position_variable;
}

void YRC1000micro_com::YRC1000microMoveCartesian(quint8 coordinate,quint8 move_type, quint8 speed_type, double speed, QVector<double>* position)
{
    QByteArray data = yrc1000micro_command.setRobotPositionCartesian(request_id_index,
                                                 coordinate,move_type,speed_type,speed,position);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_MOVE_ROBOT_CARTESIAN;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microMovePulse(double speed, QVector<double> *position)
{
    QByteArray data = yrc1000micro_command.setRobotPositionCartesianJog(request_id_index, speed, position);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_MOVE_ROBOT_PULSE;
    request_id_index ++;
}



void YRC1000micro_com::YRC1000microMoveJog(double speed, QVector<double> *position)
{
    QByteArray data = yrc1000micro_command.setRobotPositionCartesianJog(request_id_index, speed, position);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_MOVE_ROBOT_PULSE;
    request_id_index ++;
}


void YRC1000micro_com::YRC1000microReadStatus(){
    QByteArray data = yrc1000micro_command.readStatus(request_id_index);
    //qDebug()<<"yrccom data"<<data;
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_STATUS_READING;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microReadStatusResponse(QByteArray data){
    status_code = 0;
    status_code = status_code | (((quint16)(quint8)data[RES_STATUS_READING_DATA_1+HEADER_SIZE]) << 8);
    status_code = status_code | ((quint16)(quint8)data[RES_STATUS_READING_DATA_1+HEADER_SIZE]);
}

quint16 YRC1000micro_com::updateRobotStatus(){
    return status_code;
}

void YRC1000micro_com::YRC1000microSaveJob(quint32 block_num, QString send_data){
    request_id_index ++;
    QByteArray data = yrc1000micro_command.saveJob(request_id_index,CMD_HEADER_ACK_REQUEST,block_num,send_data);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_SAVE_JOB_TO_PC;
}

quint32 YRC1000micro_com::YRC1000microSaveJobResponse(QByteArray data){
    QByteArray data_rev;
    for(int i=HEADER_SIZE;i<data.size()-1;i++)
      data_rev.append(data[i]);
//    qDebug() << "Data revieve: " << data_rev;
    QString filename = "Data.txt";
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << data_rev << Qt::endl;
        file.flush();
        file.close();
        qDebug() << "save to txt";
    }
    quint32 block_num=0;
    block_num |= ((quint32)(quint8)data[CMD_BLOCK_NUM]);
    block_num |= ((quint32)(quint8)data[CMD_BLOCK_NUM+1])<<8;
    block_num |= ((quint32)(quint8)data[CMD_BLOCK_NUM+2])<<16;
    block_num |= ((quint32)(quint8)data[CMD_BLOCK_NUM+3])<<24;

    qDebug() << "block_num: " << block_num;
    QByteArray send_data = yrc1000micro_command.saveJob(request_id_index,
                                 CMD_HEADER_ACK_NOT_REQUEST,block_num,"NODATA");
    udp_server.sendData(udp_address,udp_port,send_data);

    return 1;
}

void YRC1000micro_com::YRC1000microLoadJob(QString send_data){
    request_id_index ++;
//    Create socket
//    YRC1000microFileTransferConnect();
    load_file_block_num = 0;
    QByteArray data = yrc1000micro_command.loadJob(request_id_index,CMD_HEADER_ACK_REQUEST,load_file_block_num,send_data);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_LOAD_JOB_TO_YRC;
    QFile load_file("Data.txt");
    if(load_file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream load(&load_file);
        str_load_file = load.readAll();
        qDebug() << "Read file: " << str_load_file << Qt::endl;
        load_file.flush();
        load_file.close();
        load_data_status = true;
    }
}

quint32 YRC1000micro_com::YRC1000microLoadJobResponse(QByteArray data, quint32 block_num){
    if(data[RES_STATUS] != '\x00'){
       qDebug() << "Load file command error" << Qt::endl;
       return 0;
    }
    QString str_data = QString(data);
    if(load_data_status){
      qDebug() << "Load file ......";
      if(str_load_file.size()>400){
          qDebug() << "Load file > 400";
          QString temp_str_load_file = str_load_file.left(400);
          str_load_file = str_load_file.right(str_load_file.size()-400);
          QByteArray send_data = yrc1000micro_command.loadJob(request_id_index,
                                       CMD_HEADER_ACK_NOT_REQUEST,block_num,temp_str_load_file);
          udp_server.sendData(udp_address,udp_port,send_data);
          qDebug() << "Load to be load: " << temp_str_load_file << Qt::endl;
      }
      else {
          qDebug() << "Load file < 400" ;
          QByteArray send_data = yrc1000micro_command.loadJob(request_id_index,
                                       CMD_HEADER_ACK_NOT_REQUEST,block_num+2147483648,str_load_file);
          udp_server.sendData(udp_address,udp_port,send_data);
          qDebug() << "Load to be load: " << str_load_file << Qt::endl;
          load_data_status = false;
      }
    }
    else {
          qDebug() << "Close socket" << Qt::endl;
          YRC1000microDisConnect();
    }

    return 1;
}

void YRC1000micro_com::YRC1000microReadRobotVariable(int variableNumber, int dataType)
{
    QByteArray data = yrc1000micro_command.readRobotVariable(request_id_index,variableNumber,dataType);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_READ_WRITE_ROBOT_VARIABLE;
    request_id_index ++;
}

void YRC1000micro_com::YRC1000microReadRobotVariableResponse(QByteArray data)
{
    qint32 x_axis = 0;
    qint32 y_axis = 0;
    qint32 z_axis = 0;
    qint32 roll_angle = 0;
    qint32 pitch_angle = 0;
    qint32 yaw_angle = 0;
    x_axis = ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_1ST_COORDINATE+3])<<24 | ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_1ST_COORDINATE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_1ST_COORDINATE+1])<<8 | (quint32)(quint8)data[DATA_ROBOT_VARIABLE_1ST_COORDINATE];

    y_axis = ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_2ND_COORDINATE+3])<<24 | ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_2ND_COORDINATE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_2ND_COORDINATE+1])<<8 | (quint32)(quint8)data[DATA_ROBOT_VARIABLE_2ND_COORDINATE];

    z_axis = ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_3RD_COORDINATE+3])<<24 | ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_3RD_COORDINATE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_3RD_COORDINATE+1])<<8 | (quint32)(quint8)data[DATA_ROBOT_VARIABLE_3RD_COORDINATE];

    roll_angle = ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_4TH_COORDINATE+3])<<24 | ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_4TH_COORDINATE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_4TH_COORDINATE+1])<<8 | (quint32)(quint8)data[DATA_ROBOT_VARIABLE_4TH_COORDINATE];

    pitch_angle = ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_5TH_COORDINATE+3])<<24 | ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_5TH_COORDINATE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_5TH_COORDINATE+1])<<8 | (quint32)(quint8)data[DATA_ROBOT_VARIABLE_5TH_COORDINATE];

    yaw_angle = ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_6TH_COORDINATE+3])<<24 | ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_6TH_COORDINATE+2])<<16 |
                    ((quint32)(quint8)data[DATA_ROBOT_VARIABLE_6TH_COORDINATE+1])<<8 | (quint32)(quint8)data[DATA_ROBOT_VARIABLE_6TH_COORDINATE];


    robot_position_variable[0]=(x_axis/1000.0);
    robot_position_variable[1]=(y_axis/1000.0);
    robot_position_variable[2]=(z_axis/1000.0);
    robot_position_variable[3]=(roll_angle/10000.0);
    robot_position_variable[4]=(pitch_angle/10000.0);
    robot_position_variable[5]=(yaw_angle/10000.0);
    emit readRobotVari();
}

void YRC1000micro_com::YRC1000microSaveRobotVariable(int variableNumber, int dataType, double x, double y, double z, double roll, double pitch, double yaw)
{
    QByteArray data = yrc1000micro_command.saveRobotVariable(request_id_index,variableNumber,dataType,x,y,z,roll,pitch,yaw);
    udp_server.sendData(udp_address,udp_port,data);
    request_code[request_id_index] = CMD_ID_READ_WRITE_ROBOT_VARIABLE;
    request_id_index ++;
}


