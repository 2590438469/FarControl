#include "Qwidget.h"
#include <QApplication>
#include <QMutex>
#include <QFile>
#include <QMessageLogContext>
#include <QDebug>
#include <QDateTime>
#include <qapplication.h>
#include <stdio.h>
#include <stdlib.h>
#include "mainwindow.h"
#include <QApplication>
#include "firstwindow.h"

void outputMessage(QtMsgType type,const QMessageLogContext &context,const QString &msg);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qInstallMessageHandler(outputMessage);//安装消息处理程序，关闭后输出在控制台
    MainWindow w;
//    w.show();
    FirstWindow *p = new FirstWindow;
    p->getCurrentUser("admin");
    p->show();
    return a.exec();
}

void outputMessage(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
    static QMutex mutex;
    mutex.lock();
    QByteArray localMsg = msg.toLocal8Bit();
    QString text;
    switch (type)
    {
        case QtDebugMsg:
//            text = QString("Debug:");
//            break;
            mutex.unlock();
            return;
        case QtWarningMsg:
//            text = QString("Warning:");
//            break;
            mutex.unlock();
            return;
        case QtCriticalMsg:
            text = QString("Critical:");
            break;
        case QtFatalMsg:
            text = QString("Fatal:");
            break;
        case QtInfoMsg:
            text = QString("Info:");
            break;
        default:
//            text = QString("Debug:");
            mutex.unlock();
            return;
    }

    // 设置输出信息格式
       QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line); // F文件L行数
       QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
       QString filestrDateTime = QDateTime::currentDateTime().toString("yyyy年MM月dd日");
       //QString strMessage = QString("%1 %2 \t%3 \t%4").arg(text).arg(context_info).arg(strDateTime).arg(msg);
       QString strMessage = QString("%1 \t%2 \t%3").arg(text).arg(strDateTime).arg(msg);
       // 输出信息至文件中（读写、追加形式）
       QFile file(filestrDateTime.append(QString(".txt")));
       bool a = file.open(QIODevice::ReadWrite | QIODevice::Append);
       QTextStream stream(&file);
       stream << strMessage << "\r\n";//格式
       file.flush();
       file.close();
       // 解锁
       mutex.unlock();
}
