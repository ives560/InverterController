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

QList<CodeNode> OperaFile::getFaultCodeList()
{
    QList<CodeNode> codelist;
    QDomNodeList domlist = getNodeList();
    const int count = domlist.count();
    for(int i=0;i<count;i++)
    {
        QDomElement elmt = domlist.at(i).toElement();
        CodeNode node = getFaultCodeText(elmt);
        codelist.append(node);
    }
    return codelist;
}

CodeNode OperaFile::getFaultCodeText(QString node)
{
    QDomElement elmt = FindElement(node);
    CodeNode code = getFaultCodeText(elmt);
    return code;
}

CodeNode OperaFile::getFaultCodeText(QDomElement elmt)
{
    CodeNode code;
    QDomNodeList list = elmt.childNodes();
    const int count = list.count();
    for(int i=0;i<count;i++)
    {
        QDomElement child = list.at(i).toElement();
        QString tagName = child.tagName();
        if(tagName=="name")
            code.name = child.text();
        else if(tagName=="details")
            code.details = child.text();
    }
    return code;
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

QString OperaFile::getAttribute(QString node,QString atb)
{
    QDomElement elem = FindElement(node);
    QString val = elem.attribute(atb);
    return val;
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
