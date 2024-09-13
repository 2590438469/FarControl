#ifndef MISSIONAGREEMENTANALUSIS_H
#define MISSIONAGREEMENTANALUSIS_H

#include <QObject>
#include "entity/entityout/planestream.h"

class MissionAgreementAnalusis : public QObject
{
    Q_OBJECT
public:
    explicit MissionAgreementAnalusis(QObject *parent = nullptr);
    static int analusisLoginResult(QByteArray array);
    static QList<PlaneStream *> analusisPlaneStream(QByteArray array);
    static int analusisConfigResult(QByteArray array);

signals:

public slots:
};

#endif // MISSIONAGREEMENTANALUSIS_H
