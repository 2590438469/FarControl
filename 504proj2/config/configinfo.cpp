#include "configinfo.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QDomDocument>

QString ConfigInfo::datFilePath;
QString ConfigInfo::grillePath;
QString ConfigInfo::display_frame;
QString ConfigInfo::centerIp;
int ConfigInfo::centerUdpPort;
QString ConfigInfo::grilleTcpPort;
QString ConfigInfo::displayTcpPort;
QString ConfigInfo::genMulu;
QString ConfigInfo::geShanMulu;
QString ConfigInfo::displayMulu;
QString ConfigInfo::customData;
QString ConfigInfo::waitTime;

QString ConfigInfo::datFilePathString = "datFilePath";
QString ConfigInfo::grillePathString = "grillePath";
QString ConfigInfo::display_frameString = "dispalyPath";
QString ConfigInfo::centerIpString = "centerip";
QString ConfigInfo::centerUdpPortString = "centerudpport";
QString ConfigInfo::grilleTcpPortString = "grilleTcpPort";
QString ConfigInfo::displayTcpPortString = "displayTcpPort";
QString ConfigInfo::genMuluString = "genMuLu";
QString ConfigInfo::geShanMuluString = "geShanMulu";
QString ConfigInfo::displayMuluString = "displayMulu";
QString ConfigInfo::customDataString = "customData";
QString ConfigInfo::waitTimeString = "waitTime";

QString ConfigInfo::fileName = "config.xml";

ConfigInfo::ConfigInfo(QObject *parent) : QObject(parent)
{

}

void ConfigInfo::initialAllConfig()
{
    centerIp = getValue(ConfigInfo::centerIpString);
    centerUdpPort = getValue(ConfigInfo::centerUdpPortString).toInt();
    grilleTcpPort = getValue(grilleTcpPortString);
    displayTcpPort = getValue(displayTcpPortString);
    display_frame = getValue(display_frameString);
    grillePath = getValue(grillePathString);
    genMulu = getValue(genMuluString);
    geShanMulu = getValue(geShanMuluString);
    displayMulu = getValue(displayMuluString);
    customData = getValue(customDataString);
    waitTime = getValue(waitTimeString);
    qDebug() << "打印配置信息" << centerIp<<centerUdpPort<<grilleTcpPort<<displayTcpPort<< grillePath << waitTime;
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
            if(tag==ConfigInfo::geShanMuluString){
                geShanMulu = text;
            }
            if(tag==ConfigInfo::genMuluString){
                genMulu = text;
            }
            if(tag==ConfigInfo::displayMuluString){
                displayMulu = text;
            }
            if(tag==ConfigInfo::customDataString){
                customData = text;
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
