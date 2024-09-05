#include "udp.h"

UDP::UDP(QObject *parent) : QObject(parent)
{
    // create a QUDP socket
    socket = new QUdpSocket(this);

    // The most common way to use QUdpSocket class is
    // to bind to an address and port using bind()
    // bool QAbstractSocket::bind(const QHostAddress & address,
    //     quint16 port = 0, BindMode mode = DefaultForPlatform)
}

UDP::~UDP(){
    socket->close();
}

bool UDP::udpConnect(QHostAddress address, quint16 port)
{
    bool status = socket->bind(QHostAddress::Any, port);
//    bool status = socket->bind(address, port);
    qDebug() << "Connect status: " << status;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    return status;
}
void UDP::udpDisConnect()
{
    socket->close();
}

void UDP::sendData(QHostAddress address, quint16 port, QByteArray data)
{
    socket->writeDatagram(data, address, port);
}

void UDP::HelloUDP()
{
    QByteArray Data;
    Data.append("YERC20$00$04$00$03$01$00$01$00$00$00$0099999999$83$00$02$00$01$10$00$00$01$00$00$00");

    // Sends the datagram datagram
    // to the host address and at port.
    // qint64 QUdpSocket::writeDatagram(const QByteArray & datagram,
    //                      const QHostAddress & host, quint16 port)
    socket->writeDatagram(Data, QHostAddress::LocalHost, 1234);
}

void UDP::readyRead()
{
    // when data comes in
//    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // qint64 QUdpSocket::readDatagram(char * data, qint64 maxSize,
    //                 QHostAddress * address = 0, quint16 * port = 0)
    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);


    emit dataRecieveSignal();

}

QByteArray UDP::getUdpData(){
    return buffer;
}
