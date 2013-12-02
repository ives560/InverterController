#ifndef OPERAXMLFILE_H
#define OPERAXMLFILE_H
#include <QDomElement>
#include <QDomDocument>
#include <QFile>

struct CodeNode{
        QString name;
        QString details;
};

class OperaFile
{
public:
    OperaFile(QString path);
    QDomNodeList getNodeList();
    bool saveFile();
    QDomElement FindElement(QString name);
    QString getElementText(QString name);
    QList<CodeNode> getFaultCodeList();
    CodeNode getFaultCodeText(QString node);
    CodeNode getFaultCodeText(QDomElement elmt);
    void setElementText(QString name,QString text);
    QString getAttribute(QString node,QString atb);

private:
    QDomDocument doc;
    QString filePath;
    bool isNull;
};

#endif // OPERAXMLFILE_H
