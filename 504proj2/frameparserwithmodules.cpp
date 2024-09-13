#include "frameparserwithmodules.h"

FrameParserWithModules::FrameParserWithModules(QObject *parent) : QObject(parent)
{
    m_module_instance.clear();
    m_modules_factory = nullptr;
}

FrameParserWithModules::~FrameParserWithModules()
{
    foreach (ModuleInterface *module_instance, m_module_instance) {
        delete module_instance;
    }
    m_module_instance.clear();
}

void FrameParserWithModules::setConfigModel(ConfigModel *config_model)
{
    m_config_model = config_model;
    foreach (QDomElement module_xml, m_config_model->modulesDomElement) {
        QString module_name = module_xml.attribute("name");
        foreach (ModuleInterface *module_factory, *m_modules_factory) {
            if (module_name.compare(module_factory->getModuleName()) == 0) {
                qDebug() << tr("Make %1 Module instance.").arg(module_factory->getModuleName());
                ModuleInterface *module_instance = module_factory->makeInstance();
                qDebug() << "get setup dir path.";
                module_instance->setSetupDirPath(m_config_model->getFileDir());
                qDebug() << "Set Dom element config.";
                module_instance->setDomElementConfig(module_xml);
                qDebug() << "Set view params map.";
                module_instance->setViewParamsMap(m_config_model->paramsInViewOrder);

                m_module_instance.append(module_instance);
                break;
            }
        }
    }
}

void FrameParserWithModules::setModulesFactory(QList<ModuleInterface *> *modules)
{
    m_modules_factory = modules;
}

void FrameParserWithModules::setConfigFile(FILE *config_file)
{
    Q_UNUSED(config_file);
}

void FrameParserWithModules::setParamsFile(FILE *params_file)
{
    Q_UNUSED(params_file);
}

void FrameParserWithModules::ParseFrame(const char *frame, Result8Bytes *results, int subFrameID, float h, float m, float s, float ms, const char *frame_with_timestamp)
{
    int subframe_id_in_use = subFrameID;
    if (m_config_model->frameInfo.hasSubFrameID) {
        subframe_id_in_use = frame[m_config_model->frameInfo.subFrameIDPosition];
    }
    if (m_config_model->frameInfo.noSubFrameID) {
        subframe_id_in_use = 0;
    }
    foreach (ModuleInterface *module_instance, m_module_instance) {
        module_instance->ParseFrame(frame, results, subframe_id_in_use, h, m, s, ms, frame_with_timestamp);
    }
}

const QString &FrameParserWithModules::FParserName()
{
    return m_config_model->name;
}

const QString &FrameParserWithModules::PlaneName()
{
    return m_config_model->viewParamInfo.planeName;
}

const QString &FrameParserWithModules::PlaneNo()
{
    return m_config_model->viewParamInfo.planeNo;
}

uint FrameParserWithModules::PlaneID()
{
    return static_cast<uint>(m_config_model->viewParamInfo.planeID);
}

int FrameParserWithModules::FrameLength()
{
    return m_config_model->frameInfo.frameLength;
}

int FrameParserWithModules::ResultLength()
{
    return m_config_model->viewParamInfo.sendParamSize;
}

PreHeadTypeEnum FrameParserWithModules::PreheadType()
{
    if (m_config_model->viewParamInfo.packageHead.compare("0803") == 0) {
        return PreHeadTypeEnum::_0803;
    } else if (m_config_model->viewParamInfo.packageHead.compare("1004") == 0) {
        return PreHeadTypeEnum::_1004;
    } else if (m_config_model->viewParamInfo.packageHead.compare("NO_HEAD") == 0) {
        return PreHeadTypeEnum::_NO_HEAD;
    }
    return PreHeadTypeEnum::_NO_HEAD;
}
