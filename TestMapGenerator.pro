#-------------------------------------------------
#
# Project created by QtCreator 2014-08-19T14:12:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestMapGenerator
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
        mainwindow.cpp \
    attachable.cpp \
    simpleroom.cpp \
    abstract_room.cpp \
    simplecorridor.cpp \
    qgraphicsviewcustom.cpp \
    container_room.cpp \
    connector.cpp

HEADERS  += mainwindow.h \
    attachable.h \
    simpleroom.h \
    abstract_room.h \
    simplecorridor.h \
    qgraphicsviewcustom.h \
    container_room.h \
    connector.h

FORMS    += mainwindow.ui
