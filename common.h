#ifndef COMMON_H
#define COMMON_H

#include <QMap>
#include <QFile>
#include <QList>
#include <QPair>
#include <QLabel>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QQueue>
#include <QMutex>
#include <QPixmap>
#include <QLineEdit>
#include <QBitArray>
#include <QTableView>
#include <QScrollBar>
#include <QMessageBox>
#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDomElement>
#include <QDomDocument>
#include <QSqlTableModel>
#include <QTableWidgetItem>
#include <QStandardItemModel>

#include "parainfo.h"
/*--------screen---------------*/
#define SCREEN_WIDE 800
#define SCREEN_HIGH 480
/*--------modbuss frame-----------*/
#define MAIN_ENGINE_ADDRESS 0X01
#define READ_FUNCTION_CODE  0x03
#define WRITE_FUNCTION_CODE 0x10

/*--------------------*/
#define AM335x_BOARD


typedef QList< ParaInfo*> ParaList;

/*-------要保存到数据库中的一行数据---------*/
typedef struct {

    QTime time;
    int db_Va;
    int db_Vb;
    int db_Vc;
    int db_Ia;
    int db_Ib;
    int db_Ic;
    int db_kva;
    int db_kw;
    int db_kvar;
    int db_pf;
    int db_freq;//12个
    //int db_today;
}RowData;

typedef struct {

    QVariant x;
    QVariant y;
}ChartData;

#endif // COMMON_H
