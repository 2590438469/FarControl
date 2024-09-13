#include "ui/streamsmainwindow.h"
#include "ui_streamsmainwindow.h"

StreamsMainWindow::StreamsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StreamsMainWindow)
{
    ui->setupUi(this);
    m_data_source_manager = new UdpEndpointManager("DataSources.csv");
    data_source_dialog = new UdpEndpointDialog(m_data_source_manager, this);

    m_frame_sender_manager = new UdpEndpointManager("FrameSender.csv");
    frame_sender_dialog = new UdpEndpointDialog(m_frame_sender_manager, this);

    m_module_manager_dialog = nullptr;//new ModuleManagerDialog(this);
    m_setup_manager_dialog = nullptr;//new SetupManagerDialog(this);
    m_parse_dat_file_dialog = new ParseDatFileDialog(this);
    init_modules();
    init_setups();

    stream_group_layout = new QVBoxLayout(ui->groupBoxStreams);
    m_uid_count = 0;

    ui->groupBoxStreams->setLayout(stream_group_layout);
}

StreamsMainWindow::~StreamsMainWindow()
{
    stop_all();
    foreach (ConfigModel *config_model, config_models) {
        delete config_model;
    }
    delete m_data_source_manager;
    delete data_source_dialog;
    delete m_module_manager_dialog;
    delete ui;
}

void StreamsMainWindow::on_actionOpenDataSourceConfigDialog_triggered()
{
    data_source_dialog->show();
}

void StreamsMainWindow::init_setups()
{
    config_models.clear();
    QDir dir_setups = QDir(qApp->applicationDirPath());
    dir_setups.cd("setups");
    if (dir_setups.exists()) {
        QStringList dir_list = dir_setups.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);

        foreach (QString dir_path, dir_list) {
            ConfigModel *config_model = new ConfigModel(tr("%1/%2").arg("setups", dir_path));
            config_models.append(config_model);
        }
    }
}

void StreamsMainWindow::init_modules()
{
    QDir modules_dir = QDir(qApp->applicationDirPath());
    modules_dir.cd("modules");

    const auto entryList = modules_dir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        if (!fileName.endsWith("dll")) continue;
        QPluginLoader loader(modules_dir.absoluteFilePath(fileName));
        QObject *module_factory_obj = loader.instance();
        if (module_factory_obj) {
            ModuleInterface *module_factory = qobject_cast<ModuleInterface *>(module_factory_obj);
            if (module_factory != nullptr) {
                modules_list.append(module_factory);
            }
        }
    }
}

void StreamsMainWindow::stop_all()
{
    for (int i = 0; i < panel_list.size(); ++i) {
        panel_list[i]->stop();
    }
}

void StreamsMainWindow::on_actionViewModules_triggered()
{
    delete m_module_manager_dialog;
    m_module_manager_dialog = new ModuleManagerDialog(this);
    m_module_manager_dialog->setModuleFactoryList(&modules_list);
    m_module_manager_dialog->show();
}

void StreamsMainWindow::on_pushButtonAddStream_clicked()
{
    ui->actionAddDataFlow->trigger();
}

void StreamsMainWindow::on_actionAddDataFlow_triggered()
{
    FlowStatusPanel *flow_status_panel =
            new FlowStatusPanel(
                m_data_source_manager,
                m_frame_sender_manager,
                &config_models,
                &modules_list,
                ui->groupBoxStreams);
    flow_status_panel->uid = m_uid_count++;
    panel_list.append(flow_status_panel);
    connect(flow_status_panel, SIGNAL(removePanel(int)),
            this, SLOT(on_removePanel(int)));
    stream_group_layout->addWidget(flow_status_panel);
}

void StreamsMainWindow::on_removePanel(int uid)
{
    qDebug() << "Remove panel : " << uid;
    int index = 0;
    foreach (FlowStatusPanel *flow_status_panel, panel_list) {
        if (flow_status_panel->uid == uid) {
            stream_group_layout->removeWidget(flow_status_panel);

            panel_list.removeAt(index);
            delete flow_status_panel;
            stream_group_layout->update();
        }

        ++index;
    }
}

void StreamsMainWindow::on_actionOpenFrameSenderConfigDialog_triggered()
{
    frame_sender_dialog->show();
}

void StreamsMainWindow::on_actionViewSetups_triggered()
{
    delete m_setup_manager_dialog;
    m_setup_manager_dialog = new SetupManagerDialog(this);
    m_setup_manager_dialog->setConfigModels(&config_models);
    m_setup_manager_dialog->show();
}

void StreamsMainWindow::on_actionParseDatFile_triggered()
{
    m_parse_dat_file_dialog->initDialog(&config_models, &modules_list);
    m_parse_dat_file_dialog->show();
}
