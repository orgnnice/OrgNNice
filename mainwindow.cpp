#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "c_subject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_addnew->cSubDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}
