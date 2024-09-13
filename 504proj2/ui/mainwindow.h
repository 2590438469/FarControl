#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QPluginLoader>
#include <QStringList>

#include "interfaces.h"
#include "databus.h"
#include "view_package_helper.h"
#include "framesender.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStartPause_clicked();
    void flushTimeStamp(const QString &time_str);

    void on_checkBoxIf0803_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    DataBus *databus;
    ViewPackageHelper *viewPackageHelper;
    FrameSender *frameSender;
    QList<FrameParserInterface *> frameParserList;

    int status;
};

#endif // MAINWINDOW_H
