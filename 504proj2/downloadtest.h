#ifndef DOWNLOADTEST_H
#define DOWNLOADTEST_H

#include <QObject>
#include <QWidget>

class DownLoadTest : public QObject
{
    Q_OBJECT
public:
    explicit DownLoadTest(QObject *parent = nullptr);

signals:
    delayDownloadReturn(QString ip,int download);
public slots:
    void downloadTest(QString ip);
};

#endif // DOWNLOADTEST_H
