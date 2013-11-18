#include "parainfo.h"

ParaInfo::ParaInfo()
{
    type=0;
    address=0;
    values=0;
    val_w=0;
    scaling=0;
    unit="";
}

void ParaInfo::seType(ParaInfo *para, int type)
{
    if(para==NULL)
        return;
    para->type |=type;
}

void ParaInfo::clearType(ParaInfo *para, int type)
{
    if(para==NULL)
        return;
    type = ~type;
    para->type &= type;
}

bool ParaInfo::isType(ParaInfo *para, int type)
{
    if(para==NULL)
        return false;
    int t=type;
    type &= para->type;
    if(t==type)
       return true;
    else
       return false;
}
