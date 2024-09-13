#include "ui/parsedatfiledialog.h"
#include "ui_parsedatfiledialog.h"


ParseDatFileDialog::ParseDatFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParseDatFileDialog)
{
    ui->setupUi(this);
    m_is_started = 0;
    parse_file_thread = nullptr;
}

void ParseDatFileDialog::initDialog(QVector<ConfigModel *> *config_models, QList<ModuleInterface *> *modules_factory)
{
    m_config_models = config_models;
    m_modules_factory = modules_factory;

    ui->comboBoxSetups->clear();

    for (int i = 0; i < m_config_models->size(); ++i) {
        ui->comboBoxSetups->addItem((*m_config_models)[i]->getSetupName());
    }

}


ParseDatFileDialog::~ParseDatFileDialog()
{
    delete ui;
}

void ParseDatFileDialog::stopParsingFile()
{
    if (parse_file_thread != nullptr) {
        disconnect(parse_file_thread, SIGNAL(filePositionMove(int)),
                this, SLOT(onFilePositionMove(int)));
        disconnect(parse_file_thread, SIGNAL(allResultReady(qint64)),
                this, SLOT(onParseFinsihed(qint64)));

        parse_file_thread->stop();
        if (!parse_file_thread->wait(2000)) {
            parse_file_thread->exit(0);
        }

        delete parse_file_thread;
        parse_file_thread = nullptr;
    }
}

void ParseDatFileDialog::startParsingFile()
{
    parse_file_thread = new ParseDatFileThread();
    parse_file_thread->setDatFilePath(ui->lineEditDatFilePath->text());
    parse_file_thread->setResultFilePath(ui->lineEditResultFilePath->text());
    parse_file_thread->setSkipBytes(
                static_cast<size_t>(ui->lineEditSkipHeadBytes->text().toInt())
                );
    parse_file_thread->setModuleFactory(m_modules_factory);
    parse_file_thread->setConfigModel((*m_config_models)[ui->comboBoxSetups->currentIndex()]);

    connect(parse_file_thread, SIGNAL(filePositionMove(int)),
            this, SLOT(onFilePositionMove(int)));
    connect(parse_file_thread, SIGNAL(allResultReady(qint64)),
            this, SLOT(onParseFinsihed(qint64)));

    parse_file_thread->start();

}

void ParseDatFileDialog::on_pushButtonBrowserDatFilePath_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this,
            tr("打开数据文件"), "./", tr("Data Files (*.dat);;All Files (*.*)"));
    ui->lineEditDatFilePath->setText(file_path);
    QString output_file_path = file_path.left(file_path.lastIndexOf('.'));
    ui->lineEditResultFilePath->setText(output_file_path);
}

void ParseDatFileDialog::on_pushButtonBrowserResultFilePath_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(
        this,
        tr("保存结果路径"),
        "./"
    );
//    QString file_path = QFileDialog::getSaveFileName(this,
//            tr("保存结果文件"), "./", tr("Text Files (*.txt);;All Files (*.*)"));
    ui->lineEditResultFilePath->setText(file_path);
}

void ParseDatFileDialog::on_pushButtonClose_clicked()
{
    this->close();
}

void ParseDatFileDialog::on_pushButtonStart_clicked()
{
    if (m_is_started) {
        stopParsingFile();
        ui->pushButtonStart->setText(tr("开始"));
        m_is_started = 0;
    } else {
        m_is_started = 1;
        ui->pushButtonStart->setText(tr("停止"));
        start_time.start();
        startParsingFile();
    }
}

void ParseDatFileDialog::onFilePositionMove(int persent)
{
    ui->progressBar->setValue(persent);
}

void ParseDatFileDialog::onParseFinsihed(qint64 file_size)
{
    ui->pushButtonStart->setText(tr("开始"));
    m_is_started = 0;
    ui->progressBar->setValue(100);
    int t_spend_in_ms = start_time.elapsed();
    QMessageBox msgBox;
    msgBox.setText(tr("%1字节处理完毕！用时%2 s").arg(file_size).arg(t_spend_in_ms / 1000));
    msgBox.exec();
}

ParseDatFileThread::ParseDatFileThread()
{
    dat_file = nullptr;
    result_files.clear();
    frame_parser = nullptr;
    file_pos = 0LL;
    file_size = 0LL;
    m_skip_bytes = 0LL;
    strcpy(time_stamp_buffer, "00:00:00.000\t");
    strcpy(decimal_buffer, ".000000\t");
    strcpy(end_of_line_buffer, "\n");
}

void ParseDatFileThread::setDatFilePath(const QString &dat_file_path)
{
    m_dat_file_path = dat_file_path;
    QFile file(m_dat_file_path);
    if (file.open(QIODevice::ReadOnly)) {
        file_size = file.size();
        file_pos = 0LL;
        file.close();
    }
}

void ParseDatFileThread::setSkipBytes(size_t skip_bytes)
{
    m_skip_bytes = skip_bytes;
}

void ParseDatFileThread::setResultFilePath(const QString &result_file_path)
{
    m_result_file_path = result_file_path;
    QDir result_file_path_dir(m_result_file_path);
    result_file_path_dir.mkpath(m_result_file_path);
}

void ParseDatFileThread::setConfigModel(ConfigModel *config_model)
{
    m_config_model = config_model;
}

void ParseDatFileThread::setModuleFactory(QList<ModuleInterface *> *modules)
{
    m_modules = modules;
}

void ParseDatFileThread::stop()
{
    is_running = 0;
}

void ParseDatFileThread::run()
{
    result_files.clear();
    dat_file = fopen(m_dat_file_path.toLocal8Bit().toStdString().c_str(), "rb");

    qDebug() << "Start init frame parser.";

    frame_parser = new FrameParserWithModules();

    qDebug() << "Created frame parser.";
    frame_parser->setModulesFactory(m_modules);

    qDebug() << "inited frame parser Module Factory.";
    frame_parser->setConfigModel(m_config_model);

    qDebug() << "Finish init frame parser.";

    memset(result, 0, sizeof(result));

    foreach (const QString &param_name, m_config_model->paramsInViewOrder) {
        QString param_name_in_file = param_name;
        QString param_file_name = tr("%1/%2.txt").arg(m_result_file_path, param_name_in_file.replace(tr("/"), tr("_")));
        FILE *result_file = fopen(param_file_name.toLocal8Bit().toStdString().c_str(), "w");
        qDebug() << param_name;
        fprintf(result_file, "TimeStamp");
        fprintf(result_file, "\t%s\t%s\n", param_name.toLocal8Bit().toStdString().c_str(), "raw_int");
        fflush(result_file);
        result_files.push_back(result_file);
    }

    qDebug() << "Finish create result files.";


    fread(buffer, sizeof(char), m_skip_bytes, dat_file);
    file_pos = static_cast<qint64>(m_skip_bytes);
    size_t buffer_size = fread(buffer, sizeof(char), static_cast<size_t>(m_config_model->frameInfo.frameLength + 8), dat_file);
    is_running = 1;
    while (buffer_size > 0) {
        if (is_running == 0) {
            do_stop();
            break;
        }
        float h, m, s, ms;
        ProcessTime(h, m, s, ms, reinterpret_cast<unsigned char *>(buffer));
        frame_parser->ParseFrame(
                buffer + 8,
                result,
                buffer[6],
                h, m, s, ms,
                buffer
        );
        int h_i, m_i, s_i, ms_i;
        h_i = static_cast<int>(h);
        m_i = static_cast<int>(m);
        s_i = static_cast<int>(s);
        ms_i = static_cast<int>(ms);
        time_stamp_buffer[0] = static_cast<char>(h_i / 10) + '0';
        time_stamp_buffer[1] = static_cast<char>(h_i % 10) + '0';
        time_stamp_buffer[3] = static_cast<char>(m_i / 10) + '0';
        time_stamp_buffer[4] = static_cast<char>(m_i % 10) + '0';
        time_stamp_buffer[6] = static_cast<char>(s_i / 10) + '0';
        time_stamp_buffer[7] = static_cast<char>(s_i % 10) + '0';

        time_stamp_buffer[9] = static_cast<char>((ms_i / 100) % 10)+ '0';
        time_stamp_buffer[10] = static_cast<char>((ms_i / 10) % 10) + '0';
        time_stamp_buffer[11] = static_cast<char>(ms_i % 10) + '0';

        for (int i = 0; i < m_config_model->paramsInViewOrder.size(); ++i) {
            fputs(time_stamp_buffer, result_files[i]);

            itoa(abs(static_cast<int>(result[i].f)), number_buffer, 10);
            if (result[i].f < -EPS_F) {
                fputc('-', result_files[i]);
            }

            fputs(number_buffer, result_files[i]);
            fputc('.', result_files[i]);

            double temp = fabs(static_cast<double>(result[i].f));
            temp = temp - floor(temp);

            for (int j = 0; j < 6; ++j) {
                decimal_buffer[j] = static_cast<char>(static_cast<int>(temp * 10.0)) + '0';
                temp *= 10.0;
                temp = temp - floor(temp);
            }
            fputs(decimal_buffer, result_files[i]);

            itoa(static_cast<int>(result[i].ul), number_buffer, 10);
            fputs(number_buffer, result_files[i]);

            fputs(end_of_line_buffer, result_files[i]);
        }
        file_pos += buffer_size;

        emit filePositionMove(static_cast<int>(file_pos * 100LL / file_size));
        buffer_size = fread(buffer, sizeof(char), static_cast<size_t>(m_config_model->frameInfo.frameLength + 8), dat_file);
    }
    emit allResultReady(file_size);
    do_stop();
}

void ParseDatFileThread::do_stop()
{
    if (dat_file != nullptr) {
        fclose(dat_file);
        dat_file = nullptr;
    }
    for (int i = 0; i < m_config_model->paramsInViewOrder.size(); ++i) {
        if (result_files[i] != nullptr) {
            fclose(result_files[i]);
        }
    }
    result_files.clear();
    delete frame_parser;
    frame_parser = nullptr;
    file_pos = 0LL;
    file_size = 0LL;
}
