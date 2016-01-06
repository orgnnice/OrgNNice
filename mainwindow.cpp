#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
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
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}
void MainWindow::openRTE()
{
    QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(dialog); // Be sure to destroy you window somewhere
    rte->show();
}

void MainWindow::on_pushButton_10_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}

void MainWindow::on_addnew_clicked()
{
    newCre = new c_subject(); // Be sure to destroy you window somewhere
    newCre->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}

void MainWindow::on_pushButton_8_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}
