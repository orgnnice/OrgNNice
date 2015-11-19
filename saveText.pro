#-------------------------------------------------
#
# Project created by QtCreator 2015-10-11T09:58:21
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = saveText
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    writtennote.cpp \
    subject.cpp \
    attachement.cpp

HEADERS  += \
    writtennote.h \
    subject.h \
    attachement.h

FORMS    += \
    editor.ui
