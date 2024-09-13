#include "network/udpendpointmanager.h"

UdpEndpointManager::UdpEndpointManager(const QString &data_source_csv_path, QObject *parent) : QObject(parent)
{
    m_data_source_csv_path = data_source_csv_path;
    init_local_interfaces();
    init_from_csv_file();
    data_bus_ptr_map.clear();
    frame_sender_ptr_map.clear();
}

void UdpEndpointManager::toCsvFile()
{
    FILE *csv_file_ptr = fopen(m_data_source_csv_path.toLocal8Bit().toStdString().c_str(), "w");
    fprintf(csv_file_ptr, "%s,%s,%s,%s,%s,%s\n", "ID", "SourceName", "Address", "Interface", "Port", "IsMulticast");

    int data_source_num = m_data_sources.size();
    for (int i = 0; i < data_source_num; ++i) {
        fprintf(csv_file_ptr, "%d,%s,%s,%s,%d,%d\n",
            m_data_sources[i].getId(),
            m_data_sources[i].getSourceName().toStdString().c_str(),
            m_data_sources[i].getAddress().toStdString().c_str(),
            //m_data_sources[i].getInterface().toLocal8Bit().toStdString().c_str(),
            selected_interface.toStdString().c_str(),
            m_data_sources[i].getPort(),
            m_data_sources[i].getIsMulticast() ? 1 : 0
        );
    }

    fclose(csv_file_ptr);
}

void UdpEndpointManager::reloadCsvFile()
{
    init_from_csv_file();
}

void UdpEndpointManager::addDataSource(const UdpEndpoint &data_source)
{
    m_data_sources.append(data_source);
}

void UdpEndpointManager::removeDataSource(int id)
{
    int data_source_num = m_data_sources.size();
    for (int i = 0; i < data_source_num; ++i) {
        if (m_data_sources[i].getId() == id) {
            m_data_sources.remove(i);
            break;
        }
    }
}

QVector<UdpEndpoint> *UdpEndpointManager::getDataSourceVector()
{
    return &m_data_sources;
}

void UdpEndpointManager::setSelectedInterface(const QString &str_interface)
{
    selected_interface = str_interface;
}

QString UdpEndpointManager::getSelectedInterface() const
{
    return selected_interface;
}

DataBus *UdpEndpointManager::getDataBus(int index)
{
    int id = m_data_sources[index].getId();
    if (data_bus_ptr_map.count(id) <= 0) {
        data_bus_ptr_map[id] = new DataBus(m_data_sources[index]);
    }
    return data_bus_ptr_map[id];
}

FrameSender *UdpEndpointManager::getFrameSender(int index)
{
    int id = m_data_sources[index].getId();
    if (frame_sender_ptr_map.count(id) <= 0) {
        frame_sender_ptr_map[id] = new FrameSender(m_data_sources[index]);
    }
    return frame_sender_ptr_map[id];
}

FrameSender *UdpEndpointManager::getFrameSenderByName(const QString &frame_sender_name)
{
    int index = 0;
    foreach (const UdpEndpoint &data_source, m_data_sources) {
        if (data_source.getSourceName().compare(frame_sender_name) == 0) {
            return getFrameSender(index);
        }
        ++index;
    }
    return nullptr;
}

void UdpEndpointManager::init_local_interfaces()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol) {
            if (!address.isEqual(QHostAddress("127.0.0.1"))) {
                local_interfaces.append(address.toString());
            }
        }
    }
    if (local_interfaces.size() > 0) {
        selected_interface = local_interfaces[0];
    } else {
        selected_interface = QString("0.0.0.0");
    }
}

void UdpEndpointManager::init_from_csv_file()
{
    if (!QFile::exists(m_data_source_csv_path)) {
        return ;
    }
    m_data_sources.clear();

    io::CSVReader<6> csv_in(m_data_source_csv_path.toLocal8Bit().toStdString().c_str());
    csv_in.read_header(io::ignore_extra_column, "ID", "SourceName", "Address", "Interface", "Port", "IsMulticast");

    int id, port, is_multicast;
    std::string std_str_address, std_str_interface, std_str_source_name;

    while (csv_in.read_row(id, std_str_source_name, std_str_address, std_str_interface, port, is_multicast)) {
        QString address = QString::fromStdString(std_str_address),
                interface = QString::fromStdString(std_str_interface),
                source_name = QString::fromStdString(std_str_source_name);
        foreach (QString l_interface, local_interfaces) {
            if (l_interface.compare(interface) == 0)  {
                selected_interface = interface;
            }
        }
        UdpEndpoint data_source(id, source_name, address, interface, port, is_multicast, this);
        m_data_sources.append(data_source);
    }

    int data_source_num = m_data_sources.size();
    for (int i = 0; i < data_source_num; ++i) {
        m_data_sources[i].setInterface(selected_interface);
    }
}
