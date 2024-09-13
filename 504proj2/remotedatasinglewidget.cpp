#include "remotedatasinglewidget.h"
#include "ui_remotedatasinglewidget.h"
#include <QDebug>
#include <QFileInfo>
#include "firstwindow.h"
#include "mainwindow.h"
#include "util/bytemethod.h"
#include "config/configinfo.h"

RemoteDataSingleWidget::RemoteDataSingleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteDataSingleWidget)
{
    ui->setupUi(this);
    t = new QThread;
    worker = new  SendDllFile;
    worker->moveToThread(t);

//    connect(this,&missionreview::sendFile,worker,&SendFile::sendFile);
    connect(this,&RemoteDataSingleWidget::sendFileSignal,worker,& SendDllFile::sendFile);
    connect(worker,&SendDllFile::sendProgress,this,&RemoteDataSingleWidget::refreshProgress);
    connect(worker,&SendDllFile::sendMd5Judge,this,&RemoteDataSingleWidget::sendMd5Judge);
    connect(this,&RemoteDataSingleWidget::pause,worker,&SendDllFile::getpaused);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
    });
    t->start();
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        QDesktopServices::openUrl(QUrl::fromLocalFile(directory));
    });
    ui->pushButton->setEnabled(false);

    ui->pushButton_3->setEnabled(false);
    connect(ui->pushButton,&QPushButton::clicked,[=](){

        QCryptographicHash hash(QCryptographicHash::Md5);
        QFile *file = new QFile();
        file->setFileName(filePath);
        file->open(QIODevice::ReadOnly);

        hash.addData(file);

        qDebug() << "文件md5?" << hash.result();

        QByteArray array;

        array = AgreeMent::sendFileInfo(ui->label_3->text(),filesize,ui->label_9->text(),type,hash.result(),parentPath,userName,0,1);


        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);

        file->close();
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::Datamd5StorgeFinish(grilleWorker->fileName,grilleWorker->nowsize,"")),QHostAddress(ConfigInfo::centerIp),ConfigInfo::centerUdpPort);
    });
    ui->pushButton_2->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
}

RemoteDataSingleWidget::~RemoteDataSingleWidget()
{
    delete ui;
}

void RemoteDataSingleWidget::setType(QString type)
{
    ui->label_2->setText(type);
}

void RemoteDataSingleWidget::isHideMissionInfo(bool isMission)
{
    if(!isMission){
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_6->setText("");
        ui->label_7->setText("");
        ui->label_8->setText("");
        ui->label_9->setText("");
        ui->pushButton->hide();
    }else{
        connect(worker,&SendDllFile::abortConnect,this,&RemoteDataSingleWidget::getAbort);
        ui->pushButton_3->hide();
    }
}

void RemoteDataSingleWidget::setFileInfo(FileInfo *info)
{
    ui->label_3->setText(info->fileName);
    if(info->fileSize>2147483647){
        downloadType = 1;
        ui->progressBar->setMaximum(info->fileSize/10);
    }else{
        downloadType = 0;
        ui->progressBar->setMaximum(info->fileSize);
    }
    allSize = info->fileSize;
    ui->pushButton->setEnabled(false);
}

void RemoteDataSingleWidget::setValue(quint64 value)
{
    nowsize = value;
    if(downloadType){
        ui->progressBar->setValue(value/10);
    }else{
        ui->progressBar->setValue(value);
    }
}

void RemoteDataSingleWidget::setDllInfo(FileInfo *info)
{
    qDebug() << "设置文件信息" << info->filePath;
    ui->label_3->setText(info->fileName);
    ui->label_5->setText(info->model);
    ui->label_7->setText(info->status);
    ui->label_9->setText(info->code);
    filePath = info->filePath;
    type = info->type;
    filesize = info->fileSize;
    if(info->fileSize>2147483647){
        ui->progressBar->setMaximum(info->fileSize/10);
        sizeType = 1;
    }
    else {
        ui->progressBar->setMaximum(info->fileSize);
        sizeType = 0;
    }
    parentPath = info->parentPath;
}

void RemoteDataSingleWidget::setDirectory(QString dir)
{
    directory = dir;
}

void RemoteDataSingleWidget::setButtonEnabled()
{
    ui->pushButton_3->setEnabled(true);
}

void RemoteDataSingleWidget::startSendingFile(quint64 nowSize)
{
    QFileInfo info(filePath);
    qDebug() << "dll文件路径"<< filePath;
    emit sendFileSignal(filePath,nowSize);
}

void RemoteDataSingleWidget::refreshProgress(quint64 nowSize, quint64 allSize)
{
    if(sizeType){
        ui->progressBar->setValue(nowSize/10);
    }else{
        ui->progressBar->setValue(nowSize);
    }
}

void RemoteDataSingleWidget::sendMd5Judge(QByteArray md5byte)
{
    if(type == 0){
        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDllMd5(md5byte)),*addr,ConfigInfo::centerUdpPort);

    }else if(type == 1){

    }
}

void RemoteDataSingleWidget::getMd5Result(quint8 md5Result)
{
    if(md5Result) QMessageBox::information(this,"传输结果","文件上传完成");
    else          QMessageBox::information(this,"传输结果","文件上传失败");

    ui->label_3->setText("无");
    ui->label_5->setText("无");
    ui->label_7->setText("无");
    ui->label_9->setText("无");

    ui->progressBar->setValue(0);
    
    folderFileList.removeAt(1);
    emit sendFinishSend();
    ui->pushButton->setEnabled(false);
}

void RemoteDataSingleWidget::okReceieve()
{
    QMessageBox::information(this,"文件下载提示信息","文件下载完成");
    ui->label_3->setText("无");
    ui->label_5->setText("无");
    ui->label_7->setText("无");
    ui->label_9->setText("无");
    ui->progressBar->setValue(0);
    nowsize = 0;
    ui->pushButton_3->setEnabled(false);
}

void RemoteDataSingleWidget::falseReceieve()
{
    QMessageBox::information(this,"文件下载提示信息","文件下载失败");
    ui->label_3->setText("无");
    ui->label_5->setText("无");
    ui->label_7->setText("无");
    ui->label_9->setText("无");
    ui->progressBar->setValue(0);
    nowsize = 0;
}

void RemoteDataSingleWidget::getAbort()
{
    QMessageBox::information(this,"传输提示","传输中断");
    ui->pushButton->setEnabled(true);
}
