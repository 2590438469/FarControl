#ifndef SERVICEMAINWINDOW_H
#define SERVICEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class ServiceMainWindow;
}

class ServiceMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServiceMainWindow(QWidget *parent = nullptr);
    ~ServiceMainWindow();

private:
    Ui::ServiceMainWindow *ui;
};

#endif // SERVICEMAINWINDOW_H
