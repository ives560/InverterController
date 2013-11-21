#include "mcontroller.h"
#include "operafile.h"
#include <QFileInfo>
#include <QProcess>
MController::MController(QObject *parent)
    : QThread(parent)
{
    setRun=true;
    setFirstRun=true;
    allRIndx=0;
    allWIndx=0;
    fastRIndx=0;
    fastWIndx=0;

    memset(runLevel,false,sizeof(bool)*3);
    runLevel[2]=true;

    database = NULL;
    database = new DataBase();//数据库
    serial=new MSerialOperate();//新建串口

    memset(paraArray,0,sizeof(ParaInfo*)*PARA_ARRAY_MAX);
    paraMapInit();//参数初始化

    userFileInit();
    OperaFile file("user.xml");
    fault_num= file.getElementText("fault_num").toInt();

    timerInit();//设置定时器
    start();//启动线程
}

MController::~MController()
{
    setRun=false;
    setFirstRun =false;
    wait();
    delete serial;
    //保存需要的数据
    OperaFile file("user.xml");
    file.setElementText("fault_num",QString("").arg(fault_num));
    file.saveFile();
}

//线程运行
void MController::run()
{
    while(setFirstRun==true)//第一次读取所有的参数值
    {
        if(readAllParaData()==true)
        {

#ifdef AM335x_BOARD
            systemTimeInit();//时间校准
#endif
            if(database == NULL)
                database = new DataBase();//数据库
            //写入数据库
            saveRowToDataBase();
            setFirstRun = false;
        }
    }

    /*--------------------------*/
    while(setRun==true)
    {
        //判断是否有写命令
        if(runLevel[0]==true)
        {
            runUserWriteData();
        }
        else
        {
            if(runLevel[1]==true)
            {
                runGetFastData();
            }
            if(runLevel[2]==true)
            {
                runGetAlwaysData();
            }
        }

        readFaultData();//读取错误信息
    }
}

void MController::setRunLevel(int index,bool state)
{
    runLevel[index] = state;
}
//读取错误数据
void MController::readFaultData()
{

    int fault = paraArray[flt_num]->values;

    if(fault_num!= fault)
    {
        int ridex= flt_SEC;
        int widex = flt_read;
        bool writed = false;
        uint val =9;
        uint num = fault_num;
        writed = serial->modubsWrite((uint)flt_num,1,&num);
        writed = serial->modubsWrite(201,1,&val);
        if(writed == true)
        {
            runReadData(&ridex,&widex,ALL_READ);
            //写入数据库
            qDebug()<<"readFaultData"<<paraArray[flt_read]->values<<"\n";
            qDebug()<<paraArray[flt_YER]->values<<"/"<<paraArray[flt_MON]->values<<"/"<<paraArray[flt_DAY]->values<<"\n";
            qDebug()<<paraArray[flt_HUR]->values<<":"<<paraArray[flt_MIN]->values<<":"<<paraArray[flt_SEC]->values<<"\n";
            if(serial->comState == true)
                fault_num++;
        }
    }

}

//在线程中循环检测是否有变量要写
void MController::runUserWriteData()
{
    bool writed = false;
    for(int i=0;i<uslist_w.count();i++)
    {
        writed = serial->modubsWrite(uslist_w[i]->address,1,&(uslist_w[i]->val_w));
        if(writed==false)
            break;
    }
    qDebug()<<"runUserWriteData:"<<writed;

    emit writeDataDone(uslist_w,writed);
    uslist_w.clear();
    runLevel[0]=false;
}

//在线程中循环检测
void MController::runGetAlwaysData()
{
    bool read=runReadData(&allRIndx,&allWIndx,ALWARS_READ);
    if(serial->comState==false)
    {
        allRIndx = 0;
        allWIndx = 0;
        return;
    }
    if(read==true)//读取完
    {
        //写入数据库
        saveRowToDataBase();
        //发送信号，更新数据
        qDebug()<<QTime::currentTime()<<":runGetAlwaysDataFinish";
        emit readDataDone();
        runLevel[2]=false;
        allRIndx=0;
        allWIndx=0;

    }
}

//在线程中循环检测
void MController::runGetFastData()
{
    bool read=runReadData(&fastRIndx,&fastWIndx,FAST_READ);
    if(serial->comState==false)
    {
        fastRIndx = 0;
        fastWIndx = 0;
        return;
    }
    if(read==true)
    {
        //每个界面都有mcontroller的指针，X在页面打开时先绑定信号和槽
        //全部读完后，更新数据到界面
        emit readFastDataDone();
        runLevel[1]=false;
        fastRIndx=0;
        fastWIndx=0;

    }
}
//
bool MController::readAllParaData()
{
    bool read=runReadData(&allRIndx,&allWIndx,ALL_READ);
    if(serial->comState==false)
    {
        allRIndx = 0;
        allWIndx = 0;
        return false;
    }
    if(read==true)//读取完
    {
        //发送信号，更新数据
        qDebug()<<QTime::currentTime()<<":readAllParaData";
        emit readDataDone();
        emit readFastDataDone();
        allRIndx=0;
        allWIndx=0;
        return true;
    }
    return false;
}

//逆变器时间和本地时间进行校准
void MController::systemTimeInit()
{
    int y = paraArray[yyl]->values +paraArray[yyh]->values*100;
    int mon = paraArray[MM]->values;
    int dy = paraArray[dd]->values;
    int h = paraArray[hh]->values;
    int m = paraArray[mm]->values;
    int s = paraArray[ss]->values;
    QDate d =QDate(y,mon,dy);
    QTime t =QTime(h,m,s);
    QDateTime dt = QDateTime(d,t);
    time_t tt =dt.toTime_t();
    int error = stime(&tt);

    if(error != 0)
        qDebug()<<"error:stime";

    QProcess::execute("hwclock -w");//系统时钟和硬件时钟同步
}

//用户文件初始化
void MController::userFileInit()
{
    QString fileName = "user.xml";
    QFileInfo finfo(fileName);
    if(finfo.exists() == false)
    {
        QDomDocument doc;
        QDomProcessingInstruction instruction;
        instruction = doc.createProcessingInstruction("xml","version = \"1.0\" encoding = \"UTF-8\"");
        doc.appendChild(instruction);
        QDomElement root = doc.createElement("user");
        doc.appendChild(root);
        QString names[] = {"pwd","fault_num"};
        QString texts[] = {"12345","0"};
        for(int i=0;i<2;i++)
        {
            QDomElement p = doc.createElement(names[i]);
            QDomText t = doc.createTextNode(texts[i]);
            p.appendChild(t);
            root.appendChild(p);
        }
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)==false)
            return;
        QTextStream out(&file);
        doc.save(out,4);//必须为4
        file.close();
    }
}
//
void MController::timerInit()
{

    //alwaysTimer.setSingleShot(true);
    connect(&alwaysTimer,SIGNAL(timeout()),this,SLOT(alwaysReaderTimeOut()));
//    fastTimer=new QTimer(this);

    connect(&fastTimer,SIGNAL(timeout()),this,SLOT(fastReaderTimeOut()));
    alwaysTimer.start(10000);
    fastTimer.start(2000);
}

//从xml文件中读取数据，初始化paraMap
bool MController::paraMapInit()
{
    OperaFile xmlfile=OperaFile(":/Resources/parameter.xml");
    QDomNodeList nodes=xmlfile.getNodeList();
    if(nodes.isEmpty()== true)
        return false;

    for(int i=0;i<nodes.count();i++)
    {
        ParaInfo *para= new ParaInfo();
        QDomElement element=nodes.at(i).toElement();
        para->address=element.attribute("address").toInt(0,10);
        para->type=element.attribute("type").toInt();
        para->scaling=element.attribute("scaling").toInt();
        para->unit=element.attribute("unit");
        //paraMap.insert(name,para);
        paraArray[para->address]=para;
    }
    return true;
}

//将要发送的存入发送队列
void MController::userWriteData(ParaInfo* para ,int val)
{   
    para->val_w =  val;
    uslist_w.append(para);
    runLevel[0] = true;
}

void MController::userWriteData(ParaList list)
{
    uslist_w = list;
    runLevel[0] = true;
}
//
bool MController::runReadData(int *rIndx, int *wIndx, int type)
{
    //从原始数组获得数据
    //发送命令
    uchar rxBuffer[255];
    int rxCount=0;
    bool isread;
    DataInfo data(0,0);
    data = countReadData(rIndx,wIndx,type);

    if(*rIndx!=*wIndx)
    {
        mutexCom.lock();
        isread = serial->modubsRead(data.addr,data.len,rxBuffer,&rxCount);//读取串口数据
        mutexCom.unlock();
        setReadData(rIndx,wIndx,isread,rxBuffer);//更新数据到结构体
    }
    if(*rIndx==PARA_ARRAY_MAX)//读取完
        return true;
    return false;
}

//查找数组中的变量是否为总是可读
//然后判断多个可读变量是否为连续
//获得变量的地址发送到串口
DataInfo MController::countReadData(int *indxR, int *indxW,int type)
{
    ParaInfo* para=NULL;
    int addr=0,len=0,Type=0;

    for(;(*indxW)<PARA_ARRAY_MAX;(*indxW)++)//写下标加
    {
        para=paraArray[*indxW];
        if(para==NULL)
        {
            if(len==0)
                continue;
            else
                break;
        }

        Type = (para->type)&type;
        if(Type==type)//判断readtype中是否有type相同的未
        {          
            len++;
            if(len==1)//要发送的第一个变量的地址
                addr=para->address;
            else if(len>10)//一次最多读取10个变量
                break;
        }
        else
        {
            if(len>0)
                break;
        }
    }
    if(len>0)
        (*indxR)=addr;
    else
        (*indxR) = (*indxW);
    return DataInfo(addr,len);
}
//从串口读取读命令返回的数据
//把读到的值附给相应的变量
void MController::setReadData(int *rIndex,int *wIndx,bool isread,uchar *buffer)
{
    ParaInfo* para;
    unsigned int values=0;
    int index=3;//接收数据数组的下标，初始化值为第一个变量的位子
    int count=(*rIndex);
    count =*wIndx-count;

    for(int i=0;i<count;i++)
    {
        if(isread==true)
        {
            values = buffer[index];
            index++;
            values = values<<8;
            values = values+buffer[index];
            index++;
            para = paraArray[(*rIndex)];
            para->values=values;

            if(ParaInfo::isType(para,ALWARS_READ|WRITE)==true)//第一次开机读取写数据的值
                ParaInfo::clearType(para,ALWARS_READ);
        }
        else
            paraArray[(*rIndex)]->values=0;
        (*rIndex)++;
    }
}
void MController::saveRowToDataBase()
{
    RowData row;
    row.time = QTime::currentTime();
    row.db_Va=paraArray[Va]->values;
    row.db_Vb=paraArray[Vb]->values;
    row.db_Vc=paraArray[Vc]->values;
    row.db_Ia=paraArray[Ia]->values;
    row.db_Ib=paraArray[Ib]->values;
    row.db_Ic=paraArray[Ic]->values;
    row.db_kva=paraArray[kva]->values;
    row.db_kw=paraArray[kw]->values;
    row.db_kvar=paraArray[kvar]->values;
    row.db_pf=paraArray[pf]->values;
    row.db_freq=paraArray[freq]->values;
    database->insertTodayRow(row);
}
void MController::saveFaultRowToDataBase()
{
    QDate d(paraArray[flt_YER]->values,paraArray[flt_MON]->values,paraArray[flt_DAY]->values);
    QTime t(paraArray[flt_HUR]->values,paraArray[flt_MIN]->values,paraArray[flt_SEC]->values);
    QDateTime dt(d,t);

    QString num=QString("code_%1").arg(paraArray[flt_read]->values);
    QString name = "";
    QString details = "";
    OperaFile file(":/Resources/fault.xml");
    QDomNodeList nodes = file.FindElement(num).childNodes();
    if(nodes.isEmpty() == false)
    {
        name = nodes.at(0).toElement().text();
        details = nodes.at(1).toElement().text();
    }
    database->insertFaultRow(dt,name,details);
}
//设置参数的读取类型
void MController::setParaType(QList<int> names,int type)
{
    int name;
    int count=names.count();
    for(int i=0;i<count;i++)
    {
        name=names[i];
        ParaInfo::seType(paraArray[name],type);
    }
}
//清除参数的读取类型
void MController::clearAllParaType(int type)
{
    for(int i=0;i<PARA_ARRAY_MAX;i++)
    {
        if(paraArray[i]!=NULL)
            ParaInfo::clearType(paraArray[i],type);
    }
}

//在当前页面快速读定时器，槽
void MController::fastReaderTimeOut()
{
   // qDebug()<<QTime::currentTime()<<":fastReaderTimeOut:";
    runLevel[1]=true;
}

//在一定的时间间隔内一直读定时器，槽
void MController::alwaysReaderTimeOut()
{
    qDebug()<<QTime::currentTime()<<":alwaysReaderTimeOut:";
    runLevel[2]=true;
    //判断是否为alwaysread
    //判断是否为快速读取，是的话就不再读
}

void MController::timerEvent(QTimerEvent *e)
{
//    int id=e->timerId();
//    qDebug()<<debugCount<<":timerEvent"<<id;
//    debugCount++;
//    if(id==fastTimer)
//    {
//        runLevel[1]=true;
//        this->killTimer(fastTimer);
//    }
//    else if(id==alwaysTimer)
//    {
//        mutex_timer.lock();
//        runLevel[2]=true;
//        this->killTimer(alwaysTimer);
//        mutex_timer.unlock();
//    }

}

//从串口读取写命令返回的数据
//void MController::setWriteData()
//{
//    QByteArray array;
//    bool writed = serial->readData(&array);//读取串口数据
//    if(writed==false)
//    {}
//}

//查找数组中的变量是否为快速读
//然后判断多个可读变量是否为连续
//获得变量的地址发送到串口
/*void MController::sendFastData()
{
    int addr=paraList[fastWIndx]->address;
    int len=0;
    for(;fastWIndx<paraList.count();fastWIndx++)
    {
        if(paraList[fastWIndx]->isFast==true)
        {
            if(paraList[fastWIndx]->address==addr)
            {
                len++;
                addr++;
                if(len==1)
                   fastRIndx = fastWIndx;
            }
        }
        else
        {
            if(len>0)
                break;
        }
    }

    if(len>0)
        serial->SendReadOrder(paraList[fastRIndx]->address,len);
    else
        fastRIndx = fastWIndx;
}*/
//不用
//获得向串口发命令的列表
/*QList<ParaInfo*> MController::getCommParaList(bool a,bool f)
{
    QList<ParaInfo*> readlist;
    //加锁
    QMap<QString,ParaInfo*>::iterator paras=paraMap.begin();

    for(;paras!=paraMap.end();paras++)
    {
        if(paras.value()->isAlways==a&&paras.value()->isFast==f)
        {
            bool isert=false;
            for(int i=0;i<readlist.count();i++)//根据addr排序
            {
                if((readlist[i]->address)>(paras.value()->address))
                {
                    readlist.insert(i,paras.value());
                    isert=true;
                    break;
                }

            }
            if(isert==false)
                readlist<<paras.value();
        }
    }
    return readlist;
}*/
