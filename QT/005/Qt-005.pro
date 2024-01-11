QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-005
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mydialog.cpp

HEADERS  += mainwindow.h \
    mydialog.h

FORMS    += mainwindow.ui \
    mydialog.ui
