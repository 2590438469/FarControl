#ifndef DELAYTEST_H
#define DELAYTEST_H

#include <QObject>
#include "mutifile.h"

class DelayTest : public QObject
{
    Q_OBJECT
public:
    explicit DelayTest(QObject *parent = nullptr);

signals:
    dalayReturn(MutiFile *muti, int delay);

public slots:
    void delayTest(MutiFile* muti);
};

#endif // DELAYTEST_H
