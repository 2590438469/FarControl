#include "configmodel.h"

ConfigModel::ConfigModel()
{
    setFileDir("");
}

ConfigModel::ConfigModel(const QString &dir_path, QObject *parent) : QObject(parent)
{
    setFileDir(dir_path);
}

ConfigModel::ConfigModel(const ConfigModel &config_model) : QObject(config_model.parent())
{
    setFileDir(config_model.m_dir_path);
}

ConfigModel &ConfigModel::operator=(const ConfigModel &config_model)
{
    setFileDir(config_model.m_dir_path);
    return *this;
}

void ConfigModel::setFileDir(const QString &dir_path)
{
    m_dir_path = dir_path;
    read_main_xml();
}

QString ConfigModel::getFileDir() const
{
    return m_dir_path;
}

QString ConfigModel::getSetupName() const
{
    //return tr("%1_%2").arg(viewParamInfo.planeName, viewParamInfo.planeNo);
    return m_dir_path.split("/").last();
}

void ConfigModel::read_main_xml()
{
    paramsInViewOrder.clear();
    params_map.clear();
    QString main_path = tr("%1/%2").arg(m_dir_path, "main.xml");

    QFile file(main_path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << tr("main.xml not exist : ");
        qDebug() << main_path;
        return ;
    }

    qDebug() << "m_dir_path : " << m_dir_path;

    QDomDocument doc;
    doc.setContent(&file, false);

    QDomElement root = doc.documentElement();
    if (root.tagName() != "main") {
        qDebug() << "Wrong main.xml root element.";
        return ;
    }

    QDomNodeList dom_node_list = root.childNodes();
//    QDomNode node = root.firstChild();
//    while (!node.isNull()) {
    int sz = dom_node_list.size();

    qDebug() << "Root element number : " << sz;
    for (int i = 0; i < sz; ++i) {
        QDomNode node = dom_node_list.at(i);
        QDomElement c_element = node.toElement();
        qDebug() << c_element.tagName();
        if (c_element.tagName() == "name") {
            name = c_element.text().trimmed();
            qDebug() << name;
        } else if (c_element.tagName() == "description") {
            description = c_element.text().trimmed();
        } else if (c_element.tagName() == "frame_info") {
            frameInfo.fromQDomElement(c_element);
        } else if (c_element.tagName() == "view_param_info") {
            viewParamInfo.fromQDomElement(c_element);
        } else if (c_element.tagName() == "param_list") {
            paramListPath = tr("%1/%2").arg(m_dir_path, c_element.attribute("path"));
            qDebug() << paramListPath;
        } else if (c_element.tagName() == "modules") {
            read_modules(c_element);
        }
        //node = node.nextSibling();
    }
    qDebug() << "paraListPath : " << paramListPath;
    io::CSVReader<2> csv_read(paramListPath.toLocal8Bit().toStdString().c_str());
    csv_read.read_header(io::ignore_extra_column, "画面顺序",	"参数名");

    int order;
    std::string param_name_std_str;

    while (csv_read.read_row(order, param_name_std_str)) {
        QString param_name = QString::fromStdString(param_name_std_str);
        params_map[order] = param_name;
    }

    foreach (const QString &param_name, params_map) {
        paramsInViewOrder.append(param_name);
    }
}

void ConfigModel::read_modules(const QDomElement &modules)
{
    QDomNode node = modules.firstChild();
    modulesDomElement.clear();
    while (!node.isNull()) {
        QDomElement c_element = node.toElement();

        if (c_element.tagName() == "module") {
            modulesDomElement.append(c_element);
        }

        node = node.nextSibling();
    }
}

FrameInfo::FrameInfo(QObject *parent) : QObject(parent)
{

}

void FrameInfo::fromQDomElement(const QDomElement &frame_info)
{
//    QDomNode node = frame_info.firstChild();
//    while (!node.isNull()) {
    noSubFrameID = false;
    QDomNodeList dom_node_list = frame_info.childNodes();
    int sz = dom_node_list.size();
    for (int i = 0; i < sz; ++i) {
        QDomNode node = dom_node_list.at(i);
        QDomElement c_element = node.toElement();
        if (c_element.tagName() == "frame_length") {
            frameLength = c_element.text().toInt();
        } else if (c_element.tagName() == "syn_code") {
            synCodeHex = c_element.text().trimmed();
        } else if (c_element.tagName() == "subframe_length") {
            subframeLength = c_element.text().toInt();
        } else if (c_element.tagName() == "subframe_type") {
            subFrameType = c_element.text().trimmed();
        } else if (c_element.tagName() == "has_subframe_id") {
            hasSubFrameID = (c_element.text().trimmed().compare("true", Qt::CaseInsensitive) == 0);
        } else if (c_element.tagName() == "no_subframe_id") {
            noSubFrameID = (c_element.text().trimmed().compare("true", Qt::CaseInsensitive) == 0);
        } else if (c_element.tagName() == "subframe_id_position") {
            subFrameIDPosition = c_element.text().toInt();
        } else if (c_element.tagName() == "subframe_id_base") {
            subFrameIDBase = c_element.text().toInt();
        } else if (c_element.tagName() == "subframe_id_direct") {
            subFrameIDDirect = (c_element.text().trimmed().compare("减计数") == 0 ? -1 : 1);
        }
        //node = node.nextSibling();
    }
}

ViewParamInfo::ViewParamInfo(QObject *parent) : QObject(parent)
{

}

void ViewParamInfo::fromQDomElement(const QDomElement &view_param_info)
{
//    QDomNode node = view_param_info.firstChild();
//    while (!node.isNull()) {
    QDomNodeList dom_node_list = view_param_info.childNodes();
    int sz = dom_node_list.size();
    for (int i = 0; i < sz; ++i) {
        QDomNode node = dom_node_list.at(i);
        QDomElement c_element = node.toElement();
        if (c_element.tagName() == "param_num") {
            paramNum = c_element.text().toInt();
        } else if (c_element.tagName() == "package_head") {
            packageHead = c_element.text().trimmed();
        } else if (c_element.tagName() == "plane_name") {
            planeName = c_element.text().trimmed();
        } else if (c_element.tagName() == "plane_no") {
            planeNo = c_element.text().trimmed();
        } else if (c_element.tagName() == "plane_id") {
            planeID = c_element.text().toInt();
        } else if (c_element.tagName() == "send_param_size") {
            sendParamSize = c_element.text().toInt();
        } else if (c_element.tagName() == "frame_sender_name") {
            frameSenderName = c_element.text().trimmed();
        }
        //node = node.nextSibling();
    }
}
