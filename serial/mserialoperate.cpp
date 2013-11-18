#include "mserialoperate.h"

MSerialOperate::MSerialOperate()
{
    rxCount=0;
    comState=false;

#ifdef AM335x_BOARD
    port=new SerialPort("/dev/ttyO1");//板子DSP串口ttyO1
#else
    port=new SerialPort("/dev/ttyS2");//电脑串口COM3是ttyS2
#endif

    outTimer=new QTimer(this);
    connect(outTimer,SIGNAL(timeout()),this,SLOT(timeOut()));
}

MSerialOperate::~MSerialOperate()
{
    delete port;
}

bool MSerialOperate::modubsRead(unsigned int addr, int len,uchar *rxBuffer,int *rxCount)
{
    bool isread = false;
    SendReadOrder(addr,len);
    isread = readData(rxBuffer,rxCount);//读取串口数据
    return isread;
}

bool MSerialOperate::modubsWrite(unsigned int addr, int len,unsigned int *val)
{
    bool writed = false;
    uchar rxBuffer[10];
    int rxCount=0;

    SendWriteOrder(addr,val,len);
    writed = readData(rxBuffer,&rxCount);//读取串口数据
    return writed;
}

//串口接收
bool MSerialOperate::readData(uchar *rxBuffer,int *rxCount)
{
    enread=true;
    int count=0xff;
    int caseRx=0;
    *rxCount=0;
    outTimer->start(200);//超时定时器
    while (enread==true)
    {
        if(port->bytesAvailable()>0)
        {
            uchar byte;
            port->ReadPort(&byte,1);//一次只接收一个，一次读取多个会读到后面一帧的数据
            rxBuffer[*rxCount]=byte;
            (*rxCount)++;
            //qDebug()<<"rxBuffer"<<*rxCount<<":"<<byte;
            switch(caseRx)
            {
                case 0://判断主机地址
                    {
                        if(byte==0x01)
                            caseRx=1;
                        else
                            *rxCount=0;
                    }
                    break;
                case 1://功能码
                    {
                        if(byte==0x03)//读寄存器功能码
                            caseRx=2;
                        else if(byte==0x10)//写寄存器功能码
                        {
                            count=8;
                            caseRx=3;
                        }
                        else
                        {
                            caseRx=0;
                            *rxCount=0;
                        }
                    }
                    break;
                case 2://获得读寄存器个数
                    {
                        count=rxBuffer[2];
                        count=count+5;
                        caseRx=3;
                    }
                    break;
                case 3://判断一帧是否读完
                    {
                        if((*rxCount)==count)
                        {
                            outTimer->stop();
                            caseRx=0;
                            enread=false;
                            if(checkOutCRC16(rxBuffer,count)==true)
                            {
                                if(rxBuffer[1]==0x03||rxBuffer[1]==0x10)
                                {
                                    comState=true;
                                    return true;
                                }
                            }
                        }
                    }
                    break;
            }//ensd switch
        }//end if
    }//end while
    qDebug()<<"comReadDataError";
    comState=false;
    return false;
}
//读一个或多个命令
void MSerialOperate::SendReadOrder(unsigned int addr,int len)
{
    sendLen=len;//读取参数的个数
    const int bufLen=8;
    uchar buf[bufLen];
    buf[0]=MAIN_ENGINE_ADDRESS;
    buf[1]=READ_FUNCTION_CODE;  //功能码
    buf[2]=(uchar)(addr>>8);
    buf[3]=(uchar)addr;          //起始地址
    buf[4]=(uchar)(len>>8);
    buf[5]=(uchar)len;           //寄存器数量

    addCRC16(buf,bufLen);
    port->writePort(buf,bufLen);
}
//写一个寄存器命令
void MSerialOperate::SendWriteOrder(unsigned int addr,unsigned int *val,int len)
{
    sendLen=len;
    int bufLen=9+len*2;
    uchar buf[bufLen];
    buf[0]=MAIN_ENGINE_ADDRESS;
    buf[1]=WRITE_FUNCTION_CODE; //功能码
    buf[2]=(uchar)(addr>>8);
    buf[3]=(uchar)addr;          //起始地址
    buf[4]=(uchar)(len>>8);
    buf[5]=(uchar)len;           //寄存器数量

    buf[6]=(uchar)(len*2);       //字节数
    for(int i=0;i<len;i++)
    {
        buf[7+i*2]=(uchar)(val[i]>>8);
        buf[8+i*2]=(uchar)val[i];
    }

    addCRC16(buf,bufLen);
    port->writePort(buf,bufLen);
}
//串口读取数据超时
void MSerialOperate::timeOut()
{
    outTimer->stop();
    enread=false;
    comState=false;
}

bool MSerialOperate::checkOutCRC16(uchar *buffer,int count)
{
    count=count-2;
    unsigned int countcrcs=countCRC16(buffer,count);
    unsigned int rxcrc = (uchar)buffer[count+1];
                 rxcrc = rxcrc<<8;
                 rxcrc = rxcrc + (uchar)buffer[count];

    if(countcrcs==rxcrc)
        return true;
    else
        return false;

}

void MSerialOperate::addCRC16(uchar *buf,int len)
{
    int crcsum=countCRC16(buf,len-2);

    buf[len-2]=(uchar)crcsum;
    buf[len-1]=(uchar)(crcsum>>8);
}

uint MSerialOperate::countCRC16(uchar *data_ad,int length)
{
    uint i,j,crcsum;
    crcsum=0xFFFF;
    for(i=0;i<length;i++)
    {
        crcsum^=data_ad[i];
        for(j=0;j<8;j++)
        {
            if((crcsum&1)==1)
                crcsum=(crcsum>>1) ^ 0xA001;
            else
                crcsum=(crcsum>>1);
        }
    }
    return crcsum;
}

bool MSerialOperate::getComState()
{
    return comState;
}
