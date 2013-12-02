#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include "ui_chart.h"
#include <QPaintEvent>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTime>

struct AxisData{

    int id;
    QString unit;
//    QPoint origin;		//起点坐标
    QPoint end;         //终点坐标
    int mini;        //最小值
    int max;         //最大值
    float scale;     //坐标轴在画布上的像素点/实际表示的最大值
    int inter;      //间隔数
    int step;       //间隔值
};

class Chart : public QWidget
{
	Q_OBJECT

public:
	Chart(QWidget *parent = 0);
	~Chart();
    enum Axis{X,Y};
private:
	Ui::Chart ui;

private:
	bool enpaint;
	QPoint origin;		//原点坐标
    AxisData x_axis;    //坐标系参数变量
    AxisData y_axis;
    QVector<QPointF> points;

private:
	void paintCoordinateSystem(QPainter *);
    void paint_X_Axis(QPainter *);
    void paint_Y_Axis(QPainter *);
    void paintData(QPainter *);
    qreal convertValue(int axisId,QVariant val);
    void addEmptyPoint(QTime t, QTime t_old, QPointF p);
    void count_Y_Max(QSqlQuery query);
    void countPoints(QSqlQuery query);
    void getPoints();
//坐标系参数设置
public:
	void CoordDataInit();
    void countScale(AxisData *axis);
    void countStep(AxisData *axis);
    void setQuery(QSqlQuery query/*,flot scale 值的转换*/);
    void setAxis(int axisId,int mini,int max,int inter, QString unit);
	void setData();
	void paint(bool en);


protected:
    void paintEvent(QPaintEvent *);
};

#endif // CHART_H
