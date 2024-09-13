#ifndef BASEBAND_H
#define BASEBAND_H

#include <QObject>

class BaseBand : public QObject
{
    Q_OBJECT
public:
    explicit BaseBand(QObject *parent = nullptr);
    QString stationName;
    int port;
    int id;
    static int insertNew(BaseBand *baseBand);
    static int deleteByBaseband(BaseBand *baseBand);
    static int editBaseband(BaseBand *oldBaseBand,BaseBand *newBaseBand);
    static QList<BaseBand *> selectAllBaseBand();
    int insertInfo();

signals:

public slots:
};

#endif // BASEBAND_H
