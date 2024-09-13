#ifndef FLOWSTATUSPANEL_H
#define FLOWSTATUSPANEL_H

#include <QFrame>
#include <QVector>
#include <QDebug>

#include "network/udpendpointmanager.h"
#include "configmodel.h"
#include "network/databus.h"
#include "frameparserwithmodules.h"
#include "network/view_package_helper.h"
#include "network/framesender.h"

namespace Ui {
class FlowStatusPanel;
}

class FlowStatusPanel : public QFrame
{
    Q_OBJECT
public:
    explicit FlowStatusPanel(
            UdpEndpointManager *data_source_manager,
            UdpEndpointManager *frame_sender_manager,
            QVector<ConfigModel *> *config_models,
            QList<ModuleInterface *> *modules_factory,
            QWidget *parent = nullptr);

    ~FlowStatusPanel();
    void flushDataSources();
    void flushConfigModels();
    void setFlowNum(int flow_num);
    void switchDataSourceToCurrent();
    void stop();
    void start();
    int uid;
public slots:
    void flushTimeStamp(const QString &timestamp);
private slots:
    void on_comboBoxSetup_currentIndexChanged(int index);
    void on_pushButtonStartPause_clicked();
    void on_comboBoxDataSource_currentIndexChanged(int index);
    void on_pushButtonRemove_clicked();

signals:
    void removePanel(int uid);
private:
    Ui::FlowStatusPanel *ui;
    UdpEndpointManager *m_data_source_manager, *m_frame_sender_manager;
    QVector<ConfigModel *> *m_config_models;
    QList<ModuleInterface *> *m_modules_factory;
    DataBus *databus;
    FrameParserWithModules *frame_parser;
    ViewPackageHelper *view_package_helper;
    FrameSender *frame_sender;
    int is_started;
    int m_flow_num;
};

#endif // FLOWSTATUSPANEL_H
