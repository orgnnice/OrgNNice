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
    dbhandler.cpp \
    mainwindow.cpp \
    subject_detail.cpp \
    c_subject.cpp

HEADERS  += \
    writtennote.h \
    subject.h \
    mrichtextedit.h \
    mtextedit.h \
    dbhandler.h \
    main.h \
    mainwindow.h \
    subject_detail.h \
    c_subject.h

FORMS    += \
    editor.ui \
    mrichtextedit.ui \
    mainwindow.ui \
    subject_detail.ui \
    c_subject.ui

DISTFILES += \
    Defintions_info
