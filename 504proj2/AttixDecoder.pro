#-------------------------------------------------
#
# Project created by QtCreator 2018-12-18T17:07:09
#
#-------------------------------------------------

QT       += core gui\
            network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG      += c++11
INCLUDEPATH +=  $$PWD/include

DEFINES += ASIO_STANDALONE
DEFINES += CSV_IO_NO_THREAD

Release:DESTDIR = ../build/release/
Release:OBJECTS_DIR = ../build/release/.obj
Release:MOC_DIR = ../build/release/.moc
Release:RCC_DIR = ../build/release/.rcc
Release:UI_DIR = ../build/release/.ui

Debug:DESTDIR = ../build/debug/
Debug:OBJECTS_DIR = ../build/debug/.obj
Debug:MOC_DIR = ../build/debug/.moc
Debug:RCC_DIR = ../build/debug/.rcc
Debug:UI_DIR = ../build/debug/.ui

LIBS        += -lws2_32

TARGET = AttixDecoder
TEMPLATE = app
RC_ICONS = Rocket.ico


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(ui/ui.pri)
include(network/network.pri)


SOURCES += \
	main.cpp \
    utils.cpp \
    configmodel.cpp \
    frameparserwithmodules.cpp

HEADERS += \
    frameparser_interface.h \
    module_interface.h \
    utils.h \
    cirqueue.h \
    configmodel.h \
    frameparserwithmodules.h \
	interfaces.h
