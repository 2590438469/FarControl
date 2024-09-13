#ifndef FILELOG_H
#define FILELOG_H

#include <QObject>

class FileLog : public QObject
{
    Q_OBJECT
public:
    explicit FileLog(QObject *parent = nullptr);
    QString people;
    int time;
    quint8 operation;
    QString fileName;
    static int insertNewLog(FileLog *log);

signals:

public slots:
};

#endif // FILELOG_H
