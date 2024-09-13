#ifndef BASEBANDMANAGE_H
#define BASEBANDMANAGE_H

#include <QWidget>

namespace Ui {
class BaseBandManage;
}

class BaseBandManage : public QWidget
{
    Q_OBJECT

public:
    explicit BaseBandManage(QWidget *parent = nullptr);
    ~BaseBandManage();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void sendBaseBandResult(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);

private:
    Ui::BaseBandManage *ui;
signals:
    void disconnectBaseBandManage();
};

#endif // BASEBANDMANAGE_H
