#ifndef PROGRESS_H
#define PROGRESS_H

#include <QWidget>
#include "singleprogress.h"

namespace Ui {
class progress;
}

class progress : public QWidget
{
    Q_OBJECT

public:
    explicit progress(QWidget *parent = nullptr);
    ~progress();
    Ui::progress *ui;
    QList<SingleProgress*> progressList;
    void addItem(QString stationName);

private:

public slots:
    void getPro(QString filename,quint64 allsize,quint64 nowsize,QString node);
    void setFileNameCodeRange(int num,QString code,QString name,quint64 range);
    void setFileValue(int num,quint64 value);
    void getDeleteProgress(int num);

signals:
    void finishFile(QString filename,QString node);

};

#endif // PROGRESS_H
