#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include "ui_toolbar.h"
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QPushButton>

class ToolBar : public QWidget
{
	Q_OBJECT

public:
	ToolBar(QWidget *parent = 0);
	~ToolBar();

private:
	Ui::ToolBar ui;
	QPushButton* pBtn_back;
public:
	enum {POWER,MAIN,FUNCTION,BACK};

public:
	void changeUi(bool change);
	void setupBackButton();

private:

protected:
	void paintEvent(QPaintEvent *);


private slots:
	void on_tBtn_power_clicked();
	void on_tBtn_main_clicked();
	void on_tBtn_function_clicked();
	void pBtn_back_clicked();


signals:
	void button_clicked(int);
};

#endif // TOOLBAR_H
