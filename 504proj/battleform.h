#ifndef BATTLEFORM_H
#define BATTLEFORM_H

#include <QWidget>
#include <QTableWidget>
#include "battleformline.h"

namespace Ui {
class BattleForm;
}

class BattleForm : public QWidget
{
    Q_OBJECT

public:
    explicit BattleForm(QWidget *parent = nullptr);
    ~BattleForm();
    void exportExcel();

    QString maxing;
    QString malv;
    QString zichang;
    QString zhenchang;
    QString zhenmazu;
    QString zhenmazuchang;
    QString fuzhenfangshi;
    QString fuzhenchang;
    QString idziweizhi;
    QString idzijizhi;
    QString idzijishu;
    QString jiemizhuangtai;
    QString xunhuanfuzhenweizhi;
    QString xunhuanfuzhenmazu;
    QString duofuhaojianyan;
    QString tpc;
    QString kuaitongbuzhenmazu;
    QString AGC;
    QString zhongpindaikuan;
    QString AFC;
    QString AFCmoshi;
    QString jiaowucha;
    QString gongzuodianpin;
    QString xinghao;
    QString miaoshu;
    QString biaoshi;

    QString code;
    QString date;
    QString filename;
    QString startendtime;

    void setTableWidgetItem();
    QThread *t;
    BattleFormLine *worker;

private:
    Ui::BattleForm *ui;
    void initialTablewidget();
signals:
    void sendExport(QTableWidget *tableWidget,QString dateDir,QString filename);

public slots:
    void finishExport();
};

#endif // BATTLEFORM_H
