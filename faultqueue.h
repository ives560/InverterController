#ifndef FAULTGROUP_H
#define FAULTGROUP_H

#include "common.h"
#include "faulttextlist.h"

#define MAX_QUEUE_NUM   255

struct FaultItem{

    int code;
    QString date;
    FaultTextItem *node;
};

class FaultQueue : public QQueue<FaultItem>
{
private:
    FaultTextList list;

public:
    FaultQueue();
    ~FaultQueue();
    FaultItem getCurtItem();
    bool addItem(int code,int YER,int MON,int DAY,int HUR,int MIN,int SEC);
    //inline QList<FaultTextItem> getCodeNodeList(){return NULL;}
    void retranslate();


};

#endif // FAULTGROUP_H
