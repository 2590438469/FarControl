#include "outtcpworker.h"
#include <QTcpSocket>

OutTcpWorker::OutTcpWorker(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();

}
