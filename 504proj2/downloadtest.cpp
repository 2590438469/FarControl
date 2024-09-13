#include "downloadtest.h"
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QElapsedTimer>

DownLoadTest::DownLoadTest(QObject *parent) : QObject(parent)
{

}

void DownLoadTest::downloadTest(QString ip)
{
    qDebug() << "下载速度测试线程";
    QNetworkAccessManager manager;
    QUrl url; // 替换为目标IP地址或域名
    url.setHost(ip);
    QNetworkRequest request(url);

    QElapsedTimer timer;
    qint64 lastBytesReceived = 0;
    timer.start();

    QNetworkReply* reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::downloadProgress, [&](qint64 bytesReceived, qint64 /*bytesTotal*/) {
        qint64 elapsed = timer.elapsed();
        double downloadSpeed = (bytesReceived - lastBytesReceived) / (elapsed / 1000.0) / 1024.0; // 单位：KB/s
        qDebug() << "Download speed:" << downloadSpeed << "KB/s";
        lastBytesReceived = bytesReceived;
        emit delayDownloadReturn(ip,downloadSpeed);
    });

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        qint64 elapsed = timer.elapsed();
        double downloadSpeed = reply->header(QNetworkRequest::ContentLengthHeader).toLongLong() / (elapsed / 1000.0) / 1024.0; // 单位：KB/s
        qDebug() << "Average download speed:" << downloadSpeed << "KB/s";
    });
    QThread::sleep(1);
}
