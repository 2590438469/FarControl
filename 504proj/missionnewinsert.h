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

private slots:
    void add_button_slot();

signals:
    void refresh_tableWidget();
};

#endif // MISSIONNEWINSERT_H
