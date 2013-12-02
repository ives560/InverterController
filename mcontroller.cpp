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
//    database = new DataBase();//数据库
    serial=new MSerialOperate();//新建串口

    paraMapInit();//参数初始化

    userFileInit();
    OperaFile file("user.xml");
    fault_num= file.getElementText("fault_num").toInt();

    fault_queue = new FaultQueue();

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
            //readAllFaultData();
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
                //readFaultData();//读取错误信息

            }
            if(runLevel[2]==true)
            {
                runGetAlwaysData();
            }
        }
    }
}

void MController::setRunLevel(int index,bool state)
{
    runLevel[index] = state;
}

//
bool MController::getFaultData(uchar num)
{
    int ridex= PARA::flt_SEC;
    int widex = PARA::flt_read;
    bool success = false;
    short val =9;
    short m = (short)num;
    success = serial->modubsWrite((uint)PARA::flt_num,1,&m);//  先写入要读取的错误号
    success = serial->modubsWrite(201,1,&val);//再写命令

    if(success == true)
    {
        success = runReadData(&ridex,&widex,ALL_READ);
        if((success==true)&&(paralist[PARA::flt_read]->values>0))
        {

            fault_queue->addItem(paralist[PARA::flt_read]->values,
                             paralist[PARA::flt_YER]->values,paralist[PARA::flt_MON]->values,paralist[PARA::flt_DAY]->values,
                             paralist[PARA::flt_HUR]->values,paralist[PARA::flt_MIN]->values,paralist[PARA::flt_SEC]->values);

            return true;
        }
        //if(serial->comState == true)
        //    ;

    }
    return false;
}

//
void MController::readAllFaultData()
{
    uchar curt_fault = (uchar)paralist[PARA::flt_num]->values;
    fault_num = curt_fault;
    do
    {
        if(getFaultData(fault_num)==false)
            return;

        fault_num--;
    }while(fault_num!=curt_fault);

}
//读取错误数据
void MController::readFaultData()
{
    uchar curt_fault = paralist[PARA::flt_num]->values;

     while(fault_num != curt_fault)
    {
         fault_num++;
        if(getFaultData(fault_num)==false)
        {
            fault_num--;
            return;
        }
        else
        {
            //发送报警信号
            emit haveReadNewFault(fault_num);
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
        emit readAlwaysDataDone();
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
        emit readAlwaysDataDone();
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
    int y = paralist[PARA::yyl]->values +paralist[PARA::yyh]->values*100;
    int mon = paralist[PARA::MM]->values;
    int dy = paralist[PARA::dd]->values;
    int h = paralist[PARA::hh]->values;
    int m = paralist[PARA::mm]->values;
    int s = paralist[PARA::ss]->values;
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
    fastTimer.start(1000);
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
        ParaItem *para= new ParaItem();
        QDomElement element=nodes.at(i).toElement();
        if(element.isNull()==false)//忽略注释或空行
        {
            para->name = element.attribute("name");
            para->address=element.attribute("address").toInt(0,10);
            para->type=element.attribute("type").toInt();
            para->scaling=element.attribute("scaling").toInt();
            para->unit=element.attribute("unit");
            //paraMap.insert(name,para);
            paralist.insert(para->address,para);
        }
    }
    return true;
}

//将要发送的存入发送队列
void MController::userWriteData(int name ,short int val)
{   
    ParaItem *para = paralist[name];
    para->val_w =  val;
    uslist_w.append(para);
    runLevel[0] = true;
}

void MController::userWriteData(ListParaItem list)
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
    ParaItem* para=NULL;
    int addr=0,len=0,Type=0;

    for(;(*indxW)<PARA_ARRAY_MAX;(*indxW)++)//写下标加
    {
        para=paralist[*indxW];
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
    ParaItem* para;
    short int values=0;
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
            para = paralist[(*rIndex)];
            para->values=values;

            if(paralist.isType((*rIndex),ALWARS_READ|WRITE)==true)//第一次开机读取写数据的值
                paralist.clearType((*rIndex),ALWARS_READ);
        }
        else
            paralist[(*rIndex)]->values=0;
        (*rIndex)++;
    }
}
void MController::saveRowToDataBase()
{
    RowData row;
    row.time = QTime::currentTime();
    row.db_Va=paralist[PARA::Va]->values;
    row.db_Vb=paralist[PARA::Vb]->values;
    row.db_Vc=paralist[PARA::Vc]->values;
    row.db_Ia=paralist[PARA::Ia]->values;
    row.db_Ib=paralist[PARA::Ib]->values;
    row.db_Ic=paralist[PARA::Ic]->values;
    row.db_kva=paralist[PARA::kva]->values;
    row.db_kw=paralist[PARA::kw]->values;
    row.db_kvar=paralist[PARA::kvar]->values;
    row.db_pf=paralist[PARA::pf]->values;
    row.db_freq=paralist[PARA::freq]->values;
    database->insertTodayRow(row);
}
void MController::saveFaultRowToDataBase()
{
    QDate d(paralist[PARA::flt_YER]->values,paralist[PARA::flt_MON]->values,paralist[PARA::flt_DAY]->values);
    QTime t(paralist[PARA::flt_HUR]->values,paralist[PARA::flt_MIN]->values,paralist[PARA::flt_SEC]->values);
    QDateTime dt(d,t);

    QString num=QString("code_%1").arg(paralist[PARA::flt_read]->values);
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
