QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcategory.cpp \
    addmoney.cpp \
    budgetmanager.cpp \
    expenseentrydialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    addcategory.h \
    addmoney.h \
    budgetmanager.h \
    expenseentrydialog.h \
    mainwindow.h

FORMS += \
    addcategory.ui \
    addmoney.ui \
    expenseentrydialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/add.png \
    img/minus.png
