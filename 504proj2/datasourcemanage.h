#ifndef DATASOURCEMANAGE_H
#define DATASOURCEMANAGE_H

#include <QWidget>

namespace Ui {
class DataSourceManage;
}

class DataSourceManage : public QWidget
{
    Q_OBJECT

public:
    explicit DataSourceManage(QWidget *parent = nullptr);
    ~DataSourceManage();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void sendDataSourceResult(quint8 opResult, quint8 frame, QVector<QVector<QString> > array);

private:
    Ui::DataSourceManage *ui;

signals:
    void disconnectDataSourceManage();
};

#endif // DATASOURCEMANAGE_H
