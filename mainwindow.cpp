#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
    pushButton = new QPushButton("My Button", this);
    pushButton->setGeometry(QRect(QPoint(100, 100),
        QSize(200, 50)));
    QObject::connect(pushButton, SIGNAL (clicked()), this, SLOT (openNewWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openNewWindow()
{
    this->hide();
    newCre = new c_subject(); // Be sure to destroy you window somewhere
    newCre->show();
}
/*void MainWindow::openSubject()
{
}*/
