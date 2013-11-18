#-------------------------------------------------
#
# Project created by QtCreator 2013-08-15T11:00:57
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InverterController
TEMPLATE = app


SOURCES += main.cpp\
    invertercontroller.cpp \
    keyboard.cpp \
    mainface.cpp \
    mcontroller.cpp \
    minputcontext.cpp \
    runinfoface.cpp \
    submenu.cpp \
    toolbar.cpp \
    functiontable.cpp \
    DataBase.cpp \
    clock.cpp \
    chart.cpp \
    serial/serialport.cpp \
    serial/mserialoperate.cpp \
    historyinfoface.cpp \
    paramsetface.cpp \
    powerface.cpp \
    historydata.cpp \
    operafile.cpp \
    runparasetface.cpp \
    setparadialog.cpp \
    parainfo.cpp \
    paratablewidget.cpp \
    faultdialog.cpp \
    historyfault.cpp \
    clocksetface.cpp \
    systemparaface.cpp \
    userfile.cpp

HEADERS  += \
    invertercontroller.h \
    keyboard.h \
    mainface.h \
    mcontroller.h \
    minputcontext.h \
    powerface.h \
    runinfoface.h \
    submenu.h \
    toolbar.h \
    functiontable.h \
    DataBase.h \
    clock.h \
    chart.h \
    serial/serialport.h \
    serial/mserialoperate.h \
    common.h \
    historyinfoface.h \
    paramsetface.h \
    historydata.h \
    operafile.h \
    runparasetface.h \
    setparadialog.h \
    parainfo.h \
    paratablewidget.h \
    faultdialog.h \
    historyfault.h \
    clocksetface.h \
    systemparaface.h \
    userfile.h

FORMS    += \
    invertercontroller.ui \
    keyboard.ui \
    mainface.ui \
    submenu.ui \
    toolbar.ui \
    clock.ui \
    chart.ui \
    setparadialog.ui \
    clocksetface.ui \
    historydata.ui

RESOURCES += \
    InverterController.qrc