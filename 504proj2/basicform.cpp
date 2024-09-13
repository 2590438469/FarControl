#include "basicform.h"
#include "ui_basicform.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QTableWidget>
#include <QAxObject>
#include <QMessageBox>
#include <QVBoxLayout>

#include <QDateTime>
#include <QDebug>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "mainwindow.h"
#include <QDir>

#include <QVariant>
#include "config/configinfo.h"

BasicForm::BasicForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BasicForm)
{
    ui->setupUi(this);
}

void BasicForm::initialTablewidget()
{
    ui->tableWidget->setRowCount(rowCount);
    ui->tableWidget->setColumnCount(10);
    QTableWidget *table = ui->tableWidget;

       // 填充表格数据
    table->setItem(0, 0, new QTableWidgetItem("时间"));
    table->setItem(0, 2, new QTableWidgetItem("参谋"));
    table->setItem(0, 4, new QTableWidgetItem("负责人"));
    table->setItem(0, 6, new QTableWidgetItem("进场时间"));
    table->setItem(0, 8, new QTableWidgetItem("开饭时间"));

    table->setItem(1, 0, new QTableWidgetItem("联系电话"));
    table->setItem(1, 2, new QTableWidgetItem("人员"));

    table->setItem(3, 0, new QTableWidgetItem("任务代号"));
    table->setItem(3, 1, new QTableWidgetItem("到位时间"));

    table->setItem(3, 2, new QTableWidgetItem("时间节点(起始)"));
    table->setItem(3, 3, new QTableWidgetItem("时间节点(终止)"));
    table->setItem(3, 4, new QTableWidgetItem("保障内容"));
    table->setItem(3, 5, new QTableWidgetItem("点频"));
    table->setItem(3, 6, new QTableWidgetItem("状态"));
//    table->setItem(3, 7, new QTableWidgetItem("主收端口"));
    table->setItem(3, 7, new QTableWidgetItem("解密端口"));
//    table->setItem(3, 9, new QTableWidgetItem("备份端口"));
    table->setItem(3, 8, new QTableWidgetItem("任务宏"));
    table->setItem(3, 9, new QTableWidgetItem("飞机位置"));

}

void BasicForm::setTableWidgetItem()
{
    QTableWidget *table = ui->tableWidget;
    for(int i=4;i<list.size()+4;i++){
        qDebug() << "循环设置" << i-4;
        table->setItem(i, 0, new QTableWidgetItem(list.at(i-4)->renwudaihao));
        table->setItem(i, 1, new QTableWidgetItem(list.at(i-4)->daoweishijian));
        table->setItem(i, 2, new QTableWidgetItem(list.at(i-4)->shijianjiedianqishi));
        table->setItem(i, 3, new QTableWidgetItem(list.at(i-4)->shijianjiedianzhongzhi));
        table->setItem(i, 4, new QTableWidgetItem(list.at(i-4)->baozhangneirong));
        table->setItem(i, 5, new QTableWidgetItem(list.at(i-4)->dianpin));
        table->setItem(i, 6, new QTableWidgetItem(list.at(i-4)->zhuangtai));
//        table->setItem(i, 7, new QTableWidgetItem(list.at(i-4)->zhuzhouduankou));
        table->setItem(i, 7, new QTableWidgetItem(list.at(i-4)->jiemiduankou));
//        table->setItem(i, 9, new QTableWidgetItem(list.at(i-4)->beifenduankou));
        table->setItem(i, 8, new QTableWidgetItem(list.at(i-4)->renwuhong));
        table->setItem(i, 9, new QTableWidgetItem(list.at(i-4)->feijiweizhi));
    }

    table->setItem(0, 1, new QTableWidgetItem(list.at(0)->shijian));
    table->setItem(0, 3, new QTableWidgetItem(list.at(0)->canmou));
    table->setItem(0, 5, new QTableWidgetItem(list.at(0)->fuzeren));
    table->setItem(0, 7, new QTableWidgetItem(list.at(0)->jinchangshijian));
    table->setItem(0, 9, new QTableWidgetItem(list.at(0)->kaifanshijian));

    table->setItem(1, 1, new QTableWidgetItem(list.at(0)->lianxidianhua));
    table->setItem(1, 3, new QTableWidgetItem(list.at(0)->renyuan));
}

void BasicForm::exportExcel()
{

    QString codestr = ConfigInfo::genMulu;


    QString dateDir = codestr+QString(QDateTime::currentDateTime().toString("/yyyy年MM月dd日"));
    QDir dir2;
    if (!dir2.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }

    dateDir = dateDir+QString("/%1").arg("任务表");
    QDir dir3;
    if (!dir3.mkdir(dateDir)) {
        qDebug() << "Failed to create folder";
    }else{
        qDebug() << "Folder created successfully";
    }



    QTableWidget *tableWidget = ui->tableWidget;
    QString title = QString("任务表");
    QString fileName = dateDir+QString("/")+QString(QDateTime::currentDateTime().toString("hh时mm分"))+QString("任务列表.xls");
    qDebug() << "文件路径2"<< fileName;
        if(fileName != "")
        {
            QAxObject *excel = new QAxObject;
            if(excel->setControl("Excel.Application")) //连接Excel控件
            {
                excel->dynamicCall("SetVisible (bool Visible)","false"); //不显示当前窗体
                excel->setProperty("DisplayAlerts", false); //不显示任何警告消息，如果为true那么在关闭是会出现类似"文件已修改，是否保存"的提示
                QAxObject *workBooks = excel->querySubObject("WorkBooks");//获取工作簿集合
                workBooks->dynamicCall("Add"); //新建一个工作簿
                QAxObject *workBook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
                QAxObject *workSheet = workBook->querySubObject("Worksheets(int)", 1); //获取第一个工作表（后面的参数代表的是第几张工作表）

                int colCount = tableWidget->columnCount();
                int rowCount = tableWidget->rowCount();

                QAxObject *cell, *col;

                //标题行
                cell = workSheet->querySubObject("Cells(int, int)", 1, 1);
                cell->dynamicCall("SetValue(const QString&)", title);
                cell->querySubObject("Font")->setProperty("Size", 18);
                //调整行高
                workSheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
                //合并标题行
                QString cellTitle;
                cellTitle.append("A1:");
                cellTitle.append(QChar(colCount - 1 + 'A'));
                cellTitle.append(QString::number(1));
                QAxObject *range = workSheet->querySubObject("Range(const QString&)", cellTitle);
                range->setProperty("WrapText", true);
                range->setProperty("MergeCells", true);
                range->setProperty("HorizontalAlignment", -4108);
                range->setProperty("VertivcalAlignment", -4108);

                //处理数据
                for (int i = 0; i < rowCount; i++)
                {
                    for (int j = 0; j < colCount; j++)
                    {
                        workSheet->querySubObject("Cells(int, int)", i + 3, j + 1)->dynamicCall(
                                    "SetValue(const QString&)", tableWidget->item(i, j)? tableWidget->item(i, j)->text():"");
                    }
                }

                //画框线
                QString l_range;
                l_range.append("A2:");
                l_range.append(colCount -1 + 'A');
                l_range.append(QString::number(tableWidget->rowCount() + 2));
                range = workSheet->querySubObject("Range(const QString&)", l_range);
                range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
                range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));

                //调整数据区行高
                QString rowsName;
                rowsName.append("2:");
                rowsName.append(QString::number(tableWidget->rowCount() + 2));
                range = workSheet->querySubObject("Range(const QString&)", rowsName);

                range->setProperty("RowHeight", 20);


                range = workSheet->querySubObject("Range(QString, QString)", "A1", "Z50");
                for(int i=1;i<51;i++){
                    QAxObject* columns = range->querySubObject("Columns(int)", i);
                    columns->dynamicCall("AutoFit()");
                }


                workBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(fileName)); //保存到fileName

                workBook->dynamicCall("Close()"); //关闭工作簿
                excel->dynamicCall("Quit()"); //关闭excel
                delete  excel;
            }
            else
            {
                QMessageBox::warning(NULL, tr("错误"), tr("未能创建 Excel 对象，请安装 Microsoft Excel。"), QMessageBox::Apply);
            }
        }
}

BasicForm::~BasicForm()
{
    delete ui;
}

void BasicForm::setRowCount(int count)
{
    rowCount = count;
    ui->tableWidget->setRowCount(rowCount);
}
