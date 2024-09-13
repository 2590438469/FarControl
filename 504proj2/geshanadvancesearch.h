#ifndef GESHANADVANCESEARCH_H
#define GESHANADVANCESEARCH_H

#include <QWidget>

namespace Ui {
class GeshanAdvanceSearch;
}

class GeshanAdvanceSearch : public QWidget
{
    Q_OBJECT

public:
    explicit GeshanAdvanceSearch(QWidget *parent = nullptr);
    ~GeshanAdvanceSearch();
    void yesButtonSlot();

private:
    Ui::GeshanAdvanceSearch *ui;
};

#endif // GESHANADVANCESEARCH_H
