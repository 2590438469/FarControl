#ifndef ADVANCESEARCH_H
#define ADVANCESEARCH_H

#include <QWidget>
#include "advancedsinglesearch.h"

namespace Ui {
class AdvanceSearch;
}

class AdvanceSearch : public QWidget
{
    Q_OBJECT

public:
    explicit AdvanceSearch(QWidget *parent = nullptr);
    ~AdvanceSearch();
    QStringList comboList;
    QString tName;
    void setList(QStringList list);
    void setTableName(QString tableName);
    void setStringNumList(QList<quint8> number);
    QList<AdvancedSingleSearch*> singleList;
    QList<quint8> stringNumList;

    void setMap(QMap<quint8, QStringList> mapString);

    QMap<quint8, QStringList> map;
    void setDingList(QList<int> list);
    QList<int> dingList;

public slots:
    void addIndexSlot();
    void okButtonSlot();

private:
    Ui::AdvanceSearch *ui;
signals:
    void sendResultString(QString);
};

#endif // ADVANCESEARCH_H
