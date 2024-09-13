#ifndef GEMANAGE_H
#define GEMANAGE_H

#include <QWidget>

namespace Ui {
class GeManage;
}

class GeManage : public QWidget
{
    Q_OBJECT

public:
    explicit GeManage(QWidget *parent = nullptr);
    ~GeManage();

private:
    Ui::GeManage *ui;
};

#endif // GEMANAGE_H
