#include "customtableformline.h"
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
#include <objbase.h>

CustomTableFormLine::CustomTableFormLine(QObject *parent) : QObject(parent)
{

}

void CustomTableFormLine::exportForm(QTableWidget *tableWidget,QString dateDir,QString filename)
{
    HRESULT hr = CoInitialize(nullptr); // 或 CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        // 处理错误
        return ;
    }

    // 在子线程中使用QAxBase

    QString title = QString("电子格栅");
    QString fileName = dateDir+QString(filename)+QString(".xls");
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

        // 释放COM资源
        CoUninitialize();
}
