#ifndef PARALIST_H
#define PARALIST_H

#include <QApplication>
#include <QString>
#include <QList>

/*---------readType--------------*/
#define ALL_READ        0x00
#define ALWARS_READ     0x01
#define FAST_READ       0x02
#define WRITE           0x04
#define DIRTY           0x80

/*---------变量数组最大值-----------*/
#define PARA_ARRAY_MAX  512

namespace PARA{
/*---------paraName---------------*/
enum paraName
{
    //<!--System info /Version-->
      Seri =0,Versiion =1,op_state=5,digi_out1=28,CodeCRC =97,DataCRC =99,
    //<!--AC output/Grid voltage-->
      Va =30,Vb =31,Vc =32,
    //<!--AC output/Grid current-->
      Ia =35,Ib =36,Ic =37,
    //<!--AC output/Inverter current-->
      Int_Ia =40,Int_Ib =41,Int_Ic =42,
    //<!--AC output/power-->
      kva =61,kw =62,kvar =63,pf =64,freq =48,efficy=58,
    //<!--DC Input-->
      Vpv =51,Ipv =53,kwpv =60,
    //<!--q-->
      kwh_today =65,kwh_nv=67,Mwh_nv=68,Gwh_nv =69,
    //<!--Temperature-->
      HS1 =110,
    //<!--Fault-->
      flt_read =190,flt_YER =191,flt_MON =192,flt_DAY =193,flt_HUR =194,flt_MIN =195,flt_SEC =196,
      flt_num =489,
   // <!--System info /time-->
      set_clock =202,ss =203,mm =204,hh =205,dd =206,MM =207,yyl =208,yyh =209,
    //<!--System info /Version-->
      kva_rated = 220,vline_rated = 221,
    //<!--q-->
      Initial_cmd = 201,
      sys_cmd =211,
      Clear_cmd = 218,
      kw_set =231,kvar_set=232,pf_set=236,pf_mode=235,contro_mode=230,Local_Remote_flag = 281,

      auto_restart_en = 488,
      flt_que_num =489,
};

}//end namespace PARA


struct ParaItem{

    ParaItem(QString n,QString u,int scal,unsigned int t)
    {
        type = t;
        scaling = scal;        //计算时除以这个值
        unit = u;
        name = n;
    }

    unsigned int type;
    unsigned int address;
    short int values;
    short int val_w;
    int scaling;        //计算时除以这个值
    QString unit;
    QString name;
};

class ParaList
{
    Q_DECLARE_TR_FUNCTIONS(ParaList)

private:
    ParaItem* array[PARA_ARRAY_MAX];

public:
    ParaList();
    ~ParaList();

public:
    void initList();
    void initListAddr();

public:
    void retranslateName();
    void setType(QList<int> names,int type,bool en);
    void setType(int* names,int len,int type,bool en);
    void setType(int index,int type);
    void clearType(int index,int type);
    void clearAllType(int type);
    bool isType(int index,int type);
    bool insert(int index,ParaItem* para);
    double countVal(int addr);
    double countTotalPower(int h,int m,int l);
    ParaItem* at(int idex);
    ParaItem* operator[] ( int i );


};

#endif // PARALIST_H
