#ifndef MISSONINPUT_H
#define MISSONINPUT_H

#include <QWidget>

namespace Ui {
class missoninput;
}

class missoninput : public QWidget
{
    Q_OBJECT

public:
    explicit missoninput(QWidget *parent = nullptr);
    ~missoninput();

private:
    Ui::missoninput *ui;
};

#endif // MISSONINPUT_H
