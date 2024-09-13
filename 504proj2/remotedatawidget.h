#ifndef REMOTEDATAWIDGET_H
#define REMOTEDATAWIDGET_H

#include <QWidget>
#include "agreement/agreement.h"
#include "fileinfo.h"
#include "remotedatasinglewidget.h"


extern RemoteDataSingleWidget *remoteDataWidget;
extern RemoteDataSingleWidget *fileDownload1;
extern RemoteDataSingleWidget *fileDownload2;
namespace Ui {
class RemoteDataWidget;
}

class RemoteDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteDataWidget(QWidget *parent = nullptr);
    ~RemoteDataWidget();
public slots:
    void setFileInfo(FileInfo *info,AgreeMent::FILE_TYPES type);

private:
    Ui::RemoteDataWidget *ui;
};

#endif // REMOTEDATAWIDGET_H
