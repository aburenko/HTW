#  Name: Burenko Anton
#  Matrikelnummer: 43733
#  Studiengruppe: 17/041/01
#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T01:20:09
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = beleg
TEMPLATE = app
QMAKE_CXXFLAGS = -std=c++11
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
    medium.cpp \
    book.cpp \
    cd.cpp \
    dvd.cpp \
    person.cpp \
    addnewperson.cpp \
    datamanager.cpp \
    addnewmedium.cpp \
    givemedium.cpp \
    changemedium.cpp \
    changeperson.cpp

HEADERS += \
        mainwindow.h \
    book.h \
    medium.h \
    cd.h \
    dvd.h \
    person.h \
    addnewperson.h \
    datamanager.h \
    book.h \
    addnewmedium.h \
    givemedium.h \
    changemedium.h \
    changeperson.h

FORMS += \
        mainwindow.ui \
    addnewperson.ui \
    addnewmedium.ui \
    givemedium.ui \
    changemedium.ui \
    changeperson.ui

RESOURCES +=
