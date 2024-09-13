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
    static QString grilleTcpPortString;
    static QString displayTcpPortString;
    static QString datPathString;
    static QString oxPathString;
    static QString headPathString;
    static QString backupPathString;

    static QString datFilePath;
    static QString grillePath;
    static QString display_frame;
    static QString grilleTcpPort;
    static QString displayTcpPort;
    static QString datPath;
    static QString oxPath;
    static QString headPath;
    static QString backupPath;


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
