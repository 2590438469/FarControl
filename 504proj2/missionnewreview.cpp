#include "missionnewreview.h"
#include "ui_missionnewreview.h"
#include "firstwindow.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "config/configinfo.h"
#include "util/bytemethod.h"

MissionNewReview::MissionNewReview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MissionNewReview)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&MissionNewReview::selectFile);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MissionNewReview::sendFile);
    ui->radioButton->setChecked(true);
    ui->label_26->hide();
    ui->label_25->hide();
    ui->lineEdit_12->hide();
    ui->lineEdit_11->hide();
}

MissionNewReview::~MissionNewReview()
{
    disconnect(this,&MissionNewReview::sendFileInfo,remoteDataWidget,&RemoteDataSingleWidget::setDllInfo);
    delete ui;
}

void MissionNewReview::setItemByCode(QString code,QString missioncode)
{
    qDebug() << "加载宏参数";
    ui->label_38->setText(missioncode);
    for(int i=0;i<macroInfo.size();i++){
        if(macroInfo.at(i)->biaoshi==code){
            ui->lineEdit_17->setText(macroInfo.at(i)->maxing);
            ui->lineEdit_17->setEnabled(false);
            ui->lineEdit->setText(macroInfo.at(i)->malv);
            ui->lineEdit->setEnabled(false);
            ui->lineEdit_2->setText(QString::number(macroInfo.at(i)->zichang));
            ui->lineEdit_2->setEnabled(false);
            ui->lineEdit_3->setText(QString::number(macroInfo.at(i)->zhenchang));
            ui->lineEdit_3->setEnabled(false);
            ui->lineEdit_14->setText(macroInfo.at(i)->zhenmazu);
            ui->lineEdit_14->setEnabled(false);
            ui->lineEdit_4->setText(QString::number(macroInfo.at(i)->zhenmazuchang));
            ui->lineEdit_4->setEnabled(false);
            ui->lineEdit_18->setText(macroInfo.at(i)->fuzhenfangshi);
            ui->lineEdit_18->setEnabled(false);
            ui->lineEdit_5->setText(QString::number(macroInfo.at(i)->fuzhenchang));
            ui->lineEdit_5->setEnabled(false);
            ui->lineEdit_6->setText(QString::number(macroInfo.at(i)->idziweizhi));
            ui->lineEdit_6->setEnabled(false);
            ui->lineEdit_19->setText(QString::number(macroInfo.at(i)->idzijizhi));
            ui->lineEdit_19->setEnabled(false);
            ui->lineEdit_20->setText(macroInfo.at(i)->idzijishu);
            ui->lineEdit_20->setEnabled(false);
            ui->lineEdit_21->setText(macroInfo.at(i)->jiemizhuangtai);
            ui->lineEdit_21->setEnabled(false);
            ui->lineEdit_7->setText(QString::number(macroInfo.at(i)->xunhuanfuzhenweizhi));
            ui->lineEdit_7->setEnabled(false);
            ui->lineEdit_16->setText(macroInfo.at(i)->xunhuanfuzhenmazu);
            ui->lineEdit_16->setEnabled(false);
            ui->lineEdit_22->setText(macroInfo.at(i)->duofuhaojianyan);
            ui->lineEdit_22->setEnabled(false);
            ui->lineEdit_23->setText(macroInfo.at(i)->tpc);
            ui->lineEdit_23->setEnabled(false);
            ui->lineEdit_15->setText(macroInfo.at(i)->kuaitongbuzhenmazu);
            ui->lineEdit_15->setEnabled(false);
            ui->lineEdit_24->setText(QString::number(macroInfo.at(i)->AGC));
            ui->lineEdit_24->setEnabled(false);
            ui->lineEdit_25->setText(macroInfo.at(i)->zhongpindaikuan);
            ui->lineEdit_25->setEnabled(false);
            ui->lineEdit_26->setText(QString::number(macroInfo.at(i)->AFC));
            ui->lineEdit_26->setEnabled(false);
            ui->lineEdit_27->setText(macroInfo.at(i)->AFCmoshi);
            ui->lineEdit_27->setEnabled(false);
            ui->lineEdit_8->setText(QString::number(macroInfo.at(i)->jiaowucha));
            ui->lineEdit_8->setEnabled(false);
            ui->lineEdit_9->setText(macroInfo.at(i)->gongzuodianpin);
            ui->lineEdit_9->setEnabled(false);
            ui->lineEdit_11->setText(macroInfo.at(i)->xinghao);
            ui->lineEdit_11->setEnabled(false);
            ui->lineEdit_12->setText(macroInfo.at(i)->miaoshu);
            ui->lineEdit_12->setEnabled(false);
            ui->lineEdit_13->setText(macroInfo.at(i)->biaoshi);
            ui->lineEdit_13->setEnabled(false);
            ui->lineEdit_10->setText(macroInfo.at(i)->ruanjiemi);
            ui->lineEdit_10->setEnabled(false);
            return;
        }
    }

}

void MissionNewReview::setButtonAble(bool isEnable)
{
    ui->pushButton->setEnabled(isEnable);
    ui->pushButton_2->setEnabled(isEnable);
}

void MissionNewReview::selectFile()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");

    if(filePath.isEmpty()==false){
        QFileInfo info(filePath);
        fileName = info.fileName();
        fileSize = info.size();
        model = ui->lineEdit_11->text();
        status = ui->lineEdit_12->text();
        code = ui->lineEdit_13->text();
        this->filePath = info.absoluteFilePath();

        ui->label_36->setText(fileName);
    }else{
        qDebug() << "文件路劲获取失败";
    }
}

void MissionNewReview::sendFile()
{

    FileInfo *fileInfo = new FileInfo();

    fileInfo->code = code;
    fileInfo->fileName = fileName;
    fileInfo->fileSize = fileSize;
    fileInfo->status = status;
    fileInfo->model = model;
    fileInfo->filePath = filePath;
    fileInfo->parentPath = modelStatus;

    qDebug() << "文件路径?" << filePath;
    QCryptographicHash hash(QCryptographicHash::Md5);
    QFile *file = new QFile();
    file->setFileName(filePath);
    file->open(QIODevice::ReadOnly);

    hash.addData(file);

    qDebug() << "文件md5?" << hash.result();

    QByteArray array;
    if(ui->radioButton->isChecked()){
        array = AgreeMent::sendFileInfo(fileName,fileSize,ui->label_38->text(),0,hash.result(),modelStatus,userName,0,0);
        fileInfo->type = 0;
    }else{
        array = AgreeMent::sendFileInfo(fileName,fileSize,ui->label_38->text(),1,hash.result(),modelStatus,userName,0,0);
        fileInfo->type = 1;
    }
    remoteDataWidget->setDllInfo(fileInfo);
    QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
    udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);
    file->close();
    QMessageBox::information(this,"提示信息","开始传输");
}
