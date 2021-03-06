#ifndef PARAINFO_H
#define PARAINFO_H

#include <QString>

/*---------readType--------------*/
#define ALL_READ        0x00
#define ALWARS_READ     0x01
#define FAST_READ       0x02
#define WRITE           0x04
#define DIRTY           0x80

/*---------变量数组最大值-----------*/
#define PARA_ARRAY_MAX  512

/*---------paraName---------------*/
enum paraName
{
    //<!--System info /Version-->
      Seri =0,Versiion =1,CodeCRC =97,DataCRC =99,
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
      RatedPower = 220,RatedVoltage = 221,
    //<!--q-->
      sys_cmd =211,
      kw_set =231,kvar_set=232,pf_set=236,pf_mode=235,contro_mode=230,
      flt_que_num =489,
};

class ParaInfo
{
public:
    ParaInfo();

public:
    unsigned int type;
    unsigned int address;
    short int values;
    short int val_w;
    int scaling;        //计算时除以这个值
    QString unit;

public:
    static void seType(ParaInfo* para,int type);
    static void clearType(ParaInfo* para,int type);
    static bool isType(ParaInfo* para,int type);
};

#endif // PARAINFO_H
