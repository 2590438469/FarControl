#ifndef BATTLEFORMLINE_H
#define BATTLEFORMLINE_H

#include <QObject>
#include <QTableWidget>

class BattleFormLine : public QObject
{
    Q_OBJECT
public:
    explicit BattleFormLine(QObject *parent = nullptr);

signals:
    void finishExport();

public slots:
    void exportForm(QTableWidget *tableWidget,QString dateDir,QString filename);
};

#endif // BATTLEFORMLINE_H
