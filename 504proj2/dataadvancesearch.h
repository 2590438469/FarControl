#ifndef DATAADVANCESEARCH_H
#define DATAADVANCESEARCH_H

#include <QWidget>

namespace Ui {
class DataAdvanceSearch;
}

class DataAdvanceSearch : public QWidget
{
    Q_OBJECT

public:
    explicit DataAdvanceSearch(QWidget *parent = nullptr);
    ~DataAdvanceSearch();
    void yesButtonSlot();

private slots:
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::DataAdvanceSearch *ui;
};

#endif // DATAADVANCESEARCH_H
