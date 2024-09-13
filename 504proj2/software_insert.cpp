#include "software_insert.h"

#include <QDebug>
#include <QWidget>
#include <QProcess>
#include <QWindow>
#include <Windows.h>
#include <QTimer>
#include <QVBoxLayout>
#include <QThread>
#include "config/configinfo.h"

Software_insert::Software_insert()
{

}

QWidget* Software_insert::softwareInsert(QLayout *layout,QWidget *widget, const QString &programPath)
{

    process.start(programPath, QStringList() << "");
    qDebug() << "开始启动";


    process.waitForStarted(30000);
    qDebug() << "启动完成";
    qDebug() <<"等待时间" << ConfigInfo::waitTime.toInt();
        QThread::sleep(ConfigInfo::waitTime.toInt());

        qDebug() << programPath;
        WId wid = (WId)FindWindow(L"Qt5QWindowIcon", L"综合数据处理软件");
        qDebug() << "wid" << wid;

        QWindow *m_window = QWindow::fromWinId(wid);
        m_window->setFlags(m_window->flags() | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        qDebug() << m_window->title();

        // 创建一个新的QWidget并指向widget
        QWidget *newWidget = QWidget::createWindowContainer(m_window);
        newWidget->setWindowTitle("www");

        // 将新的QWidget添加到ui->verticalLayout_9
        layout->addWidget(newWidget);

        bool ok = m_window->close();
        if (ok) {
            qDebug() << "成功";
        } else {
            qDebug() << "失败";
        }
        qDebug() << programPath << "1";

        // 将原始的widget指针指向新创建的QWidget
        widget = newWidget;

        qDebug() << "1";

        return widget;
}

QWidget *Software_insert::softwareInsert2(QLayout *layout, QWidget *widget, const QString &programPath)
{
    process.start(programPath, QStringList() << "");

        QThread::sleep(1);

        qDebug() << programPath;
        WId wid = (WId)FindWindow(L"Qt5QWindowIcon", L"totalConfig");
        qDebug() << "wid" << wid;

        QWindow *m_window = QWindow::fromWinId(wid);
        m_window->setFlags(m_window->flags() | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
        qDebug() << m_window->title();

        // 创建一个新的QWidget并指向widget
        QWidget *newWidget = QWidget::createWindowContainer(m_window);
        newWidget->setWindowTitle("www");

        // 将新的QWidget添加到ui->verticalLayout_9
        layout->addWidget(newWidget);

        bool ok = m_window->close();
        if (ok) {
            qDebug() << "成功";
        } else {
            qDebug() << "失败";
        }
        qDebug() << programPath << "1";

        // 将原始的widget指针指向新创建的QWidget
        widget = newWidget;

        qDebug() << "1";

        return widget;
}

