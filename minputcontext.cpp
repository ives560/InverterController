#include "minputcontext.h"
#include "keyboard.h"

MInputContext::MInputContext(QObject *parent)
	: QInputContext(parent)
{
    keyboard=new KeyBoard();
    connect(keyboard, SIGNAL(characterGenerated(int)), SLOT(sendCharacter(int)));
}

MInputContext::~MInputContext()
{

}

QString MInputContext::identifierName()
{
	return "MyInputPannelContext";
}

void MInputContext::reset()
{
}

bool MInputContext::isComposing() const
{
	return false;
}

QString MInputContext::language()
{
	return "en_US";
}

bool MInputContext::filterEvent(const QEvent* event)
{
	if (event->type() == QEvent::RequestSoftwareInputPanel) {
		updatePosition();
		keyboard->show();
		return true;
	} else if (event->type() == QEvent::CloseSoftwareInputPanel) {
		keyboard->hide();
		return true;
	}
	return false;
}
void MInputContext::sendCharacter(int key)
 {
    QPointer<QWidget> w = focusWidget();

    if (!w)
        return;


    switch(key)
    {
        case Qt::Key_Escape:
            {
                key=Qt::Key_A;
                QKeyEvent keyPress_Ctrl_A(QEvent::KeyPress,key,Qt::ControlModifier,QString(key));
                QApplication::sendEvent(w, &keyPress_Ctrl_A);
                key=Qt::Key_Backspace;
                QKeyEvent keyPress_CE(QEvent::KeyPress,key,Qt::NoModifier,QString(key));
                QApplication::sendEvent(w, &keyPress_CE);
            }
            break;
        default:
            {
                QKeyEvent keyPress(QEvent::KeyPress,key,Qt::NoModifier,QString(key));
                QApplication::sendEvent(w, &keyPress);
                qDebug()<<"keyPress";
            }
            break;
    }

}


void MInputContext::updatePosition()
{
	QWidget *widget = focusWidget();
	if (!widget)
		return;

	QRect widgetRect = widget->rect();
	QPoint panelPos = QPoint(widgetRect.left(), widgetRect.bottom() + 2);
	panelPos = widget->mapToGlobal(panelPos);
	keyboard->move(panelPos);


}
