#ifndef MISSIONAGREEMENT_H
#define MISSIONAGREEMENT_H

#include <QObject>
#include "entity/header.h"
#include "entity/entityout/logininfo.h"

class MissionAgreement : public QObject
{
    Q_OBJECT
public:
    explicit MissionAgreement(QObject *parent = nullptr);
    static QByteArray packHead(Header *header);
    static QByteArray sendLogin(LoginInfo *info);
    static QByteArray getStreamList();
    static QByteArray sendConfig();

signals:

public slots:
};

#endif // MISSIONAGREEMENT_H
