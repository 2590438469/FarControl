#ifndef ADVANCEDSINGLESEARCH_H
#define ADVANCEDSINGLESEARCH_H

#include <QWidget>
#include <QMap>

namespace Ui {
class AdvancedSingleSearch;
}

class AdvancedSingleSearch : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedSingleSearch(QWidget *parent = nullptr);
    ~AdvancedSingleSearch();
    void setList(QStringList list);
    QMap<quint8, QStringList> map;
    QStringList comboList;
    QString getName();
    QString getCondition();
    QString getPrice();
    int getNameNum();
    void setMap(QMap<quint8, QStringList> mapString);
    void setDingList(QList<int> list);
    QList<int> dingList;

public slots:
    void comboChange(int index);

private:
    Ui::AdvancedSingleSearch *ui;
};

#endif // ADVANCEDSINGLESEARCH_H
