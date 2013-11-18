#ifndef MSERIALOPERATE_H
#define MSERIALOPERATE_H
//
//串口应用类
//
#include "common.h"
#include"serial/serialport.h"

class MSerialOperate:public QObject
{
    Q_OBJECT
public:
    MSerialOperate();
    ~MSerialOperate();
    bool modubsRead(unsigned int addr, int len,uchar *rxBuffer, int *rxCount);
    bool modubsWrite(unsigned int addr, int len,unsigned int *val);
    bool readData(uchar *rxBuffer, int *rxCount);
    void SendReadOrder(unsigned int addr, int len);
    void SendWriteOrder(unsigned int addr, unsigned int *val, int len);
    bool getComState();

private:
    bool checkOutCRC16(uchar *buffer,int count);
    void addCRC16(uchar *buf, int len);
    uint countCRC16(uchar *data_ad,int length);

public:
        bool comState;       //串口通讯状态

private:
    SerialPort* port;
    //QByteArray rxBuffer;
    //QByteArray txBuffer;
    QTimer *outTimer;
    char rxCount;
    bool enread;
    int sendLen;

public slots:
    void timeOut();
};

#endif // MSERIALOPERATE_H
