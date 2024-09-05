#ifndef YRC1000MICRO_COMMAND_H
#define YRC1000MICRO_COMMAND_H

#include <QObject>

//Init header with servo off cmd
#define HEADER_INIT "59 45 52 43 20 00 04 00 03 01 00 01 00 00 00 00 39 39 39 39 39 39 39 39 83 00 02 00 01 10 00 00 02 00 00 00"
#define HEADER_SIZE             32

#define CMD_ID_SERVO_ON                         '\x83'
#define CMD_ID_READ_ROBOT_POS                   '\x75'
#define CMD_ID_READ_WRITE_ROBOT_VARIABLE        '\x7F'

#define CMD_ID_MOVE_ROBOT_CARTESIAN             '\x8A'
#define CMD_ID_MOVE_ROBOT_PULSE                 '\x8B'
#define CMD_ID_STATUS_READING                   '\x72'
#define CMD_ID_LOAD_SAVE_JOB                    '\x00'
#define CMD_ID_LOAD_JOB_TO_YRC                  '\x02'
#define CMD_ID_SAVE_JOB_TO_PC                   '\x03'

#define CMD_DATA_SIZE           6
#define CMD_PROCESS_DIVTION     9
#define CMD_ACK                 10
#define CMD_REQUEST_ID          11
#define CMD_BLOCK_NUM           12
#define CMD_ID_ADDRESS          24
#define CMD_INSTANCE            26
#define CMD_ATTRIBUTE           28
#define CMD_SERVICE             29

#define CMD_SERVICE_REPLY       24
#define CMD_MOVE_PULSE_LINK_ABSOLUTE_INSTANCE   1

#define RES_STATUS              25
#define RES_STATUS_SIZE         26
#define RES_STATUS_ERROR        28

#define DATA_BYTE0              32
#define DATA_BYTE1              33
#define DATA_BYTE2              34
#define DATA_BYTE3              35

#define DATA_TYPE               32
#define DATA_X_AXIS             52
#define DATA_Y_AXIS             56
#define DATA_Z_AXIS             60
#define DATA_ROLL_ANGLE         64
#define DATA_PITCH_ANGLE        68
#define DATA_YAW_ANGLE          72

#define DATA_READ_WRITE_ROBOT_VARIABLE_DATA_TYPE        32
#define DATA_ROBOT_VARIABLE_1ST_COORDINATE              52
#define DATA_ROBOT_VARIABLE_2ND_COORDINATE              56
#define DATA_ROBOT_VARIABLE_3RD_COORDINATE              60
#define DATA_ROBOT_VARIABLE_4TH_COORDINATE              64
#define DATA_ROBOT_VARIABLE_5TH_COORDINATE              68
#define DATA_ROBOT_VARIABLE_6TH_COORDINATE              72

#define DATA_MOVE_ROBOT_NUMBER      0
#define DATA_MOVE_STATION_NUM       4
#define DATA_MOVE_SPEED_TYPE        8
#define DATA_MOVE_SPEED             12
#define DATA_MOVE_COORDINATE        16
#define DATA_MOVE_X_CARTESIAN       20
#define DATA_MOVE_Y_CARTISIAN       24
#define DATA_MOVE_Z_CARTESIAN       28
#define DATA_MOVE_ROLL_CARTESIAN    32
#define DATA_MOVE_PITCH_CARTESIAN   36
#define DATA_MOVE_YAW_CARTESIAN     40
#define DATA_MOVE_USER_COORDINATE   64

#define DATA_MOVE_1ST_AXIS_PULSE    16
#define DATA_MOVE_2ND_AXIS_PULSE    20
#define DATA_MOVE_3RD_AXIS_PULSE    24
#define DATA_MOVE_4TH_AXIS_PULSE    28
#define DATA_MOVE_5TH_AXIS_PULSE    32
#define DATA_MOVE_6TH_AXIS_PULSE    36

#define DATA_SAVE_ROBOT_VARIABLE_DATA_TYPE              0
#define DATA_SAVE_ROBOT_VARIABLE_X                      20
#define DATA_SAVE_ROBOT_VARIABLE_Y                      24
#define DATA_SAVE_ROBOT_VARIABLE_Z                      28
#define DATA_SAVE_ROBOT_VARIABLE_ROLL                   32
#define DATA_SAVE_ROBOT_VARIABLE_PITCH                  36
#define DATA_SAVE_ROBOT_VARIABLE_YAW                    40


#define DATA_READ_WRITE_ROBOT_VARIABLE_TOOL_NUMBER      3
#define DATA_READ_WRITE_ROBOT_VARIABLE_USER_COORDINATE  4



#define CMD_HEADER_ACK_REQUEST                      '\x00'
#define CMD_HEADER_ACK_NOT_REQUEST                  '\x01'
#define CMD_HEADER_PROCESS_ROBOT_CONTROL            '\x01'
#define CMD_HEADER_PROCESS_FILE_CONTROL             '\x02'

#define CMD_HEADER_SERVO                            '\x83'
#define CMD_HEADER_SERVO_DATA_SIZE                  '\x04'
#define CMD_HEADER_SERVO_INSTANCE_HOLD              0x01
#define CMD_HEADER_SERVO_INSTANCE_ON                0x02
#define CMD_HEADER_SERVO_INSTANCE_HLOCK             0x03
#define CMD_HEADER_SERVO_ATTRIBUTE                  0x01
#define CMD_HEADER_SERVO_SERVICE                    0x10

#define CMD_HEADER_READ_POS_DATA_SIZE                           '\x00'
#define CMD_HEADER_READ_WRITE_ROBOT_VARIABLE_DATA_SIZE          '\x34'
#define CMD_HEADER_READ_POS_INSTANCE_CARTESIAN                  '\x65'
#define CMD_HEADER_READ_POS_INSTANCE_PULSE                      '\x01'
#define CMD_HEADER_READ_POS_ATTRIBUTE_DATA_TYPE                 '\x01'
#define CMD_HEADER_READ_POS_ATTRIBUTE_ALL                       '\x00'
#define CMD_HEADER_READ_POS_ATTRIBUTE_6TH_AXIS                  '\x0B'
#define CMD_HEADER_READ_POS_SERVICE_SINGLE                      '\x0E'
#define CMD_HEADER_READ_POS_SERVICE_ALL                         '\x01'

#define CMD_HEADER_READ_ROBOT_VARIABLE_SERVICE                  '\x01'
#define CMD_HEADER_WRITE_ROBOT_VARIABLE_SERVICE                 '\x02'
#define CMD_HEADER_READ_ROBOT_VARIABLE_SERVICE_REPLY            '\x81'
#define CMD_HEADER_WRITE_ROBOT_VARIABLE_SERVICE_REPLY           '\x82'
#define CMD_HEADER_WRITE_ROBOT_VARIABLE_ATTRIBUTE               0

#define CMD_HEADER_MOVE_CARTESIAN_DATA_SIZE         '\x68'
#define CMD_HEADER_MOVE_JOG_CARTESIAN_DATA_SIZE     '\x58'
#define CMD_HEADER_MOVE_INSTANCE_LINK_ABSOLUTE      '\x01'
#define CMD_HEADER_MOVE_INSTANCE_STRAIGHT_ABSOLUTE  '\x02'
#define CMD_HEADER_MOVE_INSTANCE_STRAIGHT_INCREMENT '\x03'
#define CMD_HEADER_MOVE_PULSE_INSTANCE              '\x01'
#define CMD_HEADER_MOVE_ATTRIBUTE                   '\x01'
#define CMD_HEADER_MOVE_SERVICE_ALL                 '\x02'

#define CMD_HEADER_STATUS_DATA_SIZE                 '\x00'
#define CMD_HEADER_STATUS_INSTANCE                  '\x01'
#define CMD_HEADER_STATUS_ATTRIBUTE_DATA_1          '\x01'
#define CMD_HEADER_STATUS_ATTRIBUTE_DATA_2          '\x02'
#define CMD_HEADER_STATUS_ATTRIBUTE_ALL             '\x00'
#define CMD_HEADER_STATUS_SERVICE_SINGLE            '\x0E'
#define CMD_HEADER_STATUS_SERVICE_ALL               '\x01'

#define CMD_HEADER_LOAD_JOB_INSTANCE                '\x00'
#define CMD_HEADER_LOAD_JOB_ATTRIBUTE               '\x00'
#define CMD_HEADER_LOAD_JOB_SERVICE                 '\x15'

#define CMD_HEADER_SAVE_JOB_INSTANCE                '\x00'
#define CMD_HEADER_SAVE_JOB_ATTRIBUTE               '\x00'
#define CMD_HEADER_SAVE_JOB_SERVICE                 '\x16'

#define CMD_DATA_SERVO_ON                           0x01
#define CMD_DATA_SERVO_OFF                          0x02

#define CMD_DATA_MOVE_SPEED_TYPE_LINK               '\x00'
#define CMD_DATA_MOVE_SPEED_TYPE_V_SPEED            '\x01'
#define CMD_DATA_MOVE_SPEED_TYPE_VR_SPEED           '\x02'
#define CMD_DATA_MOVE_COORDINATE_BASE               '\x10'
#define CMD_DATA_MOVE_COORDINATE_ROBOT              '\x11'
#define CMD_DATA_MOVE_COORDINATE_USER               '\x12'
#define CMD_DATA_MOVE_COORDINATE_TOOL               '\x13'


#define RES_VALUE_SERVO_STATUS_NORMAL               '\x00'
#define RES_VALUE_SERVO_STATUS_SIZE_ONE_WORD        0x01
#define RES_VALUE_SERVO_STATUS_SIZE_TWO_WORD        0x02

#define RES_STATUS_READING_DATA_1                   0
#define RES_STATUS_READING_DATA_2                   4

// Data 1
#define RES_VALUE_READING_RUNNING_MASK              0x0800
// Data 2
#define RES_VALUE_READING_ALARM_MASK                0x0010
#define RES_VALUE_READING_ERROR_MASK                0x0020



class YRC1000micro_command : public  QObject
{
    Q_OBJECT
public:
    explicit YRC1000micro_command(QObject *parent = nullptr);
    ~YRC1000micro_command();
    QByteArray setServoOn(quint8 request_id_index);
    QByteArray setServoOff(quint8 request_id_index);
    QByteArray readRobotPosition(quint8 request_id_index);
    QByteArray readRobotPositionPulse(quint8 request_id_index);
    QByteArray readRobotVariable(quint8 request_id_index, int variableNumber, int dataType);
    QByteArray saveRobotVariable(quint8 request_id_index, int variableNumber, int dataType, double x, double y, double z, double roll, double pitch, double yaw);

    void initRobot(quint8 robot_number);
    QByteArray setRobotPositionCartesian(quint8 request_id_index, quint8 coordinate,
              quint8 move_type,quint8 speed_type, double speed, QVector<double>* position);

    QByteArray setRobotPositionCartesianJog(quint8 request_id_index, double speed, QVector<double>* position);

    QByteArray readStatus(quint8 request_id_index);
    QByteArray loadJob(quint8 request_id_index, quint8 ack, quint32 block_num, QString data);
    QByteArray saveJob(quint8 request_id_index, quint8 ack, quint32 block_num, QString data);


signals:\

public slots:

private:
    QByteArray header_to_send;
    QByteArray data_to_send;
    QByteArray move_cartesian_data;
    QByteArray move_cartesian_jog_data;
    QByteArray read_robot_variable;
    QByteArray write_robot_variable;


};

#endif // YRC1000MICRO_COMMAND_H
