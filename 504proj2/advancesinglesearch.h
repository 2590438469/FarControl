#ifndef ADVANCESINGLESEARCH_H
#define ADVANCESINGLESEARCH_H

#include <QWidget>

namespace Ui {
class AdvanceSingleSearch;
}

class AdvanceSingleSearch : public QWidget
{
    Q_OBJECT

public:
    explicit AdvanceSingleSearch(QWidget *parent = nullptr);
    ~AdvanceSingleSearch();
    quint8 getColumn();
    quint8 getType();
    quint8 getHour();
    quint8 getMinute();

private:
    Ui::AdvanceSingleSearch *ui;
};

#endif // ADVANCESINGLESEARCH_H
