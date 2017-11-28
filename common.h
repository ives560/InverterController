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
#include <QPainter>
#include <QPixmap>
#include <QHeaderView>
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

//#include "parainfo.h"
#include "paralist.h"
/*--------screen---------------*/
#define SCREEN_WIDE 800
#define SCREEN_HIGH 480
/*--------modbuss frame-----------*/
#define MAIN_ENGINE_ADDRESS 0X01
#define READ_FUNCTION_CODE  0x03
#define WRITE_FUNCTION_CODE 0x10
#define MAX_FRAME_REGIST    10

#if(QT_VERSION == 0x040702)
    #define AM335x_BOARD
#endif

/*-------要保存到数据库中的一行数据---------*/
typedef struct {

    QTime time;
    double db_Va;
    double db_Vb;
    double db_Vc;
    double db_Ia;
    double db_Ib;
    double db_Ic;
    double db_kva;
    double db_kw;
    double db_kvar;
    double db_pf;
    double db_freq;//12个
    //int db_today;
}RowData;

typedef struct {

    QVariant x;
    QVariant y;
}ChartData;

#endif // COMMON_H
