#ifndef OUTTCPWORKER_H
#define OUTTCPWORKER_H

#include <QObject>
#include <QTcpSocket>

class OutTcpWorker : public QObject
{
    Q_OBJECT
public:
    explicit OutTcpWorker(QObject *parent = nullptr);
    QTcpSocket *socket;

signals:

public slots:
};

#endif // OUTTCPWORKER_H
