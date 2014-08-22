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
    connector.cpp \
    room_abstract.cpp \
    room_simple.cpp \
    corridor_simple.cpp \
    room_container.cpp \
    view_maze.cpp

HEADERS  += mainwindow.h \
    attachable.h \
    connector.h \
    room_abstract.h \
    room_simple.h \
    corridor_simple.h \
    room_container.h \
    view_maze.h

test {
    message(Test build)
    QT += testlib
    TARGET = UnitTests

    SOURCES -= main.cpp

    HEADERS += test/test_first.h

    SOURCES += test/test_first.cpp
    SOURCES += test/test_main.cpp
} else {
    message(Normal build)
}

FORMS    += mainwindow.ui

SUBDIRS += \
    MapGeneratorSrc.pro
