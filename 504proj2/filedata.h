#ifndef FILEDATA_H
#define FILEDATA_H

#include <QWidget>

namespace Ui {
class filedata;
}

class filedata : public QWidget
{
    Q_OBJECT

public:
    explicit filedata(QWidget *parent = nullptr);
    ~filedata();

private:
    Ui::filedata *ui;

private slots:
    void GetData(int,int);
};

#endif // FILEDATA_H
