#ifndef OPERAXMLFILE_H
#define OPERAXMLFILE_H
#include <QDomElement>
#include <QDomDocument>
#include <QFile>

class OperaFile
{
public:
    OperaFile(QString path);
    QDomNodeList getNodeList();
    bool saveFile();
    QDomElement FindElement(QString name);
    QString getElementText(QString name);
    void setElementText(QString name,QString text);
private:
    QDomDocument doc;
    QString filePath;
    bool isNull;
};

#endif // OPERAXMLFILE_H
