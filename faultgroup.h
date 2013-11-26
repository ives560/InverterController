#ifndef FAULTGROUP_H
#define FAULTGROUP_H

#include <QString>
#include <QQueue>
#include <QDateTime>
#include <QDate>
#include <QTime>

#define MAX_QUEUE_NUM   255

struct FaultItem{

    int code;
    QDateTime date;
    QString name;
    QString details;
    QString comments;

};

class FaultGroup
{
public:
    FaultGroup();

    bool addItem(int code,int YER,int MON,int DAY,int HUR,int MIN,int SEC);
    bool addItem(int code,QDateTime dt);
    FaultItem getCurtItem();

private:
    QQueue<FaultItem> queue;


};

#endif // FAULTGROUP_H
