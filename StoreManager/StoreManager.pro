#-------------------------------------------------
#
# Project created by QtCreator 2019-06-03T09:40:01
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StoreManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        auditorbuyertab.cpp \
        auditordialog.cpp \
        auditorsalestab.cpp \
        buyercalldialog.cpp \
        buyerdialog.cpp \
        buyerstatedialog.cpp \
        dbmodule.cpp \
        login.cpp \
        main.cpp \
        mainwindow.cpp \
        salesdialog.cpp \
        salesstatedialog.cpp

HEADERS += \
        auditorbuyertab.h \
        auditordialog.h \
        auditorsalestab.h \
        buyercalldialog.h \
        buyerdialog.h \
        buyerstatedialog.h \
        dbmodule.h \
        login.h \
        mainwindow.h \
        salesdialog.h \
        salesstatedialog.h \
        sqlhelps.h

FORMS += \
        auditorbuyertab.ui \
        auditordialog.ui \
        auditorsalestab.ui \
        buyercalldialog.ui \
        buyerdialog.ui \
        buyerstatedialog.ui \
        login.ui \
        mainwindow.ui \
        salesdialog.ui \
        salesstatedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
