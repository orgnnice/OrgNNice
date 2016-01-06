#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
    detsub= new QPushButton("Subject Detail", this);
    detsub->setGeometry(QRect(QPoint(250, 50),
        QSize(100, 50)));
    connect(detsub, SIGNAL (clicked()), this, SLOT (openSubject()));
    addnew= new QPushButton("New Subject", this);
    addnew->setGeometry(QRect(QPoint(350, 50),
        QSize(100, 50)));
    connect(addnew, SIGNAL (clicked()), this, SLOT (openNewWindow()));
    writn= new QPushButton("Text Edit", this);
    writn->setGeometry(QRect(QPoint(450, 50),
        QSize(100, 50)));
    connect(writn, SIGNAL (clicked()), this, SLOT (openRTE()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewWindow()
{
    newCre = new c_subject(); // Be sure to destroy you window somewhere
    newCre->show();
}
void MainWindow::openSubject()
{
    detSubject = new Subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}
void MainWindow::openRTE()
{
    QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(dialog); // Be sure to destroy you window somewhere
    rte->show();
}
