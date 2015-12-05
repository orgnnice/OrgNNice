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
    mrichtextedit.cpp \
    mtextedit.cpp \
    test.cpp \
    dbhandler.cpp

HEADERS  += \
    writtennote.h \
    subject.h \
    mrichtextedit.h \
    mtextedit.h \
    dbhandler.h \
    main.h

FORMS    += \
    editor.ui \
    mrichtextedit.ui

DISTFILES += \
    Defintions_info
