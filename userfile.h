#ifndef USERFILE_H
#define USERFILE_H

#include <QDomDocument>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>

#define USER_FILE_NAME      "user.xml"

class UserFile
{
public:
    UserFile();
    ~UserFile();
    void createUserFile();
    QDomDocument getDomDocument();
    QDomElement FindElement(QString name);
    bool setElementText(QString name,QString text);

};

#endif // USERFILE_H
