#ifndef INTERFACES_FRAMEPARSER_H
#define INTERFACES_FRAMEPARSER_H

#include "interfaces.h"

class FrameParserInterface
{
public:
    virtual ~FrameParserInterface() = default;

    virtual void setConfigFile(FILE *config_file) = 0;
    virtual void setParamsFile(FILE *params_file) = 0;
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

    virtual const QString &FParserName() = 0;
    virtual const QString &PlaneName() = 0;
    virtual const QString &PlaneNo() = 0;
    virtual uint PlaneID() = 0;
    virtual int FrameLength() = 0;
    virtual int ResultLength() = 0;
    virtual PreHeadTypeEnum PreheadType() = 0;
};

QT_BEGIN_NAMESPACE

#define FrameParserInterface_iid "com.iniyk.FrameParserInterface/2.0"
Q_DECLARE_INTERFACE(FrameParserInterface, FrameParserInterface_iid)

QT_END_NAMESPACE

#endif // INTERFACES_FRAMEPARSER_H
