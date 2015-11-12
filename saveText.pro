#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T09:58:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = saveText
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        savetext.cpp \
    writtennote.cpp \
    subject.cpp \
    attachement.cpp

HEADERS  += savetext.h \
    writtennote.h \
    subject.h \
    attachement.h

FORMS    +=
