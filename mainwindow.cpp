#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
    QObject::connect(pushButton, SIGNAL (clicked()), this, SLOT (quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::openNewWindow()
{

}
void MainWindow::openSubject()
{
}*/
