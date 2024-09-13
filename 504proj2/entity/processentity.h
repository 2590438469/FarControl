#ifndef PROCESSENTITY_H
#define PROCESSENTITY_H

#include <QObject>

class ProcessEntity : public QObject
{
    Q_OBJECT
public:
    explicit ProcessEntity(QObject *parent = nullptr);
    QString name;
    QString code;
    QString fileName;
    quint8 percent;

signals:

public slots:
};

#endif // PROCESSENTITY_H
