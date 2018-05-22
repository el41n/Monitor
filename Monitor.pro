#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T08:55:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Monitor
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        hardware.cpp \
        cpu.cpp \
        architecture.cpp \
        architectureproxy.cpp \
        family6arch.cpp \
        bigclientcores.cpp \
        family5arch.cpp \
        family4arch.cpp \
        family11arch.cpp \
        family15arch.cpp \
        micarchitecture.cpp \
        littlecores.cpp \
        bigservercores.cpp \
        ram.cpp \
        qcustomplot.cpp


HEADERS += \
        mainwindow.h \
        hardware.h \
        cpu.h \
        architecture.h \
        architectureproxy.h \
        family6arch.h \
        bigclientcores.h \
        family5arch.h \
        family4arch.h \
        family11arch.h \
        family15arch.h \
        micarchitecture.h \
        littlecores.h \
        bigservercores.h \
        ram.h \
        qcustomplot.h





FORMS += \
        mainwindow.ui



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/R384-developer/x86/ -lnvapi

INCLUDEPATH += $$PWD/R384-developer
