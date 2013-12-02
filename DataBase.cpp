#include "DataBase.h"
#include <QDate>
DataBase::DataBase()
{
    //记录修改前的日期和时间，
    //日期相同，时间不同，读取表，删除修改时间后已经存在的行
    //日期不同，表存在，删除表

    //一个数据库保存一个月的数据表，
    //和总量表，表中保存每一个月累计的总量和每一年累计的总量的行
    //在新建的总量表时，复制上一个月的总量表到当前表
    //在查询月和年时进行计算并保存
    //临时变量保存累计的日，月，年数据，在时间改变时减去数据库中的数据，把日数据清零
    //修改系统时间，数据库时间怎么设置
    dbName = "database";
    tbToday = "tb_" + QDate::currentDate().toString("yyyyMMdd");
    tbTotal = "total";
    tbFault = "fault";
    db = QSqlDatabase::addDatabase("QSQLITE");//默认连接，没有连接名
    bool t = createDataBase(dbName);
    if(t==true)
        t = newTodayTable();
    if(t==true)
        t = newTotleTable();
    t= newFaultTable();
    //新建历史故障表

    //提交更改后才能将数据真正修改到数据库
    //model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    //submitRows=0;

}

DataBase::~DataBase(void)
{
    closeDataBase();

}

//设备连续运行时，检测日期的改变
void DataBase::tableCheck()
{
    QString tody="tb_" + QDate::currentDate().toString("yyyyMMdd");

    if(tbToday!=tody)
    {
        tbToday=tody;
        newTodayTable();
    }

}

//时间设置改变，数据库中的数据做相应调整
void DataBase::timeChange(QDateTime d,QDateTime new_d)
{
    QSqlQuery query;
    if(d.date()!=new_d.date())//日期改变
    {
        query.exec(QString("drop %1").arg(tbToday));
        //清除今天的数据
        newTodayTable(false);
    }
    else if(d.time()!=new_d.time())//时间改变
    {
        QString time=new_d.time().toString("hh-mm-ss");
        QString cmd=QString("delete from %1 where time >= %2").arg(tbToday).arg(time);
        query.exec(cmd);

    }

}
//创建数据库
bool DataBase::createDataBase(QString name)
{
    if(db.isOpen()==true)
        db.close();

    db.setDatabaseName(name);
	return db.open();
}

//关闭数据库
void DataBase::closeDataBase()
{
    if(db.isOpen()==true)
        db.close();
}

//新建需要永久保存的参数数据的表
bool DataBase::newTodayTable(bool keep)
{
    QString list ="Tm time PRIMARY KEY,Va interger, Vb interger, Vc interger,\
                   Ia interger, Ib interger, Ic interger, kva interger, kw interger,\
                   kvar interger, pf interger, freq interger";
    QString cmd=QString("create table %1 (%2)").arg(tbToday).arg(list);
    return newTable(tbToday,cmd,keep);

}

//新建统计表，记录每个月的数据和每年的数据，year,month字段
bool DataBase::newTotleTable(bool keep)
{
    QString list ="Dt date PRIMARY KEY, tl_kw interger";
    QString cmd=QString("create table %1 (%2)").arg(tbTotal).arg(list);
    return newTable(tbTotal,cmd,keep);
}

//新建错误表
bool DataBase::newFaultTable()
{
    QString list ="id INTEGER PRIMARY KEY, DaTm DATETIME,FName TEXT,FDetails TEXT";
    QString cmd=QString("create table %1 (%2)").arg(tbFault).arg(list);
    return newTable(tbFault,cmd,true);
}

//新建表
bool DataBase::newTable(QString name,QString cmd,bool keep)
{
    QSqlQuery query;
    if(searchTable(name)==true)
    {
        if(keep==false)
            query.exec(QString("drop %1").arg(name));
        else
           return true;
    }
    return query.exec(cmd);
}

//查找表
bool DataBase::searchTable(QString name)
{
    QStringList list=getTables();
    if(list.indexOf(name)<0)
        return false;
    else
        return true;
}

QStringList DataBase::getTables()
{
    return db.tables();
}

//插入一行数据
bool DataBase::insertTodayRow(RowData row)
{
    QSqlQuery query;
    QString cmd=QString("insert into %1 values (?,?,?,?,?,?,?,?,?,?,?,?)").arg(tbToday);
    query.prepare(cmd);
    query.addBindValue(row.time);
    query.addBindValue(row.db_Va);
    query.addBindValue(row.db_Vb);
    query.addBindValue(row.db_Vc);
    query.addBindValue(row.db_Ia);
    query.addBindValue(row.db_Ib);
    query.addBindValue(row.db_Ic);
    query.addBindValue(row.db_kva);
    query.addBindValue(row.db_kw);
    query.addBindValue(row.db_kvar);
    query.addBindValue(row.db_pf);
    query.addBindValue(row.db_freq);
    return query.exec();
}

bool DataBase::insertFaultRow(QDateTime dt,QString name,QString details)
{
    QSqlQuery query;
    QString cmd=QString("insert into %1 (DaTm,FName,FDetails) values (?,?,?)").arg(tbFault);
    query.prepare(cmd);
    query.addBindValue(dt);
    query.addBindValue(name);
    query.addBindValue(details);
    return query.exec();
}

//读取要画曲线图的数据
QSqlQuery DataBase::readTodayTable(QString clum)
{
    QSqlQuery query;
    QString cmd=QString("select Tm,%1 from %2").arg(clum).arg(tbToday);

    query.exec(cmd);

    return query;
}

QSqlQuery DataBase::readMonthTable(QDate date)
{
    QSqlQuery query;
    QString d = date.toString("yyyy-MM-dd");
    QString cmd=QString("select Dt,tl_kw from %2 where Dt >= %1").arg(d).arg(tbTotal);

    query.exec(cmd);

    return query;
}

//QSqlTableModel DataBase::getTableModel(QString name)
//{
//	QSqlTableModel table;
//	if(searchTable(name)==false)
//		newTable(name);
//
//	table.setTable(name);
//	return table;
//}

//获得表中一列的所有数据
//QSqlTableModel DataBase::getTableList(QString listName)
//{
//    model.setFilter(listName);
//    model.select();

//    return query;
//}


//获得画曲线图的数据，返回数据列表

//保存一行数据
/*bool DataBase::saveAlwaysData(QString time,int a,int v, int d)
{
    int rowNum=model.rowCount();
    model.insertRow(rowNum);
    model.setData(model.index(rowNum,0),time);
    model.setData(model.index(rowNum,1),a);
    model.setData(model.index(rowNum,2),v);
    model.setData(model.index(rowNum,3),d);
    model.setData(model.index(rowNum,4),"");

    submitRows++;
    if(submitRows==10)
    {
        submitRows=0;
        return model.submitAll();
    }
    return true;
}*/

/*bool DataBase::newTable(QString name)
{
	QSqlQuery query;
	query.exec("create table student(id varchar,name varchar)");
	query.exec(QObject::tr("insert into student values(1,'李刚'"));
	query.exec(QObject::tr("insert into student values(2,'苹果'"));
	query.exec(QObject::tr("insert into student values(3,'葡萄'"));
	query.exec(QObject::tr("insert into student values(4,'梨子'"));
	query.exec(QObject::tr("insert into student values(5,'橘子'"));
	query.exec(QObject::tr("insert into student values(6,'核桃'"));
	query.exec(QObject::tr("insert into student values(7,'芒果'"));
	query.exec("select id,name from student where id>=1");
	while(query.next())
	{

		int ele0=query.value(0).toInt();
		QString ele1=query.value(1).toString();
		qDebug()<<ele0<<ele1;
	}
    query.exec(QObject::tr("drop student"));//删除表

	return true;
}*/
