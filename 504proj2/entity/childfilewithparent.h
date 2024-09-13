#ifndef CHILDFILEWITHPARENT_H
#define CHILDFILEWITHPARENT_H

#include <QObject>
#include "entity/childfile.h"

class ChildFileWithParent : public QObject
{
    Q_OBJECT
public:
    explicit ChildFileWithParent(QObject *parent = nullptr);
    QList<ChildFile *> childList;
    QString parent;

signals:

public slots:
};

#endif // CHILDFILEWITHPARENT_H
