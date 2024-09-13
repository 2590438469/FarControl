#include "remotedatawidget.h"
#include "ui_remotedatawidget.h"
#include "remotedatasinglewidget.h"
#include <QDebug>
#include "config/configinfo.h"

RemoteDataSingleWidget *remoteDataWidget;
RemoteDataSingleWidget *fileDownload1;
RemoteDataSingleWidget *fileDownload2;
RemoteDataWidget::RemoteDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteDataWidget)
{
    ui->setupUi(this);
    remoteDataWidget = new RemoteDataSingleWidget();
    remoteDataWidget->setType("文件上传");
    remoteDataWidget->setDirectory(ConfigInfo::genMulu);
    remoteDataWidget->isHideMissionInfo(true);
    fileDownload1 = new RemoteDataSingleWidget();
    fileDownload1->setType("文件下载");
    fileDownload1->setDirectory(ConfigInfo::geShanMulu);
    fileDownload1->isHideMissionInfo(false);
    ui->verticalLayout->addWidget(remoteDataWidget);
    ui->verticalLayout->addWidget(fileDownload1);
    qDebug() << "加载";
}

RemoteDataWidget::~RemoteDataWidget()
{
    delete ui;
}

void RemoteDataWidget::setFileInfo(FileInfo *info, AgreeMent::FILE_TYPES type)
{

    qDebug() << "jieshou setFileInfo信号";
    if(type==AgreeMent::GRILLE){
        fileDownload1->setFileInfo(info);
    }else if((type==AgreeMent::DISPLAY)){
        fileDownload1->setFileInfo(info);
    }
}
