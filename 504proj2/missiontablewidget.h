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
    void initial_table_item(quint8 opResult,QVector<QVector<QString>> array);

    void editFinish(quint8 opResult);
    void addFinish(quint8 opResult);
    void deleteFinish(quint8 opResult);
    quint8 initial_widget(quint8 opResult,QVector<QVector<QString>> array);

    QByteArray getInvert(QByteArray array);

    int currentRow;
    QList<QString> oldValue;

    enum TableWidgetStatusFlag {
        TableWidgetEditFlag = 2,
        TableWidgetAddFlag = 1,
        TableWidgetCompleteFlag = 0,
        TableWidgetDeleteFlag = 3
    };

    QByteArray PackInitialQuest(quint8 logo);
    void sendInitialQuest(quint8 logo);
    QByteArray PackEditInfo(QVector<QString> Array,quint8 column,quint8 logo);
    void sendEditInfo(QVector<QString> Array,quint8 logo);
    QByteArray PackDeleteInfo(QVector<QString> Array,quint8 column,quint8 logo);
    void sendDeleteInfo(QVector<QString> Array,quint8 logo);

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
    void initial_table_item_slot(quint8 opResult,QVector<QVector<QString>> array);
};


#endif // MISSIONTABLEWIDGET_H
