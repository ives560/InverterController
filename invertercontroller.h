#ifndef INVERTERCONTROLLER_H
#define INVERTERCONTROLLER_H

#include <QtGui/QWidget>
#include "ui_invertercontroller.h"
#include <QWidget>

#include "common.h"
#include "mcontroller.h"

class InverterController;
#include "submenu.h"

class InverterController : public QWidget
{
	Q_OBJECT

public:
	InverterController(QWidget *parent = 0, Qt::WFlags flags = 0);
	~InverterController();

private:
	Ui::InverterControllerClass ui;

private:
	QVBoxLayout* layout;
	QToolButton* tBtn_back;
//	QWidget* current;
public:
    MController* controller;

private:
	void load_mainface();
	void changeUi(bool change);
	void setupBackButton();

public:
	void hideTopInterface();
	void addTopInterface(QWidget* w);
	void removeTopInterface();
	void removeAllInterface();
	void removeWidget(SubMenu* sub);

private:
    void paintEvent(QPaintEvent *);

private slots:
	void on_tBtn_power_clicked();
	void on_tBtn_main_clicked();
	void on_tBtn_function_clicked();
	void pBtn_back_clicked();
signals:
    void enReadData();

};

#endif // INVERTERCONTROLLER_H
