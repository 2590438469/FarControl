#include "network/view_package_helper.h"

ViewPackageHelper::ViewPackageHelper(
        int sourceNo,
        FrameParserInterface *frameParser,
        QObject *parent) : QObject (parent)
{
    if (frameParser) {
        memset(log_buffer, 0, sizeof(log_buffer));
        frame_parser = frameParser;

        source_no = sourceNo;
//        if (frameParser->PreheadType() == PreHeadTypeEnum::_0803 ||
//            frameParser->PreheadType() == PreHeadTypeEnum::_1004) {
//            this->system = system;
//        } else if (frameParser->PreheadType() == PreHeadTypeEnum::_NO_HEAD) {
//            this->system = 0;
//        }
        system = frameParser->PreheadType();

        para_num = frame_parser->ResultLength() / 4;
        send_data_length = frame_parser->ResultLength();
        frame_length = frame_parser->FrameLength();
        plane_name = frame_parser->PlaneName();
        plane_no = frame_parser->PlaneNo();
        plane_id = frame_parser->PlaneID();

        if (this->system == PreHeadTypeEnum::_0803 || this->system == PreHeadTypeEnum::_1004) {
            package_head_size = this->system == PreHeadTypeEnum::_0803 ? sizeof(_send_data_head_0803) : sizeof(_send_data_head_1004);
            //ftimeptr = reinterpret_cast<int *>(buffer + package_head_size - 32);
        } else {
            package_head_size = 0;
        }

        memset(buffer, 0, sizeof(buffer));
        sprintf(time_stamp, "00:00:00");
        last_hour = 0;
        last_minute = 0;
        last_second = 0;
        init_char_map();

        PrepareSendDataHead();

        pfloatresult = reinterpret_cast<float *>(buffer + package_head_size);
        result_ptr = reinterpret_cast<Result8Bytes *>(buffer + package_head_size);
    } else {
        //Error log here
        write2log(
            QString(tr("Not a valid frame parser."))
        );
    }
}

ViewPackageHelper::~ViewPackageHelper()
{
}

void ViewPackageHelper::PrepareSendDataHeadTimeStamp(int h, int m, int s, int ms) {
    if (system == PreHeadTypeEnum::_1004) {
        _send_data_head_1004 *psendpack;
        psendpack=reinterpret_cast<_send_data_head_1004 *>(buffer);
        psendpack->ftime[0] = h;
        psendpack->ftime[1] = m;
        psendpack->ftime[2] = s;
        psendpack->ftime[3] = ms;
        psendpack->ftime[4] = h;
        psendpack->ftime[5] = m;
        psendpack->ftime[6] = s;
        psendpack->ftime[7] = ms;
        psendpack->hour = static_cast<float>(h);
        psendpack->minute = static_cast<float>(m);
        psendpack->second = static_cast<float>(s);
        psendpack->millsecond = static_cast<float>(ms);
    } else if (system == PreHeadTypeEnum::_0803){
        _send_data_head_0803 *psendpack;
        psendpack=reinterpret_cast<_send_data_head_0803 *>(buffer);
        psendpack->ftime[0] = h;
        psendpack->ftime[1] = m;
        psendpack->ftime[2] = s;
        psendpack->ftime[3] = ms;
        psendpack->ftime[4] = h;
        psendpack->ftime[5] = m;
        psendpack->ftime[6] = s;
        psendpack->ftime[7] = ms;
    }
    //else no head.
}

void ViewPackageHelper::init_char_map()
{
    for (int i = 0; i < 255; ++i) {
        char_map[i] = i % 10 + '0';
    }
}

void ViewPackageHelper::PrepareSendDataHead()
{
    if (system == PreHeadTypeEnum::_1004) {
        _send_data_head_1004 *psendpack;
        psendpack=reinterpret_cast<_send_data_head_1004 *>(buffer);
        psendpack->packLen=static_cast<uint>(package_head_size + para_num * 4);;
        psendpack->streamNo=static_cast<ushort>(source_no);
        strncpy(psendpack->chSrcName, SOURCE_NAME, 8);
        psendpack->flightNum=1;
        psendpack->dataType=0;
        psendpack->parNum=static_cast<short>(para_num + 8);
        psendpack->state=0;
        psendpack->sourceNo=16;
        psendpack->sourceType=1;
        psendpack->planeID=plane_id;
        psendpack->workMode=0;
        psendpack->sample=64;
        psendpack->ftime[0] = 0;
        psendpack->ftime[1] = 0;
        psendpack->ftime[2] = 0;
        psendpack->ftime[3] = 0;
        psendpack->ftime[4] = 0;
        psendpack->ftime[5] = 0;
        psendpack->ftime[6] = 0;
        psendpack->ftime[7] = 0;
        psendpack->hour = 0;
        psendpack->minute = 0;
        psendpack->second = 0;
        psendpack->millsecond = 0;
    } else if (system == PreHeadTypeEnum::_0803){
        _send_data_head_0803 *psendpack;
        psendpack=reinterpret_cast<_send_data_head_0803 *>(buffer);
        psendpack->dataType=0;
        psendpack->flightNum=1;
        psendpack->packLen= static_cast<uint>(package_head_size + para_num * 4);
        psendpack->parNum= static_cast<short>(para_num + 8);
        strncpy(psendpack->planeName, plane_name.toStdString().c_str(), 13);
        strncpy(psendpack->planeNo, plane_no.toStdString().c_str(), 7);
        psendpack->streamNo=static_cast<ushort>(source_no);
        psendpack->state=0;
        strncpy(psendpack->source, SOURCE_NAME, 8);
        psendpack->ftime[0] = 0;
        psendpack->ftime[1] = 0;
        psendpack->ftime[2] = 0;
        psendpack->ftime[3] = 0;
        psendpack->ftime[4] = 0;
        psendpack->ftime[5] = 0;
        psendpack->ftime[6] = 0;
        psendpack->ftime[7] = 0;
    }
    //else no head.
}

void ViewPackageHelper::onPackageArrived(const char *pkg, int pkg_len)
{
    if (pkg_len % (frame_length + 8) == 0) {
        for (int start_delta = 0; start_delta < pkg_len; start_delta += frame_length + 8) {
            const uchar *frame_start_uchar_ptr =
                    reinterpret_cast<const uchar *>(pkg + start_delta);
            ProcessTime(h, m, s, ms, frame_start_uchar_ptr);
            int i_h, i_m, i_s, i_ms;
            i_h = static_cast<int>(h);
            i_m = static_cast<int>(m);
            i_s = static_cast<int>(s);
            i_ms = static_cast<int>(ms);

            if (last_hour != i_h || last_minute != i_m || last_second != i_s) {
                last_hour = i_h;
                last_minute = i_m;
                last_second = i_s;

                time_stamp[0] = static_cast<char>(i_h / 10 + '0');
                time_stamp[1] = char_map[i_h];

                time_stamp[3] = static_cast<char>(i_m / 10 + '0');
                time_stamp[4] = char_map[i_m];

                time_stamp[6] = static_cast<char>(i_s / 10 + '0');
                time_stamp[7] = char_map[i_s];

                emit timeStampRaised(tr(time_stamp));
            }



            int subframeid = static_cast<int>(*(pkg + start_delta + 6));
            const char *frame_start_without_timestamp = pkg + start_delta + 8;

            frame_parser->ParseFrame(
                frame_start_without_timestamp,
                result_ptr,
                subframeid,
                h,
                m,
                s,
                ms,
                pkg + start_delta
            );

            PrepareSendDataHeadTimeStamp(
                        i_h,
                        i_m,
                        i_s,
                        i_ms
                        );

            if (frame_parser->PreheadType() == PreHeadTypeEnum::_NO_HEAD) {
                send_data_length = frame_parser->ResultLength();
                if (send_data_length > 0) {
                    emit resultReady(buffer, package_head_size + send_data_length);
                }
            }
        }

    }

    if (frame_parser->PreheadType() != PreHeadTypeEnum::_NO_HEAD) {
        para_num = frame_parser->ResultLength() / 4;
        if (para_num > 0) {
            emit resultReady(buffer, package_head_size + para_num * 4);
        }
    }
}

void ProcessTime(float  &h, float &m, float &s, float &ms, const unsigned char *addr)
{
    unsigned char tempbyte;
    tempbyte=addr[1];
    ms=static_cast<float>((tempbyte>>4)*100+(tempbyte&0x0f)*10);
    tempbyte=addr[0];
    ms+=static_cast<float>((tempbyte>>4)+(tempbyte&0x0f)*0.1);

    tempbyte=addr[2];
    s=static_cast<float>((tempbyte>>4)*10+(tempbyte&0x0f));

    tempbyte=addr[3];
    m=static_cast<float>((tempbyte>>4)*10+(tempbyte&0x0f));

    tempbyte=addr[4];
    h=static_cast<float>(((tempbyte&0x30)>>4)*10+(tempbyte&0x0f));
}
