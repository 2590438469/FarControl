#include "ui/flowstatuspanel.h"
#include "ui_flowstatuspanel.h"


FlowStatusPanel::FlowStatusPanel(UdpEndpointManager *data_source_manager,
                                 UdpEndpointManager *frame_sender_manager,
                                 QVector<ConfigModel *> *config_models,
                                 QList<ModuleInterface *> *modules_factory,
                                 QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FlowStatusPanel)
{
    ui->setupUi(this);
    m_data_source_manager = data_source_manager;
    m_frame_sender_manager = frame_sender_manager;
    m_config_models = config_models;
    m_modules_factory = modules_factory;
    frame_parser = nullptr;
    is_started = 0;
    setFlowNum(1);
    flushDataSources();
    flushConfigModels();
    databus = nullptr;
    frame_sender = nullptr;
    view_package_helper = nullptr;
}

FlowStatusPanel::~FlowStatusPanel()
{
    if (is_started) {
        disconnect(databus, SIGNAL(packageArrived(const char*,int)),
                view_package_helper, SLOT(onPackageArrived(const char*,int)));
        disconnect(view_package_helper, SIGNAL(resultReady(const char*,int)),
                frame_sender, SLOT(onFrameReady(const char*,int)));
        disconnect(view_package_helper, SIGNAL(timeStampRaised(QString)),
                this, SLOT(flushTimeStamp(QString)));

        if (databus != nullptr) {
            databus->disSubscribe();
        }
    }
    delete view_package_helper;
    delete frame_sender;
    delete ui;
}

void FlowStatusPanel::flushDataSources()
{
    QVector<UdpEndpoint> *data_sources = m_data_source_manager->getDataSourceVector();
    for (int i = 0; i < data_sources->size(); ++i) {
        ui->comboBoxDataSource->addItem((*data_sources)[i].getSourceName());
    }
}

void FlowStatusPanel::flushConfigModels()
{
    for (int i = 0; i < m_config_models->size(); ++i) {
        ui->comboBoxSetup->addItem((*m_config_models)[i]->getSetupName());
    }
}

void FlowStatusPanel::setFlowNum(int flow_num)
{
    m_flow_num = flow_num;
    ui->lineEditDataFlowNum->setText(tr("%1").arg(m_flow_num));
}

void FlowStatusPanel::switchDataSourceToCurrent()
{
    if (!is_started) {
        return ;
    }
    if (databus != nullptr) {
        disconnect(databus, SIGNAL(packageArrived(const char*,int)),
                   view_package_helper, SLOT(onPackageArrived(const char*,int)));
        databus->disSubscribe();
    }
    int data_source_index = ui->comboBoxDataSource->currentIndex();
    databus = m_data_source_manager->getDataBus(data_source_index);

    connect(databus, SIGNAL(packageArrived(const char*,int)),
            view_package_helper, SLOT(onPackageArrived(const char*,int)));
    databus->subscribe();
}

void FlowStatusPanel::flushTimeStamp(const QString &timestamp)
{
    ui->labelStreamTimeStamp->setText(timestamp);
}

//void FlowStatusPanel::onDataArrived(const char *pkg, int pkg_len)
//{
//    qDebug() << "Package Arrived : " << pkg_len;

//}

void FlowStatusPanel::on_comboBoxSetup_currentIndexChanged(int index)
{
    ui->labelStreamConfigName->setText(
        QString("[%1]%2_%3:%4")
        .arg((*m_config_models)[index]->viewParamInfo.packageHead)
        .arg((*m_config_models)[index]->viewParamInfo.planeName)
        .arg((*m_config_models)[index]->viewParamInfo.planeNo)
        .arg((*m_config_models)[index]->name)
    );
}

void FlowStatusPanel::on_pushButtonStartPause_clicked()
{
    if (is_started) {
        stop();
    } else {
        start();
    }
}

void FlowStatusPanel::on_comboBoxDataSource_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    switchDataSourceToCurrent();
}

void FlowStatusPanel::on_pushButtonRemove_clicked()
{
    stop();
    emit removePanel(uid);
}

void FlowStatusPanel::stop()
{
    if (is_started) {
        ui->pushButtonStartPause->setText("开始");
        ui->comboBoxSetup->setEnabled(true);
        qDebug() << "Dissubscribe databus.";
        databus->disSubscribe();
        qDebug() << "disconnect signals.";
        disconnect(databus, SIGNAL(packageArrived(const char*,int)),
                view_package_helper, SLOT(onPackageArrived(const char*,int)));
        if (frame_sender != nullptr) {
            disconnect(view_package_helper, SIGNAL(resultReady(const char*,int)),
                    frame_sender, SLOT(onFrameReady(const char*,int)));
        }
        disconnect(view_package_helper, SIGNAL(timeStampRaised(QString)),
                this, SLOT(flushTimeStamp(QString)));
        databus = nullptr;
        frame_sender = nullptr;
        qDebug() << "delete helper and parser.";
        delete view_package_helper;
        //delete frame_sender;
        delete frame_parser;
        view_package_helper = nullptr;
        frame_sender = nullptr;
        is_started = 0;
    }
}

void FlowStatusPanel::start()
{
    ui->pushButtonStartPause->setText("停止");
    ui->comboBoxSetup->setEnabled(false);
    int streamNo = ui->lineEditDataFlowNum->text().toInt();

    qDebug() << "Init frame parser.";

    frame_parser = new FrameParserWithModules(this);
    qDebug() << "setModulesFactory.";
    frame_parser->setModulesFactory(m_modules_factory);
    qDebug() << "setConfigModel.";
    frame_parser->setConfigModel((*m_config_models)[ui->comboBoxSetup->currentIndex()]);
    qDebug() << "Create view_package_helper.";
    view_package_helper = new ViewPackageHelper(
        streamNo,
        frame_parser,
        this
    );
    qDebug() << "Get frame_sender.";
    frame_sender = m_frame_sender_manager->getFrameSenderByName(
                (*m_config_models)[ui->comboBoxSetup->currentIndex()]->viewParamInfo.frameSenderName
            );
    qDebug() << frame_sender;
    is_started = 1;
    qDebug() << "connect signals.";
    if (frame_sender != nullptr) {
        connect(view_package_helper, SIGNAL(resultReady(const char*,int)),
                frame_sender, SLOT(onFrameReady(const char*,int)));
    }
    connect(view_package_helper, SIGNAL(timeStampRaised(QString)),
            this, SLOT(flushTimeStamp(QString)));
    qDebug() << "Switch DataSource to current.";
    switchDataSourceToCurrent();
}
