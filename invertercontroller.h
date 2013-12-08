#ifndef INVERTERCONTROLLER_H
#define INVERTERCONTROLLER_H

#include <QtGui/QWidget>
#include "ui_invertercontroller.h"
#include <QWidget>

#include "common.h"
#include "mcontroller.h"

class SubMenu;

class InverterController : public QWidget
{
	Q_OBJECT

private:
    Ui::InverterControllerClass ui;

    QVBoxLayout* layout;
    QToolButton* tBtn_back;

    MController* controller;

public:
	InverterController(QWidget *parent = 0, Qt::WFlags flags = 0);
	~InverterController();

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
    void readFastDataSlot();

};

#endif // INVERTERCONTROLLER_H
