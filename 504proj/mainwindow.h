#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QSqlDatabase>
#include <QUdpSocket>

/*
 *    0:遥测文件上传
 *    1:遥测文件下载
 *    2:格栅文件上传
 *    3:格栅文件下载
*/

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


    void post(QString name,QString password);
    void postback(QNetworkReply * reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager * manager;
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void sendUser(QString);
public slots:
    void judgePass();
};
#endif // MAINWINDOW_H
