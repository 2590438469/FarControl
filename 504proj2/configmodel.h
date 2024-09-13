#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QVector>
#include <QDebug>

#include "include/csv.h"

class FrameInfo : public QObject {
    Q_OBJECT
public:
    explicit FrameInfo(QObject *parent = nullptr);

    int frameLength, subframeLength;
    QString synCodeHex, subFrameType;
    bool hasSubFrameID, noSubFrameID;
    int subFrameIDPosition, subFrameIDBase, subFrameIDDirect;

    void fromQDomElement(const QDomElement &frame_info);
};

class ViewParamInfo : public QObject {
    Q_OBJECT
public:
    explicit ViewParamInfo(QObject *parent = nullptr);

    int paramNum, planeID;
    QString planeName, planeNo, packageHead, frameSenderName;
    int sendParamSize;

    void fromQDomElement(const QDomElement &view_param_info);
};

class ConfigModel : public QObject
{
    Q_OBJECT
public:
    explicit ConfigModel();
    explicit ConfigModel(const QString &dir_path, QObject *parent = nullptr);
    explicit ConfigModel(const ConfigModel &config_model);

    ConfigModel& operator=(const ConfigModel &config_model);

    void setFileDir(const QString &dir_path);
    QString getFileDir() const;

    QString name, paramListPath, description;
    FrameInfo frameInfo;
    ViewParamInfo viewParamInfo;
    QVector<QDomElement> modulesDomElement;

    QVector<QString> paramsInViewOrder;

    QString getSetupName() const;
private:
    QString m_dir_path;
    QMap<int, QString> params_map;

    void read_main_xml();
    void read_modules(const QDomElement &modules);
signals:

public slots:
};

#endif // CONFIGMODEL_H
