#ifndef DATAMANAGE_H
#define DATAMANAGE_H

#include <QWidget>
#include "entity/remotedata.h"
#include "fileinfo.h"
#include "agreement/agreement.h"

namespace Ui {
class DataManage;
}

class DataManage : public QWidget
{
    Q_OBJECT

public:
    explicit DataManage(QWidget *parent = nullptr);
    ~DataManage();

    void initialItem();
    int refreshTimes = 0;
    int tableWidget_status = 0;
    int currentRow;

private:
    Ui::DataManage *ui;

public slots:
    void refresh();
    void doubleclick(int row,int column);
    void deleteItem();

    void refreshAll(QList<RemoteData*> list);

    void downloadItem();

    void sendRefresh();

    void getDeleteResult(int result);
    void getUpdateResult(int result);

    void editButtonSlot();

    void finishButtonSlot();
signals:

    void setFileInfo(FileInfo *info);
};

#endif // DATAMANAGE_H
