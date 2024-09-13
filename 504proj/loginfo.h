#ifndef LOGINFO_H
#define LOGINFO_H

#include <QWidget>

namespace Ui {
class LogInfo;
}

class LogInfo : public QWidget
{
    Q_OBJECT

public:
    explicit LogInfo(QWidget *parent = nullptr);
    explicit LogInfo(QString filepath,QWidget *parent = nullptr);
    ~LogInfo();

private:
    Ui::LogInfo *ui;
};

#endif // LOGINFO_H
