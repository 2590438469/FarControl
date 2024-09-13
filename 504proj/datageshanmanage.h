#ifndef DATAGESHANMANAGE_H
#define DATAGESHANMANAGE_H

#include <QWidget>
#include <QMap>
#include <QHeaderView>

namespace Ui {
class DataGeshanManage;
}

class DataGeshanManage : public QWidget
{
    Q_OBJECT

public:
    explicit DataGeshanManage(QWidget *parent = nullptr);
    ~DataGeshanManage();
    void set_widget_column_header(QStringList header);
    void set_string_column_number(QList<quint8> number);
    void set_combobox_map(QMap<quint8,QStringList> map);
    void set_database(QString baseName);
    void set_primaryKeyIndex(quint8 index);
    void set_fileIndex(quint8 index);
    void set_codeIndex(quint8 code);
    void set_resizeMode(QHeaderView::ResizeMode mode);
    void set_aotuTimeColumn(int column);
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
    Ui::DataGeshanManage *ui;
    QStringList widget_column_header;
    QList<quint8> string_column_number;
    QMap<quint8,QStringList> combobox_map;
    QString dataBaseName;
    int primaryKeyIndex;
    int timeColumn = -1;
    int openFileIndex = -1;
    quint8 missionCode;
    QString recentTime;
    TableWidgetStatusFlag tableWidget_status = TableWidgetCompleteFlag;
    QHeaderView::ResizeMode resizeMode;
public slots:
    void addButton_slot();
    void deleteButton_slot();
    void finishButton_slot();
    void editButton_slot();
    void searchButton_slot();
    void download_slot();

    void cellDoubleClicked(int row,int column);

    void advanceCheckSlot();

    void getAdvanceResultString(QString resultString);
};

#endif // DATAGESHANMANAGE_H
