#ifndef FUNCTIONTABLE_H
#define FUNCTIONTABLE_H

#include "submenu.h"
#include "ui_functiontable.h"
class FunctionTable : public SubMenu
{
	Q_OBJECT

public:
    FunctionTable(QWidget *parent=0,MController* mc=0);
	~FunctionTable();

private:
	enum ID{OPERATION,HISTORY,ONOFF,PARAMETER};
    void setupUi();

private:
    Ui::FunctionTable ui_function;
	QToolButton *operationInfo;
	QToolButton *historyInfo;
	QToolButton *onOff;
	QToolButton *paramSet;

private slots:
    void operationInfo_Clicked();
    void historyInfo_Clicked();
    void onOff_Clicked();
    void paramSet_Clicked();
	
};

#endif // FUNCTIONTABLE_H
