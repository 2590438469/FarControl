#include "ui/udpendpointdialog.h"
#include "ui_udpendpointdialog.h"

UdpEndpointDialog::UdpEndpointDialog(UdpEndpointManager *data_source_manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UdpEndpointDialog)
{
    ui->setupUi(this);
    row_id_map.clear();
    m_data_source_manager = data_source_manager;

    QStringList table_header;
    table_header<<"ID"<<"数据源"<<"地址"<<"端口"<<"组播";

    QTableWidgetItem *table_item;
    ui->tableWidgetDataSources->setColumnCount(table_header.count());

    int cnt = 0;
    foreach (QString header_str, table_header) {
        table_item = new QTableWidgetItem(header_str);
        ui->tableWidgetDataSources->setHorizontalHeaderItem(cnt++, table_item);
    }

    setRowDatas(m_data_source_manager->getDataSourceVector());
    init_interfaces_combobox();
}

UdpEndpointDialog::~UdpEndpointDialog()
{
    delete ui;
}

void UdpEndpointDialog::setRowDatas(QVector<UdpEndpoint> *data_sources)
{
    row_id_map.clear();
    row_num = 0;
    max_id = 0;
    ui->tableWidgetDataSources->clearContents();
    for (int i = 0; i < data_sources->size(); ++i) {
        max_id = std::max(max_id, (*data_sources)[i].getId());
        row_id_map[(*data_sources)[i].getId()] = row_num;
        updateRowData(row_num, (*data_sources)[i]);
        ++row_num;
//        connect(&((*data_sources)[i]), SIGNAL(dataChanged(QDataSource)),
//                this, SLOT(rowDataChanged(QDataSource)));
    }
}

void UdpEndpointDialog::updateRowData(int row, const UdpEndpoint &data_source)
{
    if (ui->tableWidgetDataSources->rowCount() <= row) {
        ui->tableWidgetDataSources->setRowCount(row + 1);
    }
    QTableWidgetItem *table_item = new QTableWidgetItem(tr("%1").arg(data_source.getId()));
    table_item->setFlags(Qt::ItemIsEditable);
    ui->tableWidgetDataSources->setItem(row, 0, table_item);

    table_item = new QTableWidgetItem(data_source.getSourceName());
    ui->tableWidgetDataSources->setItem(row, 1, table_item);

    table_item = new QTableWidgetItem(data_source.getAddress());
    ui->tableWidgetDataSources->setItem(row, 2, table_item);

    table_item = new QTableWidgetItem(tr("%1").arg(data_source.getPort()));
    ui->tableWidgetDataSources->setItem(row, 3, table_item);

    table_item = new QTableWidgetItem("组播");
    table_item->setCheckState(data_source.getIsMulticast() ? Qt::Checked : Qt::Unchecked);
    ui->tableWidgetDataSources->setItem(row, 4, table_item);
}

void UdpEndpointDialog::init_interfaces_combobox()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol) {
            if (!address.isEqual(QHostAddress("127.0.0.1"))) {
                ui->comboBoxRecvInterface->addItem(address.toString());
            }
        }
    }
    ui->comboBoxRecvInterface->addItem("127.0.0.1");
    ui->comboBoxRecvInterface->addItem("0.0.0.0");

    ui->comboBoxRecvInterface->setCurrentText(m_data_source_manager->getSelectedInterface());
}

void UdpEndpointDialog::rowDataChanged(const UdpEndpoint &data_source)
{
    if (row_id_map.count(data_source.getId()) > 0) {
        updateRowData(row_id_map[data_source.getId()], data_source);
    }
}

void UdpEndpointDialog::on_tableWidgetDataSources_cellChanged(int row, int column)
{
    QTableWidgetItem *table_item = ui->tableWidgetDataSources->item(row, 0);
    int id = table_item->text().toInt();
    QVector<UdpEndpoint> *data_sources = m_data_source_manager->getDataSourceVector();
    for (int i = 0; i < data_sources->size(); ++i) {
        if ((*data_sources)[i].getId() == id) {
            if (column == 1) {
                (*data_sources)[i].setSourceName(ui->tableWidgetDataSources->item(row, column)->text());
            } else if (column == 2) {
                (*data_sources)[i].setAddress(ui->tableWidgetDataSources->item(row, column)->text());
            } else if (column == 3) {
                (*data_sources)[i].setPort(ui->tableWidgetDataSources->item(row, column)->text().toInt());
            } else if (column == 4) {
                (*data_sources)[i].setIsMulticast(ui->tableWidgetDataSources->item(row, column)->checkState());
            }
        }
    }
}

void UdpEndpointDialog::on_pushButtonAddDataSource_clicked()
{
    UdpEndpoint data_source;
    data_source.setId(++max_id);
    row_id_map[data_source.getId()] = row_num;
    updateRowData(row_num, data_source);
    m_data_source_manager->addDataSource(data_source);
    ++row_num;
}

void UdpEndpointDialog::on_pushButtonSaveDataSources_clicked()
{
    m_data_source_manager->toCsvFile();
    this->close();
}

void UdpEndpointDialog::on_pushButtonCanceled_clicked()
{
    m_data_source_manager->reloadCsvFile();
    this->close();
}

void UdpEndpointDialog::on_comboBoxRecvInterface_currentTextChanged(const QString &arg1)
{
    m_data_source_manager->setSelectedInterface(arg1);
}
