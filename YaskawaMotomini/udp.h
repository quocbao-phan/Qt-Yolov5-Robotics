#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>

class UDP : public QObject
{
    Q_OBJECT
public:
    explicit UDP(QObject *parent = nullptr);
    ~UDP();
    void HelloUDP();
    void sendData(QHostAddress address, quint16 port, QByteArray data);
    bool udpConnect(QHostAddress address,quint16 port);
    void udpDisConnect();
    QByteArray getUdpData();
signals:
    void dataRecieveSignal();

public slots:
    void readyRead();

private:
    QUdpSocket *socket;
    QByteArray buffer;
};

#endif // UDP_H
