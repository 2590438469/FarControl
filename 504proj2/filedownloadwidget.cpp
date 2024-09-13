#include "filedownloadwidget.h"
#include "ui_filedownloadwidget.h"
#include "singlefilewidget.h"
#include <QDebug>
#include "firstwindow.h"
#include <QFileInfo>
#include "config/configinfo.h"
#include "util/bytemethod.h"

FileDownLoadWidget::FileDownLoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileDownLoadWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&FileDownLoadWidget::uploadGeshan);
}

FileDownLoadWidget::FileDownLoadWidget(QString title,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileDownLoadWidget)
{
    ui->setupUi(this);
    ui->label->setText(title);
}

FileDownLoadWidget::~FileDownLoadWidget()
{
    delete ui;
}

void FileDownLoadWidget::initialFileInfo(QList<FileInfo*> list)
{


}

void FileDownLoadWidget::settype(AgreeMent::FILE_TYPES type)
{
    fileType = type;
    qDebug() << "设置type" << type;
}

void FileDownLoadWidget::setstring(QString text)
{
    ui->label_2->setText(text);
}

void FileDownLoadWidget::uploadGeshan()
{
    if(FirstWindow::role==2){
        QMessageBox::information(this,"提示信息","权限不足");
        return;
    }
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");

    if(filePath.isEmpty()==false){
        QFileInfo info(filePath);
        QString fileName = info.fileName();
        quint64 fileSize = info.size();
        QString filePath = info.absoluteFilePath();

        FileInfo *fileInfo = new FileInfo();

        fileInfo->code = "无";
        fileInfo->fileName = fileName;
        fileInfo->fileSize = fileSize;
        fileInfo->status = "无";
        fileInfo->model = "无";
        fileInfo->filePath = filePath;
        fileInfo->parentPath = ui->label_2->text();

        QCryptographicHash hash(QCryptographicHash::Md5);
        QFile *file = new QFile();
        file->setFileName(filePath);
        file->open(QIODevice::ReadOnly);

        hash.addData(file);


        QByteArray array;

        array = AgreeMent::sendFileInfo(fileName,fileSize,"无",2,hash.result(),ui->label_2->text(),userName,0,0);
        fileInfo->type = 2;
        remoteDataWidget->setDllInfo(fileInfo);

        QHostAddress *addr = new QHostAddress(ConfigInfo::centerIp);
        udpsocket->writeDatagram(ByteMethod::getInvert(array),*addr,ConfigInfo::centerUdpPort);

        file->close();
        QMessageBox::information(this,"传输提示","开始上传");
        this->close();

    }else{
        qDebug() << "文件路劲获取失败";
    }
}

void FileDownLoadWidget::refreshWidget(ChildFileWithParent* withParent)
{
    for(int i=0;i<allWidgetList.size();i++){
        ui->verticalLayout->removeWidget(allWidgetList.at(i));
        allWidgetList.at(i)->deleteLater();
    }
    allWidgetList.clear();
    qDebug() << allWidgetList.size();
    qDebug() << ui->verticalLayout->isEmpty();
    for(int i=0;i<withParent->childList.size();i++){
        SingleFileWidget *widget = new SingleFileWidget();
        widget->setFileSize(withParent->childList.at(i)->fileSize);
        widget->setFileName(withParent->childList.at(i)->fileName);
        qDebug() << "打印parent" << withParent->parent;
        widget->setParent(withParent->parent);
        ui->verticalLayout->addWidget(widget);
        allWidgetList.append(widget);
    }
}

