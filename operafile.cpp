#include "operafile.h"
#include <QTextStream>
#include <QDebug>
OperaFile::OperaFile(QString path)
{
    filePath=path;
    isNull=false;
    QFile file(filePath);//":/Resources/parameter.xml"
    if(file.open(QIODevice::ReadOnly)==true)
    {

        if(!doc.setContent(&file))//将文件内容读到doc 失败
            isNull=true;

        file.close();

    }

}

//读取xml文件
QDomNodeList OperaFile::getNodeList()
{
    if(isNull==false)
        return doc.documentElement().childNodes();
    else
        return QDomNodeList();
}

QString OperaFile::getElementText(QString name)
{
    QDomElement elmt = FindElement(name);
    return elmt.text();
}

void OperaFile::setElementText(QString name,QString text)
{
    QDomElement elmt = FindElement(name);
    elmt.firstChild().setNodeValue(text);
}

QDomElement OperaFile::FindElement(QString name)
{
    QDomNodeList list;

    if(isNull==false)
    {
        list = doc.elementsByTagName(name);
        if(list.count()==1)
            return list.at(0).toElement();
    }
    return QDomElement();
}

bool OperaFile::saveFile()
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    QTextStream out(&file);
    doc.save(out,4);//4为子元素缩进字符数//必须为4
    file.close();
    return true;
}
/*void operaXmlFile::setXmlElement()
{

}*/
