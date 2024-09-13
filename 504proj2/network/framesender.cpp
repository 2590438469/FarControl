#include "network/framesender.h"

FrameSender::FrameSender(
        const QString &address,
        const QString &interface2,
        int port,
        bool if_broadcast,
        QObject *parent) : QObject(parent)
{
    this->address = new QHostAddress(address);
    if (interface2.compare("0.0.0.0") == 0) {
        this->interface3 = nullptr;
    } else {
        this->interface3 = new QHostAddress(interface2);
    }
    this->port = port;
    this->if_broadcast = if_broadcast;

    udp_socket = new QUdpSocket(this);
    if (this->interface3 == nullptr) {
        udp_socket->bind(QHostAddress::AnyIPv4, 0, QAbstractSocket::ShareAddress);
    } else {
        udp_socket->bind(*(this->interface3), 0, QAbstractSocket::ShareAddress);
    }
    if (if_broadcast) {
        udp_socket->joinMulticastGroup(*(this->address));
    }
}

FrameSender::FrameSender(const UdpEndpoint &data_source, QObject *parent) : QObject (parent)
{
    this->address = new QHostAddress(data_source.getAddress());
    if (data_source.getInterface().compare("0.0.0.0") == 0) {
        this->interface3 = nullptr;
    } else {
        this->interface3 = new QHostAddress(data_source.getInterface());
    }
    this->port = data_source.getPort();
    this->if_broadcast = data_source.getIsMulticast();

    udp_socket = new QUdpSocket(this);
    if (this->interface3 == nullptr) {
        udp_socket->bind(QHostAddress::AnyIPv4, 0, QAbstractSocket::ShareAddress);
    } else {
        udp_socket->bind(*(this->interface3), 0, QAbstractSocket::ShareAddress);
    }
    if (if_broadcast) {
        udp_socket->joinMulticastGroup(*(this->address));
    }
    udp_socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 128);
}

FrameSender::~FrameSender()
{
    safeDelete(udp_socket);
    safeDelete(address);
    safeDelete(interface3);
}


void FrameSender::onFrameReady(const char *proDataBuffer, int pkgLen) {
    udp_socket->writeDatagram(proDataBuffer,
                              pkgLen,
                              *address,
                              static_cast<quint16>(port));
}
