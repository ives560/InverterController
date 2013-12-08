#include "paralist.h"

ParaList::ParaList()
{
    memset(array,0,sizeof(ParaItem*)*PARA_ARRAY_MAX);
}

ParaList::~ParaList()
{
    for(int i=0;i<PARA_ARRAY_MAX;i++)
    {
        if(array[i]!=NULL)
            delete array[i];
    }
}

bool ParaList::insert(int index,ParaItem* para)
{
    if(para==NULL)
        return false;

    if(array[index]!=NULL)
        delete(array[index]);
    array[index] = para;
    return true;
}

ParaItem* ParaList::at(int idex)
{
    if(idex>PARA_ARRAY_MAX)
        return NULL;
    else
        return array[idex];
}

ParaItem* ParaList::operator[] ( int i )
{
    return array[i];
}

double ParaList::countTotal(int h,int m,int l)
{
    ParaItem* para_h = array[h];
    ParaItem* para_m = array[m];
    ParaItem* para_l = array[l];

    if(para_h!=NULL&&para_m!=NULL&&para_l!=NULL)
    {
        double val = para_h->values*1000;
        val += para_m->values;
        double dl = para_l->values;
        dl = dl/1000;
        val += dl;

        return val;
    }
    return 0;
}

void ParaList::setType(QList<int> names,int type,bool en)
{
    for(int i=0;i<names.count() ;i++)
    {
        if(en == true)
            setType(names[i],type);
        else
            clearType(names[i],type);
    }
}

void ParaList::setType(int* names,int len,int type,bool en)
{
    for(int i=0;i<len;i++)
    {
        if(en == true)
            setType(names[i],type);
        else
            clearType(names[i],type);
    }
}
void ParaList::setType(int index,int type)
{
    if((index>PARA_ARRAY_MAX)||(array[index]==NULL))
        return;

    array[index]->type |=type;
}

void ParaList::clearAllType(int type)
{
    for(int i=0;i<PARA_ARRAY_MAX;i++)
        clearType(i,type);
}
void ParaList::clearType(int index, int type)
{
    if((index>PARA_ARRAY_MAX)||(array[index]==NULL))
        return;
    type = ~type;
    array[index]->type &= type;
}

bool ParaList::isType(int index, int type)
{
    if((index>PARA_ARRAY_MAX)||(array[index]==NULL))
        return false;

    int t=type;
    type &= array[index]->type;
    if(t==type)
       return true;
    else
       return false;
}
