#include "faultqueue.h"

FaultQueue::FaultQueue()
{

}

FaultQueue::~FaultQueue()
{

}

bool FaultQueue::addItem(int code,int YER,int MON,int DAY,int HUR,int MIN,int SEC)
{
    FaultItem item;
    item.code = code;

    QString dt = QString("%1-%2-%3 %4:%5:%6").arg(YER).arg(MON).arg(DAY).arg(HUR).arg(MIN).arg(SEC);
    item.date = dt;

    item.node = list[code];

    if(this->count()>MAX_QUEUE_NUM)
        this->takeLast();
    this->insert(0,item);

    return true;
}

FaultItem FaultQueue::getCurtItem()
{
    if(this->empty()==false)
        return this->last();
    else
        return FaultItem();
}

void FaultQueue::retranslate()
{
    list.retranslate();
}

