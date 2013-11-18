#ifndef MCONTROLLER_H
#define MCONTROLLER_H

#include <QThread>
#include <QTimerEvent>
#include "common.h"
#include "DataBase.h"
#include "serial/mserialoperate.h"

struct DataInfo {
    DataInfo(int a,int l)
    {
        addr=a;
        len=l;
    }
    int addr;
    int len;
};

class MController : public QThread
{
    Q_OBJECT
public:
    explicit MController(QObject *parent = 0);  
    ~MController();
    //QList<ParaInfo*> getCommParaList(bool c,bool w);

    void setParaType(QList<int> names,int type);
    void clearAllParaType(int type);

private:
    void run();
    void timerInit();
    bool paraMapInit();
    void userFileInit();
    void systemTimeInit();
    void setReadData(int* rIndex, int *wIndx, bool isread, uchar *buffer);
    DataInfo countReadData(int *indxR, int *indxW,int type);
    bool runReadData(int *rIndx, int *wIndx, int type);
    void saveRowToDataBase();
    void saveFaultRowToDataBase();
    void timerEvent(QTimerEvent * e);

    //void setWriteData();
public:
    void runUserWriteData();
    void runGetAlwaysData();
    void runGetFastData();
    bool readAllParaData();
    void readFaultData();
    void setRunLevel(int index,bool state);

public:
    void userWriteData(int addr, int val);
    void userWriteData(ParaList list);

private:
    bool setRun;
    bool setFirstRun;
    QTimer alwaysTimer;
    QTimer fastTimer;
    int allRIndx;		//当前读在数组下标
    int allWIndx;		//当前写在数组下标
    int fastRIndx;       //当前读在数组下标
    int fastWIndx;       //当前写在数组下标
    bool runLevel[3];
    MSerialOperate* serial;

private:
    uchar fault_num;     //本地错误号

public:
    QMutex mutex;
    QMutex mutexCom;
    QMutex mutexTimer;
    //QMap<QString,ParaInfo*> paraMap; //根据参数名获得参数结构体
    //QList<ParaInfo*> paraList;		//根据索引获得参数结构体
    QList< ParaInfo*> uslist_w;     //要写入串口的队列
    QQueue<ParaInfo*> usQue_r;     //要读出串口的队列
    ParaInfo* paraArray[PARA_ARRAY_MAX];
    DataBase* database;

signals:
    void readDataDone();
    void readFastDataDone();
    void writeDataDone(ParaList,bool);

public slots:
    void alwaysReaderTimeOut();
    void fastReaderTimeOut();
};

#endif // MCONTROLLER_H
