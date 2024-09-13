#ifndef REMOTEDATASINGLEWIDGET_H
#define REMOTEDATASINGLEWIDGET_H

#include <QWidget>
#include "fileinfo.h"
#include "sendllfile/senddllfile.h"
#include "QThread"

namespace Ui {
class RemoteDataSingleWidget;
}

class RemoteDataSingleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteDataSingleWidget(QWidget *parent = nullptr);
    ~RemoteDataSingleWidget();
    void setType(QString type);
    void isHideMissionInfo(bool isMission);

    void setFileInfo(FileInfo *info);
    void setValue(quint64 value);

    void setDllInfo(FileInfo *info);
    QString filePath;

    quint64 allSize;

    int isPaused = 0;
    QString directory;
    void setDirectory(QString dir);
    quint8 type;

    int sizeType;
    quint64 filesize;
    quint64 nowsize;
    void setButtonEnabled();

    int downloadType = 0;

    QString parentPath;

private:
    Ui::RemoteDataSingleWidget *ui;
    QThread *t;
     SendDllFile *worker;
public slots:
    void startSendingFile(quint64 nowSize);
    void refreshProgress(quint64 nowSize,quint64 allSize);
    void sendMd5Judge(QByteArray md5byte);
    void getMd5Result(quint8 md5Result);

    void okReceieve();
    void falseReceieve();
    void getAbort();
signals:
    void sendFileSignal(QString,quint64);
    void pause(int);
    void sendFinishSend();
};

#endif // REMOTEDATASINGLEWIDGET_H
