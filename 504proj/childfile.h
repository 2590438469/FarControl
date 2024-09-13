#ifndef CHILDFILE_H
#define CHILDFILE_H

#include <QObject>

class ChildFile : public QObject
{
    Q_OBJECT
public:
    explicit ChildFile(QObject *parent = nullptr);
    int id;
    int fileid;
    QString fileName;
    quint64 fileSize;
    int updatetime;
    QString parentString;
    QString user;
    static QList<ChildFile*> selectByFileid(int fileid);
    static int deleteByFildid(int fileid);
    static int insertNewInfo(ChildFile *childFile);
    static int deleteChildFileByFileidAndName(QString name,int fileid);

signals:

public slots:
};

#endif // CHILDFILE_H
