#include "configinfo.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDomDocument>

QString ConfigInfo::datFilePath;
QString ConfigInfo::grillePath;
QString ConfigInfo::display_frame;
QString ConfigInfo::grilleTcpPort;
QString ConfigInfo::displayTcpPort;
QString ConfigInfo::datPath;
QString ConfigInfo::oxPath;
QString ConfigInfo::headPath;
QString ConfigInfo::backupPath;

QString ConfigInfo::datFilePathString = "datFilePath";
QString ConfigInfo::grillePathString = "grillePath";
QString ConfigInfo::display_frameString = "dispalyPath";
QString ConfigInfo::grilleTcpPortString = "grilleTcpPort";
QString ConfigInfo::displayTcpPortString = "displayTcpPort";
QString ConfigInfo::datPathString = "datPath";
QString ConfigInfo::oxPathString = "oxPath";
QString ConfigInfo::headPathString = "headPath";
QString ConfigInfo::backupPathString = "backupPath";

QString ConfigInfo::fileName = "config.xml";

ConfigInfo::ConfigInfo(QObject *parent) : QObject(parent)
{

}

void ConfigInfo::initialAllConfig()
{
    qDebug() << "打印配置信息";
    datFilePath = getValue(datFilePathString);
    display_frame = getValue(display_frameString);
    grillePath = getValue(grillePathString);
    grilleTcpPort = getValue(grilleTcpPortString);
    displayTcpPort = getValue(displayTcpPortString);
    datPath = getValue(datPathString);
    oxPath = getValue(oxPathString);
    headPath = getValue(headPathString);
    backupPath = getValue(backupPathString);
}

void ConfigInfo::writeXml(QString tag, QString text)
{
    QFile file(fileName);
    QDomDocument doc;
    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "data打开失败";
        return;
    }
    QString errorStr;  //出错的原因
    int errorLine;  //出错的行
    int errorCol;   //出错的列

    if(!doc.setContent(&file, true, &errorStr, &errorLine, &errorCol))
    {
        qDebug() << errorStr << "line: " << errorLine << "col: " << errorCol;
        qDebug() << "读取错误";
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode firstNode = docElem.firstChild();   //返回根节点的第一个子节点
    while(!firstNode.isNull()) //若是节点不为空， book
    {
        if(firstNode.toElement().tagName() == tag)
        {
            qDebug() << "写入xml值" << tag;
            firstNode.firstChild().setNodeValue(text);
            if(tag==ConfigInfo::datFilePathString){
                datFilePath = text;
            }
            if(tag==ConfigInfo::grillePathString){
                grillePath = text;
            }
            if(tag==ConfigInfo::display_frameString){
                display_frame = text;
            }
            if(tag==ConfigInfo::datPathString){
                datPath = text;
            }
            if(tag==ConfigInfo::oxPathString){
                oxPath = text;
            }
            if(tag==ConfigInfo::headPathString){
                headPath = text;
            }
            if(tag==ConfigInfo::backupPathString){
                backupPath = text;
            }
        }
        firstNode = firstNode.nextSibling();  //下一个兄弟节点
    }
    file.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}
QString ConfigInfo::getValue(const QString &name)
{
    if(fileName.isEmpty()){
        qDebug() << "文件为空";
        return "";
    }
    QFile *file = new QFile(fileName);
    if(!file->open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(NULL, QString("title"), QString("open error!"));
        qDebug() << "文件打开失败";
        return "";
    }
    reader = new QXmlStreamReader(file);
     while(!reader->atEnd() && !reader->hasError()) {
         QXmlStreamReader::TokenType token = reader->readNext();
         if(token == QXmlStreamReader::StartDocument) {
             continue;
         }
          if (reader->isStartElement() && reader->name() == name) {
              QString elementText = reader->readElementText();
              qDebug() << elementText;
              reader->clear();
              delete reader;
              reader = NULL;
              return elementText;
          }
     }
    if (reader->hasError()) {
        qDebug() << "错误信息"<<reader->errorString();
        //QMessageBox::information(NULL, QString("parseXML"), reader->errorString());
    }
    reader->clear();
    delete reader;
    reader = NULL;
    return "";
}
