#ifndef REMOTEDATA_H
#define REMOTEDATA_H

#include <QObject>

class RemoteData : public QObject
{
    Q_OBJECT
public:
    explicit RemoteData(QObject *parent = nullptr);
    QString code;
    QString model;
    int time;
    QString type;
    QString fileName;
    quint64 fileSize;
    int id;
    QString user;
    static int insertNewRemoteData(RemoteData *data);

signals:

public slots:
};

#endif // REMOTEDATA_H
