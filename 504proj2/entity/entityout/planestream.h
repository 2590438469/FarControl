#ifndef PLANESTREAM_H
#define PLANESTREAM_H

#include <QObject>

class PlaneStream : public QObject
{
    Q_OBJECT
public:
    explicit PlaneStream(QObject *parent = nullptr);
    char streamName[20]; //流名：飞机名_飞机号
    short streamType; //流类型，0－PCM，1－外部工程格式
    char setupName[32]; //格式名称，如果streamType为0，该值为"PCM"，否则为外部
                        //工程格式名称，如："光测数据"、"某站雷达遥测"
    short videoFlag;  //视频标志
    short GPSFlag;   //GPS标志

signals:

public slots:
};

#endif // PLANESTREAM_H
