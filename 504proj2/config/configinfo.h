#ifndef CONFIGINFO_H
#define CONFIGINFO_H

#include <QObject>
#include <QXmlStreamReader>

class ConfigInfo : public QObject
{
    Q_OBJECT
public:
    explicit ConfigInfo(QObject *parent = nullptr);

    static QString datFilePathString;
    static QString grillePathString;
    static QString display_frameString;
    static QString centerIpString;
    static QString centerUdpPortString;
    static QString grilleTcpPortString;
    static QString displayTcpPortString;
    static QString genMuluString;
    static QString geShanMuluString;
    static QString displayMuluString;
    static QString customDataString;
    static QString waitTimeString;

    static QString datFilePath;
    static QString grillePath;
    static QString display_frame;
    static QString centerIp;
    static int centerUdpPort;
    static QString grilleTcpPort;
    static QString displayTcpPort;
    static QString genMulu;
    static QString geShanMulu;
    static QString displayMulu;
    static QString customData;
    static QString waitTime;


    void initialAllConfig();

    void parseUserInformation();
    static void writeXml(QString tag,QString text);
    QString getValue(const QString &name);
private:
    static QString fileName;
    QXmlStreamReader *reader;
    QXmlStreamWriter *writer;

signals:

public slots:
};

#endif // CONFIGINFO_H
