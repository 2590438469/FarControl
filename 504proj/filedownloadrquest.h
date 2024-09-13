#ifndef FILEDOWNLOADRQUEST_H
#define FILEDOWNLOADRQUEST_H

#include <QObject>

class fileDownloadRquest : public QObject
{
    Q_OBJECT
public:
    explicit fileDownloadRquest(QObject *parent = nullptr);
    quint8 fileType;
    QString fileName;
    QString stationIp;

signals:

public slots:
};

#endif // FILEDOWNLOADRQUEST_H
