#ifndef GEMANAGE_H
#define GEMANAGE_H

#include <QWidget>
#include <QMap>
#include <QHeaderView>
#include <receievedata.h>
#include <filedownloadwidget.h>
#include "entity/childfilewithparent.h"


namespace Ui {
class GeManage;
}

extern QList<QString> folderFileList;
class GeManage : public QWidget
{
    Q_OBJECT

public:
    explicit GeManage(QWidget *parent = nullptr);
    ~GeManage();
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

    void editFinish(quint8 opResult);
    void addFinish(quint8 opResult);
    void deleteFinish(quint8 opResult);
    quint8 initial_widget(quint8 opResult, QVector<QVector<QString> > array);

    quint8 initial_widget();
    void set_isShow(bool isShow);

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

    void addFinish();
    void editFinish();
    FileDownLoadWidget *fileDownLoadWidget = new FileDownLoadWidget();

    void sendFolderFile();

    void getUpdateResult(int result);
    int refreshTimes = 0;


private:
    Ui::GeManage *ui;
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

    void uploadButtonSlot();
    void downloadButtonSlot();

    void cellDoubleClicked(int row,int column);

    void initial_table_item(QList<GeShan*> list);

    void finishAddGeshan();
    void wrongAddGeshan();

    void refreshChildFile(ChildFileWithParent* withParent);
signals:

    void sendFileInfo(FileInfo*);
};

#endif // GEMANAGE_H
