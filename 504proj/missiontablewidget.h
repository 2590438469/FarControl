#ifndef MISSIONTABLEWIDGET_H
#define MISSIONTABLEWIDGET_H

#include <QWidget>
#include <QMap>

namespace Ui {
class MissionTableWidget;
}

class MissionTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MissionTableWidget(QWidget *parent = nullptr);
    ~MissionTableWidget();
    void set_widget_column_header(QStringList header);
    void set_string_column_number(QList<quint8> number);
    void set_combobox_map(QMap<quint8,QStringList> map);
    void set_database(QString baseName);
    void set_primaryKeyIndex(quint8 index);
    void initial_table_item();

    void editFinish();
    void addFinish();
    quint8 initial_widget();


    int currentRow;
    QList<QString> oldValue;

    enum TableWidgetStatusFlag {
        TableWidgetEditFlag = 2,
        TableWidgetAddFlag = 1,
        TableWidgetCompleteFlag = 0
    };

private:
    Ui::MissionTableWidget *ui;
    QStringList widget_column_header;
    QList<quint8> string_column_number;
    QMap<quint8,QStringList> combobox_map;
    QString dataBaseName;
    int primaryKeyIndex;
    TableWidgetStatusFlag tableWidget_status = TableWidgetCompleteFlag;
public slots:
    void addButton_slot();
    void deleteButton_slot();
    void finishButton_slot();
    void editButton_slot();
    void searchButton_slot();
};


#endif // MISSIONTABLEWIDGET_H
