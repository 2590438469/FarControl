#ifndef QDATASOURCE_H
#define QDATASOURCE_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class UdpEndpoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ID READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString SourceName READ getSourceName WRITE setSourceName NOTIFY sourceNameChanged)
    Q_PROPERTY(QString Address READ getAddress WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString Interface READ getInterface WRITE setInterface NOTIFY interfaceChanged)
    Q_PROPERTY(int Port READ getPort WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool IsMulticast READ getIsMulticast WRITE setIsMulticast NOTIFY isMulticastChanged)

public:
    explicit UdpEndpoint();
    explicit UdpEndpoint(
        int id,
        const QString &source_name,
        const QString &str_address,
        const QString &str_interface,
        int port,
        bool is_multicast,
        QObject *parent = nullptr);
    explicit UdpEndpoint(const UdpEndpoint &data_source);
    ~UdpEndpoint();

    UdpEndpoint& operator=(const UdpEndpoint &data_source);

    //void start();

    QString getSourceName() const;
    QString getAddress() const;
    QString getInterface() const;
    int getPort() const;
    int getId() const;
    bool getIsMulticast() const;

    void setSourceName(const QString &source_name);
    void setAddress(const QString &str_address);
    void setInterface(const QString &str_interface);
    void setPort(int port);
    void setId(int id);
    void setIsMulticast(bool is_multicast);
protected:
    QString m_address, m_interface, m_source_name;
    //QUdpSocket *udp_socket;

    int m_port, m_id;
    bool m_is_multicast;

signals:
    //void packageArrived(const char *pkg, int pkg_len);
    void sourceNameChanged(const QString &);
    void addressChanged(const QString &);
    void interfaceChanged(const QString &);
    void portChanged(int);
    void idChanged();
    void isMulticastChanged(bool);
    void dataChanged(const UdpEndpoint &);
//protected slots:
//    void onDataRecived();
};

#endif // QDATASOURCE_H
