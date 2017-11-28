#include "invertercontroller.h"
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include "minputcontext.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

    /*-------虚拟键盘设置----------*/
    MInputContext* ic = new MInputContext();
    a.setInputContext(ic);
    /*-------中文乱码设置---------*/
//    QTextCodec* codec =QTextCodec::codecForName("UTF8");
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
//    QTextCodec::setCodecForLocale(codec);
/*-----------------------------------*/
    QTranslator translator;
    translator.load(":/zh_CN.qm");
    a.installTranslator(&translator);
	InverterController w;
    w.show();
	return a.exec();
}
