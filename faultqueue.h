#ifndef FAULTGROUP_H
#define FAULTGROUP_H

#include "common.h"
#include "operafile.h"

#define MAX_QUEUE_NUM   255

struct FaultItem{

    int code;
    QString date;
    CodeNode node;
};

class FaultQueue : public QQueue<FaultItem>
{
private:
    OperaFile* file;

public:
    FaultQueue();
    FaultItem getCurtItem();
    bool addItem(int code,int YER,int MON,int DAY,int HUR,int MIN,int SEC);
    inline QList<CodeNode> getCodeNodeList(){return file->getFaultCodeList();}


};

#endif // FAULTGROUP_H
