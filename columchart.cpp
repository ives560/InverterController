#include "columchart.h"
#include "ui_columchart.h"

ColumChart::ColumChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColumChart)
{
    ui->setupUi(this);
    enpaint=false;
    x_axis.id = X;
    y_axis.id = Y;
}

ColumChart::~ColumChart()
{
    delete ui;
}

void ColumChart::CoordDataInit()
{
    origin=QPoint(60,-20);
    x_axis.end=QPoint(width()-20,-20);
    y_axis.end=QPoint(60,20-height());
}
//画图事件
void ColumChart::paintEvent(QPaintEvent *)
{
    QImage img;
    img=QImage(width(),height(),QImage::Format_ARGB32);
    img.fill(Qt::transparent);//设置背景为透明
    QPainter imgpaint(&img);
    imgpaint.translate(0,img.height());//原点变换

    imgpaint.setPen(Qt::yellow);
    imgpaint.setBrush(Qt::yellow);

    if(enpaint==true)
    {
        paintCoordinateSystem(&imgpaint);
        paintData(&imgpaint);
    }

    QPainter painter(this);
    painter.drawImage(0,0,img);
}

//画坐标系
void ColumChart::paintCoordinateSystem(QPainter *painter)
{

    paint_X_Axis(painter);
    paint_Y_Axis(painter);
}

//画X轴刻度
void ColumChart::paint_X_Axis(QPainter *painter)
{
    QPoint end =QPoint(x_axis.end.x()+10,x_axis.end.y());
    QPoint b = QPoint(end.x()-3,end.y()+3);
    QPoint c = QPoint(end.x()-3,end.y()-3);
    QPoint points[]={end,b,c};
    painter->drawLine(origin,end);//X轴
    painter->drawPolygon(points,3);//终点三角
    painter->drawText(end,x_axis.unit);//单位
    /*----------------画X轴刻度---------------------------------*/
    end = x_axis.end;
    QPointF ps=origin;
    QPointF pe=QPoint(origin.x(),origin.y()+3);

    for(int i=1;i<=x_axis.inter;i++)
    {
        double val = x_axis.mini + i*x_axis.step;
        double x = val*x_axis.scale+origin.x();
        ps.setX(x);
        pe.setX(x);
        painter->drawLine(ps,pe);
        painter->drawText(QPointF(pe.x()-5,pe.y()+15),QString("%1").arg(val));

    }
}

//画Y轴刻度
void ColumChart::paint_Y_Axis(QPainter *painter)
{
    QPoint end = QPoint(y_axis.end.x(),y_axis.end.y()-5);
    QPoint b = QPoint(end.x()-3,end.y()+3);
    QPoint c = QPoint(end.x()+3,end.y()+3);
    QPoint points[]={end,b,c};

    painter->drawLine(origin,end);//Y轴
    painter->drawPolygon(points,3);//终点三角
    //painter->drawText(QPoint(end.x()-10,end.y()),y_axis.unit);//单位
    painter->drawText(0,end.y()-10,end.x()-5,15,(Qt::AlignRight)|(Qt::AlignVCenter),QString("%1").arg(y_axis.unit));
    /*----------------画Y轴刻度---------------------------------*/
    end = y_axis.end;
    QPoint ps=origin;
    QPoint pe=QPoint(origin.x()-3,origin.y());
    int hh=(origin.y()-end.y()-10)/y_axis.inter;
    for (int i=0;i<=y_axis.inter;i++)
    {
        painter->drawLine(ps,pe);
        int val = y_axis.mini+i*y_axis.step;
        painter->drawText(0,pe.y()-5,pe.x(),15,(Qt::AlignRight)|(Qt::AlignVCenter),QString("%1").arg(val));
        //painter->drawText(QPoint(pe.x()-30,pe.y()+5),tr("%1").arg(val));
        ps.setY(ps.y()-hh);
        pe.setY(pe.y()-hh);
    }
}
//
void ColumChart::paintData(QPainter *painter)
{

    const int count = points.count();
    for(int i=0;i<count;i++)
    {
        int w = 10;
        int h = origin.y() - points[i].y();
        int x = points[i].x()-(w/2);
        int y = points[i].y();


        painter->drawRect(x,y,w,h);
    }
}

void ColumChart::paint(bool en)
{
    enpaint=en;
    if(en==true)
        update();
}

void ColumChart::setQuery(QSqlQuery query/*,flot scale 值的转换*/)
{
    count_Y_Max(query);
    countStep(&y_axis);
    countScale(&y_axis);
    countPoints(query);
}

//计算要画出的所有坐标点
void ColumChart::countPoints(QSqlQuery query)
{
    points.clear();
    int i=0;
    if(query.first()== true)
    {
        do
        {
            qreal x = convertValue(X,query.value(0))+ origin.x();
            qreal y = convertValue(Y,query.value(1)) + origin.y();
            QPointF pf = QPointF(x,y);

            points.append(pf);
            i++;
        }while(query.next());
    }

}

//获得表中的最大值
void ColumChart::count_Y_Max(QSqlQuery query)
{
    int max=0;
    while(query.next())
    {
       max=query.value(1).toInt();
       if(max>y_axis.max)
           y_axis.max=max;
    }
}

//转换为坐标值
qreal ColumChart::convertValue(int axisId,QVariant val)
{
    qreal r;
    if(axisId==X)
    {
        QDate date = val.toDate();
        r = date.day();
        r = r*x_axis.scale;
    }
    else if(axisId==Y)
    {
        r = val.toInt();
        r = r*y_axis.scale;
    }
    return r;
}


//设置坐标轴参数
void ColumChart::setAxis(int axisId,int mini, int max, int inter,QString unit)
{
    if(max<mini)
        return;

    AxisData* axis;
    if(axisId==X)
        axis = &x_axis;
    else if(axisId==Y)
        axis = &y_axis;
    else
        return;

    axis->unit = unit;
    axis->mini= mini;
    axis->max = max;
    axis->inter = inter;

    countStep(axis);
    countScale(axis);
}
//
void ColumChart::countStep(AxisData *axis)
{
    axis->step = (axis->max- axis->mini)/axis->inter;
    int m = axis->step*axis->inter;
    if(m<axis->max)
    {
        axis->step = (axis->max+ axis->inter - axis->mini)/axis->inter;
        axis->max = axis->step*axis->inter;
    }
}

//计算比例参数
void ColumChart::countScale(AxisData *axis)
{
    float a,b;
    if(axis->id==X)
    {
        a = axis->max - axis->mini;
        b = axis->end.x() - origin.x()-10;//
        axis->scale = b/a;
    }
    else if(axis->id==Y)
    {
        a = axis->max - axis->mini;
        b = axis->end.y() - origin.y();
        axis->scale = b/a;
    }
}
