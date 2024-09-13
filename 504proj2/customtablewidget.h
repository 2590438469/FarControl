#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QWidget>
#include <QMap>
#include <QHeaderView>
#include <receievedata.h>

namespace Ui {
class customTableWidget;
}

class customTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit customTableWidget(QWidget *parent = nullptr);
    ~customTableWidget();
    Ui::customTableWidget *ui;

    struct UserInfo
    {
        QString oldusername;
        QString username;
        QString realname;
        QString telenumber;
        QString role;
        QString status;
        quint8 frame;
        quint8 dataNum;
    };

    void set_widget_column_header(QStringList header);
    void set_string_column_number(QList<quint8> number);
    void set_combobox_map(QMap<quint8,QStringList> map);
    void set_database(QString baseName);
    void set_primaryKeyIndex(quint8 index);
    void set_fileIndex(quint8 index);
    void set_codeIndex(quint8 code);
    void set_resizeMode(QHeaderView::ResizeMode mode);
    void set_aotuTimeColumn(int column);
    void initial_table_item(quint8 opResult, QVector<QVector<QString> > array);

    void editFinish(quint8 opResult);
    void addFinish(quint8 opResult);
    void deleteFinish(quint8 opResult);
    quint8 initial_widget(quint8 opResult, QVector<QVector<QString> > array);

    void initial_table_item();
    quint8 initial_widget();
    void set_isShow(bool isShow);
    void set_isJidai(bool isJidai);

    bool isJidai = false;

    int currentRow;
    QList<QString> oldValue;

    enum TableWidgetStatusFlag {
        TableWidgetDeleteFlag = 3,
        TableWidgetEditFlag = 2,
        TableWidgetAddFlag = 1,
        TableWidgetCompleteFlag = 0
    };

    QByteArray getInvert(QByteArray array);
    void sendInitialQuest(quint8 logo);

private:
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



    QByteArray PackAddInfo(QVector<QString> Array, quint8 column, quint8 logo);
    void sendAddInfo(QVector<QString> Array, quint8 logo);
    QByteArray PackEditInfo(QVector<QString> Array, quint8 column, quint8 logo);
    void sendEditInfo(QVector<QString> Array, quint8 logo);
    QByteArray PackDeleteInfo(QVector<QString> Array, quint8 column, quint8 logo);
    void sendDeleteInfo(QVector<QString> Array, quint8 logo);
    QByteArray PackInitialQuest(quint8 logo);


public slots:
    void addButton_slot();
    void deleteButton_slot();
    void finishButton_slot();
    void editButton_slot();
    void searchButton_slot();
    void backButton_slot();

    void cellDoubleClicked(int row,int column);
};

#endif // CUSTOMTABLEWIDGET_H
