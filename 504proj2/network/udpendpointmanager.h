#ifndef DATASOURCEMANAGER_H
#define DATASOURCEMANAGER_H

#include <QObject>
#include <QVector>
#include <QNetworkInterface>
#include <QFile>
#include <QMap>

#include <string>
#include <cstdio>

#include <csv.h>

#include "network/udpendpoint.h"
#include "network/framesender.h"
#include "network/databus.h"

class UdpEndpointManager : public QObject
{
    Q_OBJECT
public:
    explicit UdpEndpointManager(
        const QString &data_source_csv_path,
        QObject *parent = nullptr);
    void toCsvFile();
    void reloadCsvFile();
    void addDataSource(const UdpEndpoint &data_source);
    void removeDataSource(int id);
    QVector<UdpEndpoint> *getDataSourceVector();
    void setSelectedInterface(const QString &str_interface);
    QString getSelectedInterface() const;
    DataBus* getDataBus(int index);
    FrameSender* getFrameSender(int index);
    FrameSender* getFrameSenderByName(const QString &frame_sender_name);
private:
    QVector<UdpEndpoint> m_data_sources;
    QVector<QString> local_interfaces;
    QMap<int, DataBus*> data_bus_ptr_map;
    QMap<int, FrameSender*> frame_sender_ptr_map;
    QString selected_interface;
    QString m_data_source_csv_path;

    void init_local_interfaces();
    void init_from_csv_file();
};

#endif // DATASOURCEMANAGER_H
