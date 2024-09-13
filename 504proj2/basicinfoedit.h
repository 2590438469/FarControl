#ifndef BASICINFOEDIT_H
#define BASICINFOEDIT_H

#include <QWidget>
#include <QComboBox>
#include <QList>
#include "basicinfo.h"
#include <QCheckBox>

namespace Ui {
class BasicInfoEdit;
}

class BasicInfoEdit : public QWidget
{
    Q_OBJECT

public:
    explicit BasicInfoEdit(QWidget *parent = nullptr);
    ~BasicInfoEdit();


private:
    Ui::BasicInfoEdit *ui;
    void initialinfo();
    QList<QCheckBox *> checkBoxList;

public slots:
    void judgeCombobox(QString text);
    void insertInfo();
    void deleteMember();

signals:
    finishUpdate(BasicInfo*);
};

#endif // BASICINFOEDIT_H
