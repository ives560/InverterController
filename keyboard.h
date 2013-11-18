#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QDialog>
#include <QtCore>
#include "ui_keyboard.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <QSignalMapper>

class MInputContext;

class KeyBoard : public QDialog
{
	Q_OBJECT

public:
    KeyBoard(QWidget *parent = 0);
	~KeyBoard();

private:
	Ui::KeyBoard ui;
	QSignalMapper* mapper;
    QWidget *lastFocusedWidget;

private:
	void singnalMapperInit();
    bool event(QEvent *e);

private slots:
    void keyClicked(int);
    void saveFocusWidget(QWidget *oldFocus, QWidget *newFocus);
    void mousePressEvent(QMouseEvent *);

signals:
    void characterGenerated(int key);





};

#endif // KEYBOARD_H
