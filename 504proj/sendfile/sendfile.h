#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class  sendfile : public QObject
{
    Q_OBJECT
public:
    enum FILE_TYPE {
        GRILLE = 0,
        DISPLAY_FRAME = 1
    };
    explicit  sendfile(QObject *parent = nullptr);
    void initialSocket();
    QString nodenow;
    QByteArray getInvert(QByteArray array);
    void setPort(QString tcpPort);
    void setAddr(QString tcpAddr);
    FILE_TYPE fileType;


private:
    QTcpSocket *socket;
    QString fileDestIp;
    QHostAddress *addr;
    quint16 *port;

    QString fileName;
    QString filePath;
    quint64 fileSize;
    quint64 currentPoint;


    QString fileDirectory;

signals:
    void sendPro(quint64 nowsize,quint64 allsize);
    void sendFileData(QByteArray array);
    void abortConnect();
    void sendProgress(quint64 nowsize,quint64 allsize);

public slots:
    void sendFile( sendfile::FILE_TYPE type,QString stationIp,QString filename,quint64 progress,QString parentString);
    void sendAbortFile( sendfile::FILE_TYPE type,QString stationIp,QString filename,quint64 progress);
    void sendDianziFile( sendfile::FILE_TYPE type,QString stationIp,QString filename,quint64 progress,QString parentString);
    void deleteSlot();
};

Q_DECLARE_METATYPE(sendfile::FILE_TYPE)

// 在全局作用域中注册类型
static int dummy = qRegisterMetaType< sendfile::FILE_TYPE>();
#endif // SENDFILE_H
