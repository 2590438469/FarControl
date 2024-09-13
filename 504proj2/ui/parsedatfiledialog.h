#ifndef PARSEDATFILEDIALOG_H
#define PARSEDATFILEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QThread>
#include <QMessageBox>

#include <cstdio>
#include <cmath>

#include "configmodel.h"
#include "frameparserwithmodules.h"
#include "interfaces.h"
#include "network/view_package_helper.h"

const float EPS_F = 1e-8;

namespace Ui {
class ParseDatFileDialog;
}

class ParseDatFileThread : public QThread
{
    Q_OBJECT
public:
    ParseDatFileThread();
    void setDatFilePath(const QString &dat_file_path);
    void setSkipBytes(size_t skip_bytes);
    void setResultFilePath(const QString &result_file_path);
    void setConfigModel(ConfigModel *config_model);
    void setModuleFactory(QList<ModuleInterface *> *modules);
    void stop();
signals:
    void allResultReady(qint64 file_size);
    void filePositionMove(int percent);
protected:
    void run() Q_DECL_OVERRIDE;
    void do_stop();

    char buffer[65536];
    Result8Bytes result[65536];
    char time_stamp_buffer[500];
    char number_buffer[500];
    char decimal_buffer[500];
    char end_of_line_buffer[10];

    qint64 file_pos, file_size;
    size_t m_skip_bytes;
    FILE *dat_file;
    QVector<FILE *> result_files;
    bool is_running;
    QString m_dat_file_path, m_result_file_path;
    ConfigModel *m_config_model;
    FrameParserWithModules *frame_parser;
    QList<ModuleInterface *> *m_modules;
};

class ParseDatFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParseDatFileDialog(QWidget *parent = nullptr);
    void initDialog(QVector<ConfigModel *> *config_models,
                                QList<ModuleInterface *> *modules_factory);
    ~ParseDatFileDialog();
    void stopParsingFile();
    void startParsingFile();

private slots:
    void on_pushButtonBrowserDatFilePath_clicked();

    void on_pushButtonBrowserResultFilePath_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonStart_clicked();

    void onFilePositionMove(int persent);
    void onParseFinsihed(qint64 file_size);
private:
    Ui::ParseDatFileDialog *ui;
    QVector<ConfigModel *> *m_config_models;
    QList<ModuleInterface *> *m_modules_factory;
    ParseDatFileThread *parse_file_thread;

    int m_is_started;
    QTime start_time;
};

#endif // PARSEDATFILEDIALOG_H
