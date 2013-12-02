#ifndef MCONTROLLER_H
#define MCONTROLLER_H

#include <QThread>
#include <QTimerEvent>
#include "common.h"
#include "DataBase.h"
#include "serial/mserialoperate.h"
#include "faultqueue.h"

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

    bool getFaultData(uchar num);
    void readAllFaultData();

    //void setWriteData();
public:
    void runUserWriteData();
    void runGetAlwaysData();
    void runGetFastData();
    bool readAllParaData();
    void readFaultData();
    void setRunLevel(int index,bool state);

public:
    void userWriteData(int name, short int val);
    void userWriteData(ListParaItem list);

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

public:
    uchar fault_num;     //本地错误号
    FaultQueue* fault_queue;

public:
    QMutex mutex;
    QMutex mutexCom;
    QMutex mutexTimer;
    QList< ParaItem*> uslist_w;     //要写入串口的队列
    QQueue<ParaItem*> usQue_r;     //要读出串口的队列
    ParaList paralist;
    DataBase* database;

signals:
    void readAlwaysDataDone();
    void readFastDataDone();
    void writeDataDone(ListParaItem,bool);
    void haveReadNewFault(int);

public slots:
    void alwaysReaderTimeOut();
    void fastReaderTimeOut();
};

#endif // MCONTROLLER_H
