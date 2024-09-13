#ifndef FILE_H
#define FILE_H

#include <QObject>

class FileInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileInfo(QObject *parent = nullptr);
    QString fileName;
    quint64 fileSize;

    QString code;
    QString model;
    QString status;

    QString filePath;

    quint8 type;

    QString parentPath;

    QString user;

signals:

public slots:
};
#endif // FILE_H
