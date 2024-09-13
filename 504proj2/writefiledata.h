#ifndef WRITEFILEDATA_H
#define WRITEFILEDATA_H

#include <QObject>
#include <QFile>

class WriteFiledata : public QObject
{
    Q_OBJECT
public:
    explicit WriteFiledata(QObject *parent = nullptr);
    void setFile(QString filePath);
    void setFileSize(quint64 size);
    void setNum(int num);
    void setCode(QString code);
    QFile *file;

    quint64 fileSize;
    int number;
    QString filename;
    QString missionCode;

signals:
    void sentValue(int,quint64);
    void finishWrite(int num,QString filename,QString code);

public slots:
    void writeFile(QByteArray fileData ,int num);

};

#endif // WRITEFILEDATA_H
