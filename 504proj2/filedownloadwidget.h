#ifndef FILEDOWNLOADWIDGET_H
#define FILEDOWNLOADWIDGET_H

#include <QWidget>
#include "singlefilewidget.h"
#include "agreement/agreement.h"
#include "fileinfo.h"
#include "entity/childfile.h"
#include "entity/childfilewithparent.h"

namespace Ui {
class FileDownLoadWidget;
}

class FileDownLoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileDownLoadWidget(QWidget *parent = nullptr);
    explicit FileDownLoadWidget(QString title,QWidget *parent = nullptr);
    ~FileDownLoadWidget();

    void initialFileInfo(QList<FileInfo*> list);
    QList<SingleFileWidget*> allWidgetList;
    AgreeMent::FILE_TYPES fileType;
    void settype(AgreeMent::FILE_TYPES type);
    void setstring(QString text);

public slots:
    void uploadGeshan();
    void refreshWidget(ChildFileWithParent* withParent);
signals:

    void sendFileInfo(FileInfo*);

private:
    Ui::FileDownLoadWidget *ui;
};

#endif // FILEDOWNLOADWIDGET_H
