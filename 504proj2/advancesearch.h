#ifndef ADVANCESEARCH_H
#define ADVANCESEARCH_H

#include <QWidget>
#include "advancesinglesearch.h"

namespace Ui {
class AdvanceSearch;
}

class AdvanceSearch : public QWidget
{
    Q_OBJECT

public:
    explicit AdvanceSearch(QWidget *parent = nullptr);
    ~AdvanceSearch();
    QList<AdvanceSingleSearch*> allList;

public slots:
    void yesButtonSlot();

private:
    Ui::AdvanceSearch *ui;
};

#endif // ADVANCESEARCH_H
