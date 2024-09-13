#include "network/qasioudpsocket.h"

bool QAsioUdpSocket::bindToLocalAddress(quint16 port, QAbstractSocket::BindMode mode)
{
    qDebug()<<"Before asio bind.";
    qDebug()<<QString(local_address->to_string().c_str());
    qDebug()<<port;
    bind_port = port;
    bind_mode = mode;

    socket->set_option(asio::ip::udp::socket::reuse_address(true));

    return true;
}

void QAsioUdpSocket::ioContextRun()
{
    io_context.run();
}

QAsioUdpSocket::QAsioUdpSocket(QObject *parent) : QObject(parent)
{
    socket = nullptr;
    local_address = nullptr;
    bind_port = -1;
    bytes_recvd = -1;
    worker = new asio::io_context::work(io_context);
    t = new std::thread(&QAsioUdpSocket::ioContextRun, this);
}



QAsioUdpSocket::~QAsioUdpSocket()
{
    if (socket) delete socket;
    if (local_address) delete local_address;
    io_context.stop();
    if (t) {
        t->join();
        delete t;
        delete worker;
    }
}

bool QAsioUdpSocket::bind(const QHostAddress &address, quint16 port, QAbstractSocket::BindMode mode)
{
    qDebug()<<address;
    local_address = new asio::ip::address(
        asio::ip::address::from_string(address.toString().toStdString())
    );

    socket = new asio::ip::udp::socket(
        io_context,
        asio::ip::udp::endpoint(
            *local_address, port
        )
    );
    return bindToLocalAddress(port, mode);
}

bool QAsioUdpSocket::bind(const QString &address, quint16 port, QAbstractSocket::BindMode mode)
{
    qDebug()<<address;
    local_address = new asio::ip::address(
        asio::ip::address::from_string(address.toStdString())
    );

    socket = new asio::ip::udp::socket(
        io_context,
        asio::ip::udp::endpoint(
            *local_address, port
        )
    );

    return bindToLocalAddress(port, mode);
}

bool QAsioUdpSocket::bind(quint16 port, QAbstractSocket::BindMode mode)
{
    socket = new asio::ip::udp::socket(
        io_context,
        asio::ip::udp::endpoint(asio::ip::udp::v4(), port)
    );

    bindToLocalAddress(port, mode);

    return true;
}

void QAsioUdpSocket::startListen()
{  
    socket->async_receive_from(
        asio::buffer(recv_data, MAX_LENGTH),
        sender_endpoint,
        [this](std::error_code ec, std::size_t bytes_recvd)
        {
            qDebug()<<"Entered recevie callback.";
            if (!ec && bytes_recvd > 0)
            {
                this->bytes_recvd = static_cast<int>(bytes_recvd);
                emit readyRead();
            } else {
                this->bytes_recvd = -1;
            }
            startListen();
        }
    );
}

bool QAsioUdpSocket::joinMulticastGroup(const QHostAddress &groupAddress)
{
    asio::ip::address group_address =
        asio::ip::address::from_string(groupAddress.toString().toStdString());
    asio::ip::multicast::join_group join_group_option(group_address);

    socket->set_option(join_group_option);

    return true;
}

bool QAsioUdpSocket::leaveMulticastGroup(const QHostAddress &groupAddress)
{
    asio::ip::address group_address =
        asio::ip::address::from_string(groupAddress.toString().toStdString());
    asio::ip::multicast::leave_group leave_group_option(group_address);

    socket->set_option(leave_group_option);

    return true;
}

bool QAsioUdpSocket::joinMulticastGroup(const QString &groupAddress)
{
    asio::ip::address group_address =
        asio::ip::address::from_string(groupAddress.toStdString());
    asio::ip::multicast::join_group join_group_option(group_address);

    socket->set_option(join_group_option);

    return true;
}

bool QAsioUdpSocket::leaveMulticastGroup(const QString &groupAddress)
{
    asio::ip::address group_address =
        asio::ip::address::from_string(groupAddress.toStdString());
    asio::ip::multicast::leave_group leave_group_option(group_address);

    socket->set_option(leave_group_option);

    return true;
}

bool QAsioUdpSocket::hasPendingDatagrams() const
{
    return (bytes_recvd > 0);
}

int QAsioUdpSocket::pendingDatagramSize() const
{
    return bytes_recvd;
}

int QAsioUdpSocket::readDatagram(char *data, int maxSize, QHostAddress *address, quint16 *port)
{
    int copy_size = maxSize > bytes_recvd ? bytes_recvd : maxSize;
    if (address) {
        address->setAddress(QString(sender_endpoint.address().to_string().c_str()));
    }
    if (port) {
        *port = sender_endpoint.port();
    }
    memcpy(data, recv_data, static_cast<size_t>(copy_size));
    return copy_size;
}

int QAsioUdpSocket::writeDatagram(const char *data, int size, const QHostAddress &address, quint16 port)
{
    asio::ip::address *remote_address = nullptr;
    if (address.protocol() == QAbstractSocket::IPv4Protocol) {
        uint address_uint = address.toIPv4Address();
        asio::ip::address_v4 remote_address_ipv4(address_uint);
        remote_address = new asio::ip::address(remote_address_ipv4);
        socket->open(asio::ip::udp::v4());
    } else if (address.protocol() == QAbstractSocket::IPv6Protocol) {
        asio::ip::address_v6::bytes_type ipv6_bytes;
        for (int i = 0; i < 16; ++i) {
            ipv6_bytes[static_cast<unsigned int>(i)] =
                    static_cast<unsigned char>(
                        ((address.toIPv6Address()[(i >> 2)] >> ((i & 3) << 2)) & 0xFF)
                    );
        }

        asio::ip::address_v6 remote_address_ipv6(ipv6_bytes);
        remote_address = new asio::ip::address(remote_address_ipv6);
        socket->open(asio::ip::udp::v6());
    }
    asio::ip::udp::endpoint remote_endpoint(*remote_address, port);
    size_t send_size = socket->send_to(asio::buffer(data, static_cast<size_t>(size)), remote_endpoint);
    return static_cast<int>(send_size);
}

int QAsioUdpSocket::writeDatagram(const char *data, int size, const QString &address, quint16 port)
{
    qDebug()<<data;
    qDebug()<<size;
    qDebug()<<address;
    qDebug()<<port;
    asio::ip::address *remote_address = new asio::ip::address(
        asio::ip::address::from_string(address.toStdString())
    );
    asio::ip::udp::endpoint remote_endpoint(*remote_address, port);
    size_t send_size = socket->send_to(asio::buffer(data, static_cast<size_t>(size)), remote_endpoint);
    return static_cast<int>(send_size);
}
