#ifndef CUSTOMTABLEFORMLINE_H
#define CUSTOMTABLEFORMLINE_H

#include <QObject>
#include <QTableWidget>

class CustomTableFormLine : public QObject
{
    Q_OBJECT
public:
    explicit CustomTableFormLine(QObject *parent = nullptr);

signals:

public slots:

    void exportForm(QTableWidget *tableWidget,QString dateDir,QString filename);
};

#endif // CUSTOMTABLEFORMLINE_H
