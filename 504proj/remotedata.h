#ifndef REMOTEDATA_H
#define REMOTEDATA_H

#include <QObject>
#include "dataadvance.h"

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
    QString user;
    int id;
    static int insertNewRemoteData(RemoteData *data);
    static QList<RemoteData *> selectAllGeshan();
    static QList<RemoteData *> selectByAdvance(DataAdvance *advance);
    static int deleteByXuhao(QString xuhao);
    static int updateDataByXuhao(QString xuhao,QString type);

signals:

public slots:
};

#endif // REMOTEDATA_H
