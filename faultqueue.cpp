#include "faultqueue.h"

FaultQueue::FaultQueue()
{
    file = new OperaFile(":/Resources/fault.xml");

}

bool FaultQueue::addItem(int code,int YER,int MON,int DAY,int HUR,int MIN,int SEC)
{
    QDateTime dt(QDate(YER,MON,DAY),QTime(HUR,MIN,SEC));
    addItem(code,dt);
    return true;
}

bool FaultQueue::addItem(int code,QDateTime dt)
{
    FaultItem item;
    item.code = code;
    item.date = dt;
    QString node = QString("code_%1").arg(code);
    item.node = file->getFaultCodeText(node);

    if(this->count()>MAX_QUEUE_NUM)
        this->dequeue();
    this->enqueue(item);

    return true;
}

FaultItem FaultQueue::getCurtItem()
{
    if(this->empty()==false)
        return this->last();
    else
        return FaultItem();
}

