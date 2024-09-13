#ifndef SOFTWARE_INSERT_H
#define SOFTWARE_INSERT_H

#include<QWidget>
#include<QProcess>
#include <QMainWindow>
#include <QLayout>
class Software_insert
{
public:
    Software_insert();
    QWidget* softwareInsert(QLayout *layout, QWidget *widget, const QString &programPath);
    QWidget* softwareInsert2(QLayout *layout, QWidget *widget, const QString &programPath);
    QProcess process;

//private:
//    QWidget *w;
};

#endif // SOFTWARE_INSERT_H
