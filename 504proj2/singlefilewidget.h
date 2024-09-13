#ifndef SINGLEFILEWIDGET_H
#define SINGLEFILEWIDGET_H

#include <QWidget>
#include "agreement/agreement.h"
#include "fileinfo.h"

namespace Ui {
class SingleFileWidget;
}

class SingleFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleFileWidget(QWidget *parent = nullptr);
    ~SingleFileWidget();

    void setFileName(QString fileName);
    void setFileType(AgreeMent::FILE_TYPES fileType);
    void setFileSize(quint64 fileSize);
    void setParent(QString parentString);
    AgreeMent::FILE_TYPES type;
    quint64 size;
    QString parentString;

    void deleteFileButtonSlot();
signals:
    void setFileInfo(FileInfo *info,AgreeMent::FILE_TYPES type);

private:
    Ui::SingleFileWidget *ui;
};

#endif // SINGLEFILEWIDGET_H
