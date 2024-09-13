#include "singlefilewidget.h"
#include "ui_singlefilewidget.h"
#include "firstwindow.h"
#include "config/configinfo.h"
#include "agreement/agreement.h"
#include "util/bytemethod.h"

SingleFileWidget::SingleFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleFileWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&SingleFileWidget::deleteFileButtonSlot);
}

SingleFileWidget::~SingleFileWidget()
{
    delete ui;
}

void SingleFileWidget::setFileName(QString fileName)
{
    ui->label_2->setText(fileName);
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        FileInfo *info = new FileInfo();
        info->fileName = ui->label_2->text();
        info->fileSize = size;

        qDebug() <<"打印大小" << size;
        fileDownload1->setFileInfo(info);

        grilleWorker->fileDirectoryPath = ConfigInfo::geShanMulu;
        grilleWorker->setFileName(ui->label_2->text());
        grilleWorker->parentString = parentString;
        grilleWorker->setFileSize(size);



        QHostAddress addre;
        addre.setAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDownloadDianziRequest(parentString,ui->label_2->text(),userName)),addre,ConfigInfo::centerUdpPort);

        QMessageBox::information(this,"提示信息","开始下载");
    });
}

void SingleFileWidget::setFileType(AgreeMent::FILE_TYPES fileType)
{
    type = fileType;
}

void SingleFileWidget::setFileSize(quint64 fileSize)
{
    size = fileSize;
}

void SingleFileWidget::setParent(QString parentString)
{
    this->parentString = parentString;
}

void SingleFileWidget::deleteFileButtonSlot()
{
    if(FirstWindow::role!=0){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    QString str("是否确认删除%1");
    str = str.arg(ui->label_2->text());
    int rep = QMessageBox::question(this,"警告",str);
    if(rep == QMessageBox::Yes)
    {
        QHostAddress addre;
        addre.setAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(AgreeMent::sendDeleteChildGeshan(ui->label_2->text(),parentString)),addre,ConfigInfo::centerUdpPort);
    }
}

