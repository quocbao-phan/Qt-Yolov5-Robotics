#include "servocontrol.h"

servoControl::servoControl(QObject *parent)
    : QThread{parent}
{

}

void servoControl::run()
{
    qDebug()<< "Thread Serial is Running";
    updateSerialPorts();

    emit sliderEnable(false);

    connect(&mSerialScanTimer,SIGNAL(timeout()),this,SLOT(updateSerialPorts()));

    connect(&mSerial,SIGNAL(readyRead()),this, SLOT(serialReadyRead()));

    //connect(&checkSerialConnectionTimer,SIGNAL(timeout()),this,SLOT(checkSerialConnection()));

}

void servoControl::Send()
{
    posToSend = (unsigned char*)(&Pos);

    if (mSerial.isOpen())
    {
        //frame
        txbuff[0] = QByteArray::number(65,16);
        txbuff[1] = QByteArray::number(1,16);
        txbuff[2] = QByteArray::number(68,16);
        txbuff[3] = QByteArray::number(69,16);
        for (int j = 0; j < 4; j++)
        {
            mSerial.write(QByteArray::fromHex(txbuff[j]));
        }
    }
    else
    {
        qDebug() << "Serial port not connected!";
    }
}

void servoControl::serialReadyRead()
{
    QByteArray data = mSerial.readAll();
    QString str = QString(data);
    if ((str[0]=="A")&&(str[1]=="B"))
    {
        str.remove("A");
        str.remove("B");
        rcv_flag = str.toInt();
    }
    str.clear();
    data.clear();
    Send();
}

void servoControl::checkSerialConnection()
{
    if  (!rcv_flag)
    {
       emit statusServoText("Check serial connection and reconnect");
       emit btnServoText("CONNECT");
       emit sliderEnable(false);
       mSerial.close();
    }
    rcv_flag = 0;
}

void servoControl::on_btn_ConnectServo_clicked()
{
    emit btnConnectEnable(false);
    emit comboBoxDataRequest();
    if (mSerial.isOpen())
    {
        emit btnServoText("CONNECT");
        qDebug() << "Serial already connected, disconnecting!";
        emit statusServoText("COM port disconnected");
        mSerial.close();
        emit sliderEnable(false);
        emit btnConnectEnable(true);
        checkSerialConnectionTimer.stop();
    }
    else
    {
        emit btnServoText("DISCONNECT");
        mSerial.setPortName(serialLoc);
        mSerial.setBaudRate(QSerialPort::Baud9600);//Baud115200
        mSerial.setDataBits(QSerialPort::Data8);
        mSerial.setParity(QSerialPort::NoParity);
        mSerial.setStopBits(QSerialPort::OneStop);
        mSerial.setFlowControl(QSerialPort::NoFlowControl);
        if(mSerial.open(QIODevice::ReadWrite))
        {
            qDebug() << "SERIAL: OK!";
            emit statusServoText("COM port connected");
            emit sliderEnable(true);
        } else {
            qDebug() << "SERIAL: ERROR!";
        }
        emit btnConnectEnable(true);
        Send();
        checkSerialConnectionTimer.start(1000);
    }
}

void servoControl::updateSerialPorts()
{
    mSerialPorts = QSerialPortInfo::availablePorts();
    emit comboBoxClear();
    for (QSerialPortInfo port : mSerialPorts)
    {
        emit comboBoxAddItem(port.portName(), port.systemLocation());
    }
}

void servoControl::getSliderValue(int pwm)
{
    Pos = pwm;
    QByteArray tf = QByteArray::number(pwm,16);
    mSerial.write(QByteArray::fromHex(tf));
}

void servoControl::receiveComboBoxData(QString serialName_rcv, QString serialLoc_rcv)
{
    serialName = serialName_rcv;
    serialLoc = serialLoc_rcv;
}




