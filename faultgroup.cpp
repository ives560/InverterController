#include "faultgroup.h"

FaultGroup::FaultGroup()
{
}

bool FaultGroup::addItem(int code,int YER,int MON,int DAY,int HUR,int MIN,int SEC)
{
    QDateTime dt(QDate(YER,MON,DAY),QTime(HUR,MIN,SEC));
    addItem(code,dt);
    return true;
}

bool FaultGroup::addItem(int code,QDateTime dt)
{
    FaultItem item;
    item.code = code;
    item.date = dt;

    if(queue.count()>MAX_QUEUE_NUM)
        queue.pop_back();
    this->queue.append(item);

    return true;
}

FaultItem FaultGroup::getCurtItem()
{
    if(queue.empty()==false)
        return queue.first();
    else
        return FaultItem();
}

