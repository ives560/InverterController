#include "userfile.h"
#include <QDebug>

UserFile::UserFile()
{
    createUserFile();
}

UserFile::~UserFile()
{

}

//用户文件初始化
void UserFile::createUserFile()
{
    QFileInfo finfo(USER_FILE_NAME);
    if(finfo.exists() == false)
    {
        QDomDocument doc;
        QDomProcessingInstruction instruction;
        instruction = doc.createProcessingInstruction("xml","version = \"1.0\"encoding = \"UTF-8\"");
        doc.appendChild(instruction);
        QDomElement root = doc.createElement("user");
        doc.appendChild(root);
        QString names[] = {"pwd","fault_num","tcport"};
        QString texts[] = {"12345","0","502"};
        for(int i=0;i<3;i++)
        {
            QDomElement p = doc.createElement(names[i]);
            QDomText t = doc.createTextNode(texts[i]);
            p.appendChild(t);
            root.appendChild(p);
        }
        QFile file(USER_FILE_NAME);
        if(file.open(QIODevice::WriteOnly)==false)
            return;
        QTextStream out(&file);
        doc.save(out,4);//必须为4
        file.close();
    }
}

//读取xml文件
QDomDocument UserFile::getDomDocument()
{
    QFile file(USER_FILE_NAME);
    QDomDocument doc;
    bool isopen=false;
    if(file.open(QIODevice::ReadOnly)==true)
    {
        if(!doc.setContent(&file))//将文件内容读到doc 失败
            qDebug()<<"read file"<<USER_FILE_NAME<<"fale";

        file.close();
    }
    return doc;
}

QDomElement UserFile::FindElement(QString name)
{
    QDomNodeList list;

    list = getDomDocument().elementsByTagName(name);
    if(list.count()==1)
        return list.at(0).toElement();

    return QDomElement();
}

bool UserFile::setElementText(QString name,QString text)
{
    QDomElement elmt = FindElement(name);
    elmt.firstChild().setNodeValue(text);
}
