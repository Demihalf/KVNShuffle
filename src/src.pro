#-------------------------------------------------
#
# Project created by QtCreator 2011-04-08T20:22:14
#
#-------------------------------------------------

QT       += core gui

CONFIG   += warn_on \
            qt

TARGET = ../bin/kvn-shuffle
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    buttonstablewidget.cpp \
    displaywidget.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    buttonstablewidget.h \
    displaywidget.h \
    settingsdialog.h \
    utilities.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

RC_FILE = kvn-shuffle.rc

MOC_DIR = ../tmp
OBJECTS_DIR = ../tmp
RCC_DIR = ../tmp

RESOURCES += \
    resources.qrc
