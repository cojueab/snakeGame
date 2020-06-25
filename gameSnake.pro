#-------------------------------------------------
#
# Project created by QtCreator 2015-12-26T17:49:02
#
#-------------------------------------------------

QT       += core gui testlib multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gameSnake
TEMPLATE = app


SOURCES += main.cpp\
        windowgame.cpp \
    testclass.cpp \
    item.cpp \
    snake.cpp \
    food.cpp \
    obstacle.cpp \
    portal.cpp \
    menu.cpp

HEADERS  += windowgame.h \
    testclass.h \
    item.h \
    point.h \
    snake.h \
    food.h \
    obstacle.h \
    portal.h \
    menu.h

RESOURCES += \
    images.qrc

FORMS += \
    menu.ui
