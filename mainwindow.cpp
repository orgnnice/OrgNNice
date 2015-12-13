#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QFontDatabase>
#include <QInputDialog>
#include <QColorDialog>
#include <QTextList>
#include <QtDebug>
#include <QFileDialog>
#include <QImageReader>
#include <QSettings>
#include <QBuffer>
#include <QUrl>
#include <QPlainTextEdit>
#include <QMenu>
#include <QDialog>
#include <QToolButton>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(addnewsub, SIGNAL(click()), this, SLOT(openNewWindow()));
    /*connect(pushButton, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_2, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_3, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_4, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_5, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_6, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_7, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_8, SIGNAL(click()), this, SLOT(openSubject()));
    connect(pushButton_9, SIGNAL(click()), this, SLOT(openSubject()));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewWindow()
{
   newWindow = new c_subject(); // Be sure to destroy you window somewhere
   newWindow->show();
}

void MainWindow::openSubject()
{
   //selSub = new subject_detail(); // Be sure to destroy you window somewhere
   //selSub->show();
}

