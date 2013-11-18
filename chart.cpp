#include "chart.h"
#include <QSqlRecord>
#include <QTime>

Chart::Chart(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	enpaint=false;
    x_axis.id = X;
    y_axis.id = Y;
    CoordDataInit();
    setAxis(Chart::X,0,24,6,"");
    setAxis(Chart::Y,0,100,5,"");
}

Chart::~Chart()
{

}

void Chart::CoordDataInit()
{
    origin=QPoint(60,-20);
    x_axis.end=QPoint(width()-20,-20);
    y_axis.end=QPoint(60,20-height());
}
//画图事件
void Chart::paintEvent(QPaintEvent *)
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
void Chart::paintCoordinateSystem(QPainter *painter)
{

    paint_X_Axis(painter);
    paint_Y_Axis(painter);
}

//画X轴刻度
void Chart::paint_X_Axis(QPainter *painter)
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
    QPoint ps=origin;
    QPoint pe=QPoint(origin.x(),origin.y()+3);
    int wh=(end.x()-origin.x()-10)/x_axis.inter;
    ps.setX(ps.x()+wh);
    pe.setX(pe.x()+wh);
    for(int i=1;i<=x_axis.inter;i++)
    {
        painter->drawLine(ps,pe);
        int val = x_axis.mini + i*x_axis.step;
        painter->drawText(QPoint(pe.x()-5,pe.y()+15),QString("%1").arg(val));
        ps.setX(ps.x()+wh);
        pe.setX(pe.x()+wh);
    }
}

//画Y轴刻度
void Chart::paint_Y_Axis(QPainter *painter)
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
void Chart::paintData(QPainter *painter)
{
    //painter->drawLines(points);
    int count = points.count();
    for(int i=1;i<count;i++)
    {
        painter->drawLine(points[i-1],points[i]);
    }
}

void Chart::paint(bool en)
{
    enpaint=en;
    if(en==true)
        update();
}

void Chart::setQuery(QSqlQuery query/*,flot scale 值的转换*/)
{
    count_Y_Max(query);
    countStep(&y_axis);
    countScale(&y_axis);
    countPoints(query);
}

//计算要画出的所有坐标点
void Chart::countPoints(QSqlQuery query)
{
    points.clear();
    int i=0;
    QTime t_old;

    while(query.next())
    {
        qreal x = convertValue(X,query.value(0))+ origin.x();
        qreal y = convertValue(Y,query.value(1)) + origin.y();
        QPointF pf = QPointF(x,y);

        if(i>0)
        {
            QTime t = query.value(0).toTime();
            addEmptyPoint(t,t_old,pf);
        }
        points.append(pf);
        t_old = query.value(0).toTime();
        i++;
    }

}

//获得表中的最大值
void Chart::count_Y_Max(QSqlQuery query)
{
    int max=0;
    while(query.next())
    {
       max=query.value(1).toInt();
       if(max>y_axis.max)
           y_axis.max=max;
    }
    query.first();
}
//添加空值
void Chart::addEmptyPoint(QTime t, QTime t_old, QPointF p)
{
    t_old = t_old.addSecs(600);
    if(t>t_old)//两点之间的时间大于一定值，
    {
        QPointF pf_l = points.last();
        pf_l.setY(origin.y());
        points.append(pf_l);

        QPointF pf = QPointF(p.x(),origin.y());
        points.append(pf);
    }
}

//转换为坐标值
qreal Chart::convertValue(int axisId,QVariant val)
{
    qreal r;
    if(axisId==X)
    {
        QTime time = val.toTime();
        r = time.second()+time.minute()*60;
        r /= 3600;
        r += time.hour();
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
void Chart::setAxis(int axisId,int mini, int max, int inter,QString unit)
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
void Chart::countStep(AxisData *axis)
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
void Chart::countScale(AxisData *axis)
{
    float a,b;
    if(axis->id==X)
    {
        a = axis->max - axis->mini;
        b = axis->end.x() - origin.x();
        axis->scale = b/a;
    }
    else if(axis->id==Y)
    {
        a = axis->max - axis->mini;
        b = axis->end.y() - origin.y();
        axis->scale = b/a;
    }
}

