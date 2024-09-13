#ifndef DATASOURCESDIALOG_H
#define DATASOURCESDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMap>

#include <algorithm>

#include "network/udpendpointmanager.h"

namespace Ui {
class UdpEndpointDialog;
}

class UdpEndpointDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UdpEndpointDialog(UdpEndpointManager *data_source_manager, QWidget *parent = nullptr);
    ~UdpEndpointDialog();

    void setRowDatas(QVector<UdpEndpoint> *data_sources);
    void updateRowData(int row, const UdpEndpoint &data_source);
private:
    Ui::UdpEndpointDialog *ui;
    UdpEndpointManager *m_data_source_manager;
    QMap<int, int> row_id_map;
    int row_num, max_id;

    void init_interfaces_combobox();
public slots:

private slots:
    void rowDataChanged(const UdpEndpoint &data_source);
    void on_tableWidgetDataSources_cellChanged(int row, int column);
    void on_pushButtonAddDataSource_clicked();
    void on_pushButtonSaveDataSources_clicked();
    void on_pushButtonCanceled_clicked();
    void on_comboBoxRecvInterface_currentTextChanged(const QString &arg1);
};

#endif // DATASOURCESDIALOG_H
