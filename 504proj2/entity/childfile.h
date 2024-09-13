#ifndef CHILDFILE_H
#define CHILDFILE_H

#include <QObject>

class ChildFile : public QObject
{
    Q_OBJECT
public:
    explicit ChildFile(QObject *parent = nullptr);
    int id;
    int fileid;
    QString fileName;
    quint64 fileSize;
    int updatetime;

signals:

public slots:
};

#endif // CHILDFILE_H
