#pragma once
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QSqlTableModel>

#include <QDebug>

#include "common.h"

class DataBase
{

public:
    DataBase();
	~DataBase(void);

public:

	bool createDataBase(QString name);
    inline void closeDataBase();
    bool newTodayTable(bool keep=true);
    bool newTotleTable(bool keep=true);
    bool newFaultTable();
    bool newTable(QString name,QString cmd, bool keep);
	bool searchTable(QString name);
    QStringList getTables();
    bool insertTodayRow(RowData row);
    bool insertFaultRow(QDateTime dt,QString name,QString details);

    QSqlQuery readTodayTable(QString clum);
    QSqlQuery readMonthTable(QDate date);
    void tableCheck();
    void timeChange(QDateTime d,QDateTime new_d);
    bool saveAlwaysData(QString time,int a,int v, int d);
    //QSqlTableModel getTableList(QString listName);
	//QSqlTableModel getTableModel(QString name);

private:
    QSqlDatabase db;
    QSqlTableModel model;
    int submitRows;

public:
    QString tbToday;
    QString tbTotal;
    QString tbFault;
    QString dbName;

};
