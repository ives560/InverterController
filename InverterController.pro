#-------------------------------------------------
#
# Project created by QtCreator 2013-08-15T11:00:57
#
#-------------------------------------------------

QT       += core gui widgets
QT       += sql
QT       += xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InverterController
TEMPLATE = app

TRANSLATIONS = zh_CN.ts en_EN.ts

INCLUDEPATH += control control/modbus widgets

SOURCES += main.cpp\
    operafile.cpp \
    userfile.cpp \
    paralist.cpp \
    control/vtcptoserial.cpp \
    control/mcontroller.cpp \
    control/DataBase.cpp \
    control/modbus/vserialport.cpp \
    control/modbus/vmodbusclient.cpp \
    control/modbus/vmodbus.cpp \
    control/vserialtoserial.cpp \
    widgets/systemparaface.cpp \
    widgets/submenu.cpp \
    widgets/setparadialog.cpp \
    widgets/runparasetface.cpp \
    widgets/runinfoface.cpp \
    widgets/rltimdttable.cpp \
    widgets/returnfactory.cpp \
    widgets/remotelocal.cpp \
    widgets/powerface.cpp \
    widgets/paratablewidget.cpp \
    widgets/paramsetface.cpp \
    widgets/msgbox.cpp \
    widgets/mainface.cpp \
    widgets/language.cpp \
    widgets/keyboard.cpp \
    widgets/invertercontroller.cpp \
    widgets/historyinfoface.cpp \
    widgets/historyfault.cpp \
    widgets/historydata.cpp \
    widgets/functiontable.cpp \
    widgets/faultled.cpp \
    widgets/faultdialog.cpp \
    widgets/electricitychart.cpp \
    widgets/communiset.cpp \
    widgets/columchart.cpp \
    widgets/clocksetface.cpp \
    widgets/clock.cpp \
    widgets/chart.cpp \
    paramodel.cpp \
    faulttextlist.cpp \
    faultqueue.cpp \
    minputcontext.cpp \
    control/modbus/vmcsocket.cpp \
    control/modbus/vmcserial.cpp \
    control/modbus/vmbserial.cpp \
    control/modbus/vmodbusmaster.cpp

HEADERS  += \
    invertercontroller.h \
    keyboard.h \
    mainface.h \
    minputcontext.h \
    powerface.h \
    runinfoface.h \
    submenu.h \
    functiontable.h \
    clock.h \
    chart.h \
    common.h \
    historyinfoface.h \
    paramsetface.h \
    historydata.h \
    operafile.h \
    runparasetface.h \
    setparadialog.h \
    paratablewidget.h \
    faultdialog.h \
    historyfault.h \
    clocksetface.h \
    systemparaface.h \
    userfile.h \
    rltimdttable.h \
    msgbox.h \
    paramodel.h \
    paralist.h \
    language.h \
    communiset.h \
    faultqueue.h \
    faultled.h \
    electricitychart.h \
    columchart.h \
    returnfactory.h \
    remotelocal.h \
    faulttextlist.h \
    control/vtcptoserial.h \
    control/mcontroller.h \
    control/DataBase.h \
    control/modbus/vserialport.h \
    control/modbus/vmodbusclient.h \
    control/modbus/vmodbus.h \
    control/vserialtoserial.h \
    widgets/systemparaface.h \
    widgets/submenu.h \
    widgets/setparadialog.h \
    widgets/runparasetface.h \
    widgets/runinfoface.h \
    widgets/rltimdttable.h \
    widgets/returnfactory.h \
    widgets/remotelocal.h \
    widgets/powerface.h \
    widgets/paratablewidget.h \
    widgets/paramsetface.h \
    widgets/msgbox.h \
    widgets/mainface.h \
    widgets/language.h \
    widgets/keyboard.h \
    widgets/invertercontroller.h \
    widgets/historyinfoface.h \
    widgets/historyfault.h \
    widgets/historydata.h \
    widgets/functiontable.h \
    widgets/faultled.h \
    widgets/faultdialog.h \
    widgets/electricitychart.h \
    widgets/communiset.h \
    widgets/columchart.h \
    widgets/clocksetface.h \
    widgets/clock.h \
    widgets/chart.h \
    control/modbus/vmcsocket.h \
    control/modbus/vmcserial.h \
    control/modbus/vmbserial.h \
    control/modbus/vmodbusmaster.h

FORMS    += \
    invertercontroller.ui \
    keyboard.ui \
    mainface.ui \
    submenu.ui \
    clock.ui \
    chart.ui \
    setparadialog.ui \
    clocksetface.ui \
    historydata.ui \
    rltimdttable.ui \
    msgbox.ui \
    powerface.ui \
    functiontable.ui \
    historyinfo.ui \
    password.ui \
    paraset.ui \
    systempara.ui \
    runinfo.ui \
    faultdialog.ui \
    language.ui \
    communiset.ui \
    faultled.ui \
    electricitychart.ui \
    columchart.ui \
    runparaset.ui \
    historyfault.ui \
    returnfactory.ui \
    remotelocal.ui

RESOURCES += \
    InverterController.qrc
