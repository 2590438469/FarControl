#ifndef STREAMSMAINWINDOW_H
#define STREAMSMAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QDir>
#include <QPluginLoader>

#include "ui\flowstatuspanel.h"
#include "ui\udpendpointdialog.h"
#include "configmodel.h"
#include "ui\modulemanagerdialog.h"
#include "ui\setupmanagerdialog.h"
#include "ui\parsedatfiledialog.h"
#include "network/udpendpointmanager.h"

namespace Ui {
class StreamsMainWindow;
}

class StreamsMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StreamsMainWindow(QWidget *parent = nullptr);
    ~StreamsMainWindow();

private slots:
    void on_actionOpenDataSourceConfigDialog_triggered();

    void on_actionViewModules_triggered();

    void on_pushButtonAddStream_clicked();

    void on_actionAddDataFlow_triggered();

    void on_removePanel(int uid);

    void on_actionOpenFrameSenderConfigDialog_triggered();

    void on_actionViewSetups_triggered();

    void on_actionParseDatFile_triggered();

private:
    Ui::StreamsMainWindow *ui;
    UdpEndpointManager *m_data_source_manager;
    UdpEndpointDialog *data_source_dialog;

    UdpEndpointManager *m_frame_sender_manager;
    UdpEndpointDialog *frame_sender_dialog;

    ModuleManagerDialog *m_module_manager_dialog;
    SetupManagerDialog *m_setup_manager_dialog;
    ParseDatFileDialog *m_parse_dat_file_dialog;

    QVBoxLayout *stream_group_layout;

    QVector<ConfigModel *> config_models;
    QList<ModuleInterface *> modules_list;
    QList<FlowStatusPanel *> panel_list;
    int m_uid_count;
    void init_setups();
    void init_modules();
    void stop_all();
};

#endif // STREAMSMAINWINDOW_H
