#ifndef COMBOLABEL_H
#define COMBOLABEL_H

#include <QWidget>

namespace Ui {
class ComboLabel;
}

class ComboLabel : public QWidget
{
    Q_OBJECT

public:
    explicit ComboLabel(QWidget *parent = nullptr);
    ~ComboLabel();
    Ui::ComboLabel *ui;
    QStringList nameList;
    QStringList ipList;
    QString getIp();
    QString getName();
    bool isSelect;
    void changeText(QString text);

private:
public slots:
    void changeIp(int index);
};

#endif // COMBOLABEL_H
