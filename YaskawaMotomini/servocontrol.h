#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QString>
#include <QChar>
#include <QDebug>
#include <QList>
class servoControl : public QThread
{
    Q_OBJECT
public:
    explicit servoControl(QObject *parent = nullptr);

    QSerialPort mSerial;

    QList<QSerialPortInfo> mSerialPorts;

    QTimer mSerialScanTimer;
protected:
    void run();
signals:
    void comboBoxDataRequest();

    void comboBoxClear();

    void comboBoxAddItem(QString Name, QString Location);

    void statusServoText(QString text);

    void btnServoText(QString text);

    void btnConnectEnable(bool flag);

    void sliderEnable(bool en);
private slots:
    void Send();

    void serialReadyRead();

    void checkSerialConnection();

    void on_btn_ConnectServo_clicked();

    void updateSerialPorts();

    void getSliderValue(int pwm);

    void receiveComboBoxData(QString serialName_rcv,QString serialLoc_rcv);
private:

    QTimer checkSerialConnectionTimer;
    QByteArray txbuff[13];
    int rcv_flag = 0;
    QString serialName;
    QString serialLoc;
    unsigned char *posToSend;
    int Pos;
};

#endif // SERVOCONTROL_H
