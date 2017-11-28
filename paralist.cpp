#include "paralist.h"

ParaList::ParaList()
{

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

double ParaList::countVal(int addr)
{
    double val=array[addr]->values;
    val= val/array[addr]->scaling;
    return val;
}
//计算总发电量
double ParaList::countTotalPower(int h,int m,int l)
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

void ParaList::initListAddr()
{
    for(int i=0;i<PARA_ARRAY_MAX;i++)
    {
        if(array[i]!=NULL)
            array[i]->address = i;
    }
}

void ParaList::initList()
{
    //57
    memset(array,0,sizeof(ParaItem*)*PARA_ARRAY_MAX);
    //名称,单位，缩放，变量类型
    //QString n,QString u,int scal,unsigned int t
    //<!--System info /Version-->
    array[PARA::Seri] = new ParaItem(tr("Seri"),"",1,ALL_READ);
    array[PARA::Versiion] = new ParaItem(tr("Versiion"),"",1,ALL_READ);
    array[PARA::op_state] = new ParaItem(tr("op_state"),"",1,ALL_READ);
    array[PARA::digi_out1] = new ParaItem(tr("digi_out1"),"",1,ALL_READ);
    array[PARA::CodeCRC] = new ParaItem(tr("CodeCRC"),"",1,ALL_READ);
    array[PARA::DataCRC] = new ParaItem(tr("DataCRC"),"",1,ALL_READ);
    //<!--AC output/Grid voltage-->
    array[PARA::Va] = new ParaItem(tr("Va"),"V",10,ALL_READ);
    array[PARA::Vb] = new ParaItem(tr("Vb"),"V",10,ALL_READ);
    array[PARA::Vc] = new ParaItem(tr("Vc"),"V",10,ALL_READ);
    //<!--AC output/Grid current-->
    array[PARA::Ia] = new ParaItem(tr("Ia"),"A",10,ALL_READ);
    array[PARA::Ib] = new ParaItem(tr("Ib"),"A",10,ALL_READ);
    array[PARA::Ic] = new ParaItem(tr("Ic"),"A",10,ALL_READ);
    //<!--AC output/Inverter current-->
    array[PARA::Int_Ia] = new ParaItem(tr("Int_Ia"),"A",10,ALL_READ);
    array[PARA::Int_Ib] = new ParaItem(tr("Int_Ib"),"A",10,ALL_READ);
    array[PARA::Int_Ic] = new ParaItem(tr("Int_Ic"),"A",10,ALL_READ);
    //<!--AC output/power-->
    array[PARA::kva] = new ParaItem(tr("kva"),"KVA",100,ALL_READ);
    array[PARA::kw] = new ParaItem(tr("kw"),"KW",100,ALL_READ);
    array[PARA::kvar] = new ParaItem(tr("kvar"),"KVAR",100,ALL_READ);
    array[PARA::pf] = new ParaItem(tr("pf"),"",100,ALL_READ);
    array[PARA::freq] = new ParaItem(tr("freq"),"Hz",100,ALL_READ);
    array[PARA::efficy] = new ParaItem(tr("efficy"),"%",100,ALL_READ);
    //<!--DC Input-->
    array[PARA::Vpv] = new ParaItem(tr("Vpv"),"V",10,ALL_READ);
    array[PARA::Ipv] = new ParaItem(tr("Ipv"),"A",10,ALL_READ);
    array[PARA::kwpv] = new ParaItem(tr("kwpv"),"KW",100,ALL_READ);
    //<!--q-->
    array[PARA::kwh_today] = new ParaItem(tr("kwh_today"),"KWh",1,ALL_READ);
    array[PARA::kwh_nv] = new ParaItem(tr("kwh_nv"),"KWh",1,ALL_READ);
    array[PARA::Mwh_nv] = new ParaItem(tr("Mwh_nv"),"MWh",1,ALL_READ);
    array[PARA::Gwh_nv] = new ParaItem(tr("Gwh_nv"),"GWh",1,ALL_READ);
    //<!--Temperature-->
    array[PARA::HS1] = new ParaItem(tr("HS1"),"C",100,ALL_READ);
    //<!--Fault-->
    array[PARA::flt_read] = new ParaItem(tr("flt_read"),"",1,ALL_READ);
    array[PARA::flt_YER] = new ParaItem(tr("flt_YER"),"",1,ALL_READ);
    array[PARA::flt_MON] = new ParaItem(tr("flt_MON"),"",1,ALL_READ);
    array[PARA::flt_DAY] = new ParaItem(tr("flt_DAY"),"",1,ALL_READ);
    array[PARA::flt_HUR] = new ParaItem(tr("flt_HUR"),"",1,ALL_READ);
    array[PARA::flt_MIN] = new ParaItem(tr("flt_MIN"),"",1,ALL_READ);
    array[PARA::flt_SEC] = new ParaItem(tr("flt_SEC"),"",1,ALL_READ);
    array[PARA::flt_num] = new ParaItem(tr("flt_num"),"",1,FAST_READ);
    // <!--System info /time-->
    array[PARA::set_clock] = new ParaItem(tr("set_clock"),"",1,ALL_READ);
    array[PARA::ss] = new ParaItem(tr("ss"),"",1,ALL_READ);
    array[PARA::mm] = new ParaItem(tr("mm"),"",1,ALL_READ);
    array[PARA::hh] = new ParaItem(tr("hh"),"",1,ALL_READ);
    array[PARA::dd] = new ParaItem(tr("dd"),"",1,ALL_READ);
    array[PARA::MM] = new ParaItem(tr("MM"),"",1,ALL_READ);
    array[PARA::yyl] = new ParaItem(tr("yyl"),"",1,ALL_READ);
    array[PARA::yyh] = new ParaItem(tr("yyh"),"",1,ALL_READ);
    //<!--System info /Version-->
    array[PARA::kva_rated] = new ParaItem(tr("kva_rated"),"KVA",100,ALL_READ);
    array[PARA::vline_rated] = new ParaItem(tr("vline_rated"),"V",1,ALL_READ);
    //<!--q-->
    array[PARA::Initial_cmd] = new ParaItem(tr("Initial_cmd"),"",1,FAST_READ);
    array[PARA::sys_cmd] = new ParaItem(tr("sys_cmd"),"",1,FAST_READ);
    array[PARA::Clear_cmd] = new ParaItem(tr("Clear_cmd"),"",1,FAST_READ);
    array[PARA::kw_set] = new ParaItem(tr("kw_set"),"%",1,FAST_READ);
    array[PARA::kvar_set] = new ParaItem(tr("kvar_set"),"%",1,FAST_READ);
    array[PARA::pf_set] = new ParaItem(tr("pf_set"),"%",1,FAST_READ);
    array[PARA::pf_mode] = new ParaItem(tr("pf_mode"),"",1,FAST_READ);
    array[PARA::contro_mode] = new ParaItem(tr("contro_mode"),"",1,FAST_READ);
    array[PARA::Local_Remote_flag] = new ParaItem(tr("Local_Remote_flag"),"",1,FAST_READ);
    array[PARA::auto_restart_en] = new ParaItem(tr("auto_restart_en"),"",1,FAST_READ);
    array[PARA::flt_que_num] = new ParaItem(tr("flt_que_num"),"",1,FAST_READ);
}

void ParaList::retranslateName()
{

    //<!--System info /Version-->
    array[PARA::Seri]->name = QApplication::translate("ParaList", "Seri", 0, QApplication::UnicodeUTF8);
    array[PARA::Versiion]->name = QApplication::translate("ParaList", "Versiion", 0, QApplication::UnicodeUTF8);
    array[PARA::op_state]->name = QApplication::translate("ParaList", "op_state", 0, QApplication::UnicodeUTF8);
    array[PARA::digi_out1]->name = QApplication::translate("ParaList", "digi_out1", 0, QApplication::UnicodeUTF8);
    array[PARA::CodeCRC]->name = QApplication::translate("ParaList", "CodeCRC", 0, QApplication::UnicodeUTF8);
    array[PARA::DataCRC]->name = QApplication::translate("ParaList", "DataCRC", 0, QApplication::UnicodeUTF8);
    //<!--AC output/Grid voltage-->
    array[PARA::Va]->name = QApplication::translate("ParaList", "Va", 0, QApplication::UnicodeUTF8);
    array[PARA::Vb]->name = QApplication::translate("ParaList", "Vb", 0, QApplication::UnicodeUTF8);
    array[PARA::Vc]->name = QApplication::translate("ParaList", "Vc", 0, QApplication::UnicodeUTF8);
    //<!--AC output/Grid current-->
    array[PARA::Ia]->name = QApplication::translate("ParaList", "Ia", 0, QApplication::UnicodeUTF8);
    array[PARA::Ib]->name = QApplication::translate("ParaList", "Ib", 0, QApplication::UnicodeUTF8);
    array[PARA::Ic]->name = QApplication::translate("ParaList", "Ic", 0, QApplication::UnicodeUTF8);
    //<!--AC output/Inverter current-->
    array[PARA::Int_Ia]->name = QApplication::translate("ParaList", "Int_Ia", 0, QApplication::UnicodeUTF8);
    array[PARA::Int_Ib]->name = QApplication::translate("ParaList", "Int_Ib", 0, QApplication::UnicodeUTF8);
    array[PARA::Int_Ic]->name = QApplication::translate("ParaList", "Int_Ic", 0, QApplication::UnicodeUTF8);
    //<!--AC output/power-->
    array[PARA::kva]->name = QApplication::translate("ParaList", "kva", 0, QApplication::UnicodeUTF8);
    array[PARA::kw]->name = QApplication::translate("ParaList", "kw", 0, QApplication::UnicodeUTF8);
    array[PARA::kvar]->name = QApplication::translate("ParaList", "kvar", 0, QApplication::UnicodeUTF8);
    array[PARA::pf]->name = QApplication::translate("ParaList", "pf", 0, QApplication::UnicodeUTF8);
    array[PARA::freq]->name = QApplication::translate("ParaList", "freq", 0, QApplication::UnicodeUTF8);
    array[PARA::efficy]->name = QApplication::translate("ParaList", "efficy", 0, QApplication::UnicodeUTF8);
    //<!--DC Input-->
    array[PARA::Vpv]->name = QApplication::translate("ParaList", "Vpv", 0, QApplication::UnicodeUTF8);
    array[PARA::Ipv]->name = QApplication::translate("ParaList", "Ipv", 0, QApplication::UnicodeUTF8);
    array[PARA::kwpv]->name = QApplication::translate("ParaList", "kwpv", 0, QApplication::UnicodeUTF8);
    //<!--q-->
    array[PARA::kwh_today]->name = QApplication::translate("ParaList", "kwh_today", 0, QApplication::UnicodeUTF8);
    array[PARA::kwh_nv]->name = QApplication::translate("ParaList", "kwh_nv", 0, QApplication::UnicodeUTF8);
    array[PARA::Mwh_nv]->name = QApplication::translate("ParaList", "Mwh_nv", 0, QApplication::UnicodeUTF8);
    array[PARA::Gwh_nv]->name = QApplication::translate("ParaList", "Gwh_nv", 0, QApplication::UnicodeUTF8);
    //<!--Temperature-->
    array[PARA::HS1]->name = QApplication::translate("ParaList", "HS1", 0, QApplication::UnicodeUTF8);
    //<!--Fault-->
    array[PARA::flt_read]->name = QApplication::translate("ParaList", "flt_read", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_YER]->name = QApplication::translate("ParaList", "flt_YER", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_MON]->name = QApplication::translate("ParaList", "flt_MON", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_DAY]->name = QApplication::translate("ParaList", "flt_DAY", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_HUR]->name = QApplication::translate("ParaList", "flt_HUR", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_MIN]->name = QApplication::translate("ParaList", "flt_MIN", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_SEC]->name = QApplication::translate("ParaList", "flt_SEC", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_num]->name = QApplication::translate("ParaList", "flt_num", 0, QApplication::UnicodeUTF8);
    // <!--System info /time-->
    array[PARA::set_clock]->name = QApplication::translate("ParaList", "set_clock", 0, QApplication::UnicodeUTF8);
    array[PARA::ss]->name = QApplication::translate("ParaList", "ss", 0, QApplication::UnicodeUTF8);
    array[PARA::mm]->name = QApplication::translate("ParaList", "mm", 0, QApplication::UnicodeUTF8);
    array[PARA::hh]->name = QApplication::translate("ParaList", "hh", 0, QApplication::UnicodeUTF8);
    array[PARA::dd]->name = QApplication::translate("ParaList", "dd", 0, QApplication::UnicodeUTF8);
    array[PARA::MM]->name = QApplication::translate("ParaList", "MM", 0, QApplication::UnicodeUTF8);
    array[PARA::yyl]->name = QApplication::translate("ParaList", "yyl", 0, QApplication::UnicodeUTF8);
    array[PARA::yyh]->name = QApplication::translate("ParaList", "yyh", 0, QApplication::UnicodeUTF8);
    //<!--System info /Version-->
    array[PARA::kva_rated]->name = QApplication::translate("ParaList", "kva_rated", 0, QApplication::UnicodeUTF8);
    array[PARA::vline_rated]->name = QApplication::translate("ParaList", "vline_rated", 0, QApplication::UnicodeUTF8);
    //<!--q-->
    array[PARA::Initial_cmd]->name = QApplication::translate("ParaList", "Initial_cmd", 0, QApplication::UnicodeUTF8);
    array[PARA::sys_cmd]->name = QApplication::translate("ParaList", "sys_cmd", 0, QApplication::UnicodeUTF8);
    array[PARA::Clear_cmd]->name = QApplication::translate("ParaList", "Clear_cmd", 0, QApplication::UnicodeUTF8);
    array[PARA::kw_set]->name = QApplication::translate("ParaList", "kw_set", 0, QApplication::UnicodeUTF8);
    array[PARA::kvar_set]->name = QApplication::translate("ParaList", "kvar_set", 0, QApplication::UnicodeUTF8);
    array[PARA::pf_set]->name = QApplication::translate("ParaList", "pf_set", 0, QApplication::UnicodeUTF8);
    array[PARA::pf_mode]->name = QApplication::translate("ParaList", "pf_mode", 0, QApplication::UnicodeUTF8);
    array[PARA::contro_mode]->name = QApplication::translate("ParaList", "contro_mode", 0, QApplication::UnicodeUTF8);
    array[PARA::Local_Remote_flag]->name = QApplication::translate("ParaList", "Local_Remote_flag", 0, QApplication::UnicodeUTF8);
    array[PARA::auto_restart_en]->name = QApplication::translate("ParaList", "auto_restart_en", 0, QApplication::UnicodeUTF8);
    array[PARA::flt_que_num]->name = QApplication::translate("ParaList", "flt_que_num", 0, QApplication::UnicodeUTF8);


}
