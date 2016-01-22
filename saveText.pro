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
    c_subject.cpp \
    todoitem.cpp \
    waitforlist.cpp \
    exportimport.cpp \
    todo.cpp \
    new_todo.cpp

HEADERS  += \
    writtennote.h \
    subject.h \
    mrichtextedit.h \
    mtextedit.h \
    dbhandler.h \
    main.h \
    mainwindow.h \
    subject_detail.h \
    c_subject.h \
    todoitem.h \
    ui_mainwindow.h \
    ui_c_subject.h \
    ui_subject_detail.h \
    waitforlist.h \
    exportimport.h \
    todo.h \
    new_todo.h

FORMS    += \
    mrichtextedit.ui \
    mainwindow.ui \
    subject_detail.ui \
    c_subject.ui \
    todo.ui \
    new_todo.ui

DISTFILES += \
    Defintions_info
