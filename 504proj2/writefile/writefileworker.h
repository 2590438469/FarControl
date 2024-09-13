#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <QObject>
#include "agreement/agreement.h"
#include <QFile>
#include "fileinfo.h"

class WriteFileWorker : public QObject
{
    Q_OBJECT
public:
    explicit WriteFileWorker(QObject *parent = nullptr);
    QString fileName;
    QString fileDirectoryPath;
    QFile *file;
    QString parentString;
    AgreeMent::FILE_TYPES type;

    void setFileName(QString fileName);
    void setFileType(AgreeMent::FILE_TYPES fileType);
    void setFileSize(quint64 fileSize);
    quint64 fileSize;
    QByteArray md5;
    quint64 nowsize;

signals:

    void setPorgress(quint64);
    void okReceieve();
    void falseReceieve();
public slots:
    void writeFileData(QByteArray fileData);
    void setFileInfo(FileInfo *info,AgreeMent::FILE_TYPES type);
};

#endif // WRITEFILE_H
