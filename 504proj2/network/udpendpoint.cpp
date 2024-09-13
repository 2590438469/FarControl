#include "network/udpendpoint.h"

UdpEndpoint::UdpEndpoint()
{
    this->setId(-1);
    this->setSourceName("新建数据源");
    this->setAddress("225.0.2.2");
    this->setInterface("0.0.0.0");
    this->setPort(8448);
    this->setIsMulticast(true);

//    udp_socket = nullptr;
}

UdpEndpoint::UdpEndpoint(int id, const QString &source_name, const QString &str_address, const QString &str_interface, int port, bool is_multicast, QObject *parent)
    : QObject(parent)
{
    this->setId(id);
    this->setSourceName(source_name);
    this->setAddress(str_address);
    this->setInterface(str_interface);
    this->setPort(port);
    this->setIsMulticast(is_multicast);

//    udp_socket = nullptr;
}

UdpEndpoint::UdpEndpoint(const UdpEndpoint &data_source) : QObject(data_source.parent())
{
    this->setId(data_source.m_id);
    this->setSourceName(data_source.m_source_name);
    this->setAddress(data_source.m_address);
    this->setInterface(data_source.m_interface);
    this->setPort(data_source.m_port);
    this->setIsMulticast(data_source.m_is_multicast);

//    udp_socket = nullptr;
}

UdpEndpoint::~UdpEndpoint()
{
//    delete udp_socket;
}

UdpEndpoint &UdpEndpoint::operator=(const UdpEndpoint &data_source)
{
    this->setId(data_source.m_id);
    this->setSourceName(data_source.m_source_name);
    this->setAddress(data_source.m_address);
    this->setInterface(data_source.m_interface);
    this->setPort(data_source.m_port);
    this->setIsMulticast(data_source.m_is_multicast);

//    udp_socket = nullptr;

    return *this;
}

//void QDataSource::start()
//{
//    if (udp_socket != nullptr) {
//        delete udp_socket;
//        udp_socket = nullptr;
//    }
//    if (m_interface.compare("0.0.0.0") == 0) {
//        udp_socket->bind(
//            QHostAddress::AnyIPv4,
//            static_cast<quint16>(this->m_port),
//            QAbstractSocket::ShareAddress
//        );
//    } else {
//        QHostAddress host_interface(m_interface);
//        udp_socket->bind(
//            host_interface,
//            static_cast<quint16>(this->m_port),
//            QAbstractSocket::ShareAddress
//        );
//    }
//    if (m_is_multicast) {
//        QHostAddress host_address(m_address);
//        udp_socket->joinMulticastGroup(host_address);
//    }
//}

//void QDataSource::onDataRecived() {
//    QByteArray datagram;
//    while (udp_socket->hasPendingDatagrams()) {
//        datagram.resize(int(udp_socket->pendingDatagramSize()));
//        udp_socket->readDatagram(datagram.data(), datagram.size());
//        emit packageArrived(datagram.constData(), datagram.size());
//    }
//}

QString UdpEndpoint::getSourceName() const
{
    return m_source_name;
}

QString UdpEndpoint::getAddress() const
{
    return m_address;
}

QString UdpEndpoint::getInterface() const
{
    return m_interface;
}

int UdpEndpoint::getPort() const
{
    return m_port;
}

int UdpEndpoint::getId() const
{
    return m_id;
}

bool UdpEndpoint::getIsMulticast() const
{
    return m_is_multicast;
}

void UdpEndpoint::setSourceName(const QString &source_name)
{
    m_source_name = source_name;
    emit dataChanged(*this);
}

void UdpEndpoint::setAddress(const QString &str_address)
{
    this->m_address = str_address;
    emit dataChanged(*this);
}

void UdpEndpoint::setInterface(const QString &str_interface)
{
    this->m_interface = str_interface;
    emit dataChanged(*this);
}

void UdpEndpoint::setPort(int port)
{
    this->m_port = port;
    emit dataChanged(*this);
}

void UdpEndpoint::setId(int id)
{
    m_id = id;
    emit dataChanged(*this);
}

void UdpEndpoint::setIsMulticast(bool is_multicast)
{
    this->m_is_multicast = is_multicast;
    emit dataChanged(*this);
}
