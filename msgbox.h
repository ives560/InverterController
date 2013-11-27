#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>

namespace Ui {
class MsgBox;
}

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    enum Icon{Question, Critical};
    enum Button{Ok                 = 0x00000400,
                Cancel             = 0x00400000,};
public:
    explicit MsgBox(QWidget *parent = 0,Icon icon=Question, QString text="");

    ~MsgBox();
private:
    void switchIcon(Icon icon);
    void setQuestionIcon();
    void setCriticalIcon();
    void setText(QString text);


private:
    Ui::MsgBox *ui;

private slots:
    void ok_button_clicked();
    void cancel_button_clicked();
};

#endif // MSGBOX_H
