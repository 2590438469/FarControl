#ifndef INTERFACES_MODULE_H
#define INTERFACES_MODULE_H

#include "interfaces.h"

class ModuleInterface{
public:
    virtual ~ModuleInterface() = default;
    virtual ModuleInterface* makeInstance() = 0;
    void setSetupDirPath(const QString &dir_path) {
        m_setup_dir_path = dir_path;
    }
    virtual const QString &getModuleName() = 0;
    virtual void setDomElementConfig(const QDomElement &module_element) = 0;
    virtual void setViewParamsMap(const QVector<QString> &params_in_view_order) = 0;
    virtual void ParseFrame(
            const char *frame,
            Result8Bytes *results,
            int subFrameID,
            float h,
            float m,
            float s,
            float ms,
            const char *frame_with_timestamp
        ) = 0;
    virtual const QString &getModuleInfo() = 0;
protected:
    QString m_setup_dir_path;
};

QT_BEGIN_NAMESPACE

#define ModuleInterface_iid "com.iniyk.ModuleInterface/1.0"
Q_DECLARE_INTERFACE(ModuleInterface, ModuleInterface_iid)

QT_END_NAMESPACE

#endif // INTERFACES_MODULE_H
