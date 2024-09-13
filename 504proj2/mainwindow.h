#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QSqlDatabase>
#include <QUdpSocket>
#include "receievedata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
extern QString response;
extern QString name;
extern QSqlDatabase db;
//extern QUdpSocket *socket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    receieveData *worker;

    void post(QString name,QString password);
    void postback(QNetworkReply * reply);

    QByteArray PackLastNameQuest();
    void SendLastNameQuest();
    QByteArray PackLoginInfo();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager * manager;
    bool eventFilter(QObject *watched, QEvent *event);
    QByteArray getInvert(QByteArray array);

signals:
    //void sendUser(QString);
    void sendSocketData(quint64 pend,QByteArray arrayjudge,QHostAddress addr,quint16 port);

public slots:
    void login(receieveData::opResult opresult);
    void setLastname(QString lastname);
    void readPendingDatagrams();
    void SendLoginInfo();
};
#endif // MAINWINDOW_H
