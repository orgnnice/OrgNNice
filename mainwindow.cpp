#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <subject.h>
#include <dbhandler.h>
#include <QGroupBox>

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

void MainWindow::setSubList(QList<Subject> list)
{
    this->sublist = list;
    qDebug() << "Subjectname: " << sublist[0].getName();
    qDebug() << "Anzahl der Mitschriften:" << sublist[0].getWrittenNotesSize();
    for(int i=0;i<sublist.length();i++){
        qDebug() << "Subjectname: " << sublist[i].getName();
        qDebug() << "Anzahl der Mitschriften:" << sublist[i].getWrittenNotesSize();
        QGroupBox *groupbox = new QGroupBox(sublist[i].getName());
        QLabel *anzahlnotes = new QLabel(QString::number(sublist[i].getWrittenNotesSize()));
        QLabel *desc = new QLabel("Mitschriften");
        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(anzahlnotes);
        verticalLayout->addWidget(desc);
        groupbox->setLayout(verticalLayout);
        ui->gridLayout->addWidget(groupbox);

    }
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
