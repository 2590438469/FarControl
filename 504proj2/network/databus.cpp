#include "network/databus.h"

DataBus::DataBus(const QString &address, const QString &interface2, int port, bool if_broadcast, QObject *parent) : QObject(parent)
{
    this->address = new QHostAddress(address);
    if (interface2.compare("0.0.0.0") == 0) {
        this->interface3 = nullptr;
    } else {
        this->interface3 = new QHostAddress(interface2);
    }
    this->port = port;
    this->if_broadcast = if_broadcast;
    required_count = 0;
}

DataBus::DataBus(const UdpEndpoint &data_source, QObject *parent) : QObject(parent)
{
    this->address = new QHostAddress(data_source.getAddress());
    QString interface = data_source.getInterface();
    if (interface.compare("0.0.0.0") == 0) {
        this->interface3 = nullptr;
    } else {
        this->interface3 = new QHostAddress(interface);
    }
    this->port = data_source.getPort();
    this->if_broadcast = data_source.getIsMulticast();
    udp_socket = nullptr;
    required_count = 0;
}

DataBus::~DataBus()
{
    delete udp_socket;
    delete address;
    delete interface3;
}

void DataBus::start()
{
    //udp_socket = new QAsioUdpSocket(this);
    if (udp_socket != nullptr) return;

    udp_socket = new QUdpSocket(this);
    if (this->interface3 == nullptr) {
        udp_socket->bind(
                    QHostAddress::AnyIPv4,
                    static_cast<quint16>(this->port),
                    QAbstractSocket::ShareAddress
                );
    } else {
        udp_socket->bind(
                    *interface3,
                    static_cast<quint16>(this->port),
                    QAbstractSocket::ShareAddress
                );
    }
    if (if_broadcast) {
        udp_socket->joinMulticastGroup(*address);
    }
    //Only for asio;
    //udp_socket->startListen();
    qDebug() << "Setup databus udp socket.";
    connect(udp_socket, SIGNAL(readyRead()),
            this, SLOT(onDataRecived()));

}

void DataBus::stop()
{
    required_count = 0;
    udp_socket->close();
    disconnect(udp_socket, SIGNAL(readyRead()),
            this, SLOT(onDataRecived()));
    delete udp_socket;
    udp_socket = nullptr;
}

void DataBus::subscribe()
{
    ++required_count;

    qDebug() << this << " Databus " << this->port << " require count : " << required_count;

    if (this->udp_socket == nullptr && required_count == 1) {
        this->start();
    }
}

void DataBus::disSubscribe()
{
    --required_count;
    qDebug() << this << "Databus " << this->port << " require count : " << required_count;
    if (this->udp_socket != nullptr && required_count <= 0) {
        this->stop();
    }
}

void DataBus::onDataRecived()
{
    QByteArray datagram;
    while (udp_socket->hasPendingDatagrams()) {
        datagram.resize(int(udp_socket->pendingDatagramSize()));
        udp_socket->readDatagram(datagram.data(), datagram.size());
        emit packageArrived(datagram.constData(), datagram.size());
    }
}
