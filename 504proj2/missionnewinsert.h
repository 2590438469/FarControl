#ifndef MISSIONNEWINSERT_H
#define MISSIONNEWINSERT_H

#include <QWidget>

namespace Ui {
class MissionNewInsert;
}

class MissionNewInsert : public QWidget
{
    Q_OBJECT

public:
    explicit MissionNewInsert(QWidget *parent = nullptr);
    ~MissionNewInsert();

private:
    Ui::MissionNewInsert *ui;
    void initial_combobox_items();
    void initial_header();
    QStringList widget_column_header;

    void sendAddInfo(QVector<QString> Array,quint8 logo);
    QByteArray getInvert(QByteArray array);

private slots:
    void add_button_slot();
    void text_change(int index);

signals:
    void refresh_tableWidget(quint8 opResult,QVector<QVector<QString>> array);
};

#endif // MISSIONNEWINSERT_H
