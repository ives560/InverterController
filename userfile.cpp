#include "userfile.h"

UserFile::UserFile()
{
    createUserFile();
}

//用户文件初始化
void UserFile::createUserFile()
{
    QString fileName = "user.xml";
    QFileInfo finfo(fileName);
    if(finfo.exists() == false)
    {
        QDomDocument doc;
        QDomProcessingInstruction instruction;
        instruction = doc.createProcessingInstruction("xml","version = \"1.0\"encoding = \"UTF-8\"");
        doc.appendChild(instruction);
        QDomElement root = doc.createElement("user");
        doc.appendChild(root);
        QString names[] = {"pwd","fault_num"};
        QString texts[] = {"12345","0"};
        for(int i=0;i<2;i++)
        {
            QDomElement p = doc.createElement(names[i]);
            QDomText t = doc.createTextNode(texts[i]);
            p.appendChild(t);
            root.appendChild(p);
        }
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)==false)
            return;
        QTextStream out(&file);
        doc.save(out,4);//必须为4
        file.close();
    }
}
