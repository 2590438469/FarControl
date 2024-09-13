#ifndef FRAMEPARSERWITHMODULES_H
#define FRAMEPARSERWITHMODULES_H

#include <QObject>
#include <QDomDocument>
#include <QList>
#include <QVector>
#include <QtPlugin>

#include "frameparser_interface.h"
#include "module_interface.h"
#include "configmodel.h"

class FrameParserWithModules : public QObject, public FrameParserInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.iniyk.FrameParserInterface")
    Q_INTERFACES(FrameParserInterface)
public:
    explicit FrameParserWithModules(QObject *parent = nullptr);
    ~FrameParserWithModules() override;
    void setConfigModel(ConfigModel *config_model);
    void setModulesFactory(QList<ModuleInterface *> *modules);

    // FrameParserInterface interface
    void setConfigFile(FILE *config_file) override;
    void setParamsFile(FILE *params_file) override;
    void ParseFrame(const char *frame, Result8Bytes *results, int subFrameID, float h, float m, float s, float ms, const char *frame_with_timestamp) override;
    const QString &FParserName() override;
    const QString &PlaneName() override;
    const QString &PlaneNo() override;
    uint PlaneID() override;
    int FrameLength() override;
    int ResultLength() override;
    PreHeadTypeEnum PreheadType() override;
protected:
    ConfigModel *m_config_model;
    QList<ModuleInterface *> *m_modules_factory;
    QList<ModuleInterface *> m_module_instance;
signals:

public slots:


};

#endif // FRAMEPARSERWITHMODULES_H
