#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() == QAbstractSocket::IPv4Protocol) {
           ui->comboBoxSendInterface->addItem(address.toString());
           ui->comboBoxRecvInterface->addItem(address.toString());
       }
    }

    QDir frame_parsers_dir = QDir(qApp->applicationDirPath());
    frame_parsers_dir.cd("frameparsers");

    const auto entryList = frame_parsers_dir.entryList(QDir::Files);
    for (const QString &fileName : entryList) {
        if (!fileName.endsWith("dll")) continue;
        QPluginLoader loader(frame_parsers_dir.absoluteFilePath(fileName));
        QObject *frame_parser_obj = loader.instance();
        if (frame_parser_obj) {
            FrameParserInterface *frame_parser = qobject_cast<FrameParserInterface *>(frame_parser_obj);
            if (frame_parser != nullptr) {
                QString plane_name = frame_parser->PlaneName();
                QString plane_no = frame_parser->PlaneNo();
                QString config_file_path = QString("%1/%2_%3_config.txt").arg(frame_parsers_dir.path()).arg(plane_name).arg(plane_no);
                QString params_file_path = QString("%1/%2_%3_params.txt").arg(frame_parsers_dir.path()).arg(plane_name).arg(plane_no);

                FILE *config_file, *params_file;
                config_file = fopen(config_file_path.toLocal8Bit().toStdString().c_str(), "r");
                if (config_file != nullptr) {
                    frame_parser->setConfigFile(config_file);
                    fclose(config_file);
                }

                params_file = fopen(params_file_path.toLocal8Bit().toStdString().c_str(), "r");
                if (params_file != nullptr) {
                    frame_parser->setParamsFile(params_file);
                    fclose(params_file);
                }

                frameParserList.append(frame_parser);
                ui->comboBoxDecoderConfig->addItem(frame_parser->FParserName());
            }
        }
    }

    databus = nullptr;
    viewPackageHelper = nullptr;
    frameSender = nullptr;
    status = 0;
}

MainWindow::~MainWindow()
{
    if (status) {
        disconnect(databus, SIGNAL(packageArrived(const char*,int)),
                viewPackageHelper, SLOT(onPackageArrived(const char*,int)));
        disconnect(viewPackageHelper, SIGNAL(resultReady(const char*,int)),
                frameSender, SLOT(onFrameReady(const char*,int)));
        disconnect(viewPackageHelper, SIGNAL(timeStampRaised(QString)),
                this, SLOT(flushTimeStamp(QString)));
    }
    delete databus;
    delete viewPackageHelper;
    delete frameSender;

    delete ui;
}

void MainWindow::on_pushButtonStartPause_clicked()
{
    if (status) {
        disconnect(databus, SIGNAL(packageArrived(const char*,int)),
                viewPackageHelper, SLOT(onPackageArrived(const char*,int)));
        disconnect(viewPackageHelper, SIGNAL(resultReady(const char*,int)),
                frameSender, SLOT(onFrameReady(const char*,int)));
        disconnect(viewPackageHelper, SIGNAL(timeStampRaised(QString)),
                this, SLOT(flushTimeStamp(QString)));
        delete databus;
        delete viewPackageHelper;
        delete frameSender;
        databus = nullptr;
        viewPackageHelper = nullptr;
        frameSender = nullptr;
        status = 0;
        ui->pushButtonStartPause->setText(tr("开始"));
    } else {
        const QString &sendAddress = ui->lineEditSendAddr->text();
        int sendPort = ui->lineEditSendPort->text().toInt();
        bool sendBroadcast = ui->checkBoxSendIfBroadcast->isChecked();
        const QString &sendInterface = ui->comboBoxSendInterface->currentText();

        const QString &recvAddress = ui->lineEditRecvAddr->text();
        int recvPort = ui->lineEditRecvPort->text().toInt();
        bool recvBroadcast = ui->checkBoxRecvIfBroadcast->isChecked();
        const QString &recvInterface = ui->comboBoxRecvInterface->currentText();

        int streamNo = ui->lineEditSendNo->text().toInt();

        databus = new DataBus(recvAddress, recvInterface, recvPort, recvBroadcast, this);
        qDebug() << "Start Databus.";


        viewPackageHelper = new ViewPackageHelper(
            streamNo,
            frameParserList[ui->comboBoxDecoderConfig->currentIndex()],
            this
        );

        qDebug() << "Start TempFrameParser.";
        frameSender = new FrameSender(sendAddress, sendInterface, sendPort, sendBroadcast, this);
        qDebug() << "Start FrameSender.";

        connect(databus, SIGNAL(packageArrived(const char*,int)),
                viewPackageHelper, SLOT(onPackageArrived(const char*,int)));
        connect(viewPackageHelper, SIGNAL(resultReady(const char*,int)),
                frameSender, SLOT(onFrameReady(const char*,int)));
        connect(viewPackageHelper, SIGNAL(timeStampRaised(QString)),
                this, SLOT(flushTimeStamp(QString)));

        qDebug() << "Connect all signals.";

        status = 1;
        ui->pushButtonStartPause->setText(tr("结束"));
        databus->start();
    }
}

void MainWindow::flushTimeStamp(const QString &time_str)
{
    ui->labelTimeStamp->setText(time_str);
}

void MainWindow::on_checkBoxIf0803_stateChanged(int arg1)
{
    if (arg1) {
        ui->lineEditSendAddr->setText("224.1.1.5");
        ui->lineEditSendPort->setText("7777");
    } else {
        ui->lineEditSendAddr->setText("225.1.1.1");
        ui->lineEditSendPort->setText("8888");
    }
}
