#ifndef DIRECTORYSELECT_H
#define DIRECTORYSELECT_H

#include <QWidget>

namespace Ui {
class DirectorySelect;
}

class DirectorySelect : public QWidget
{
    Q_OBJECT

public:
    explicit DirectorySelect(QWidget *parent = nullptr);
    ~DirectorySelect();

private:
    Ui::DirectorySelect *ui;
public slots:
    void selectFilePath();
    void setGrillePath();
    void setDisplayFramePath();
    void setDatPath();
    void setOxPath();
    void setHeadPath();
    void setBackupPath();
};

#endif // DIRECTORYSELECT_H
