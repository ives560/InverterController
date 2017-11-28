#ifndef MINPUTCONTEXT_H
#define MINPUTCONTEXT_H

#include <QInputContext>
#include <QDebug>

class KeyBoard;

class MInputContext : public QInputContext
{
	Q_OBJECT

public:
	MInputContext(QObject *parent=0);
	~MInputContext();

	QString identifierName();
	QString language();
	bool isComposing() const;
	void reset();
	bool filterEvent(const QEvent* event);

private:
	void updatePosition();

private:
	KeyBoard* keyboard;

private slots:
    void sendCharacter(int key);

};

#endif // MINPUTCONTEXT_H
