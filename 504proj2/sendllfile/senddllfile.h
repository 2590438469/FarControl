#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class  SendDllFile : public QObject
{
    Q_OBJECT
public:
    explicit  SendDllFile(QObject *parent = nullptr);
    void initialSocket();

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
    int ispaused=0;
private:
    QTcpSocket *socket;

signals:
    void sendPro(quint64 nowsize,quint64 allsize);
    void sendFileData(QByteArray array);
    void abortConnect();
    void sendProgress(quint64 nowsize,quint64 allsize);

    void sendMd5Judge(QByteArray);

public slots:
    void sendFile(QString filepath,quint64 progress);
    void getpaused(int pau);
    void deleteSlot();
};

#endif // SENDFILE_H
