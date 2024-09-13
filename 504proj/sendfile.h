#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>

class SendDllFile : public QObject
{
    Q_OBJECT
public:
    explicit SendDllFile(QObject *parent = nullptr);

    struct File{
        QString fileName;
        QString node;
        quint32 fileSize;
        quint32 fileBlockLength;
        quint32 beginPosition;
        QByteArray fileBlockData;
        quint8 frame;
    };


    QString nodenow;

    QByteArray getInvert(QByteArray array);


    QByteArray s07(File file);

signals:
    void sendPro(quint64 nowsize,quint64 allsize);

public slots:
    void sendFile(QString filepath,QString node,QString ip1,QString ip2);
};

#endif // SENDFILE_H
