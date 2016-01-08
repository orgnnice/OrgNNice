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

void MainWindow::openSubject()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->setSubDet(sel);
    detSubject->show();
}

void MainWindow::setSubList(QList<Subject> list)
{
    this->sublist = list;
    int a = 2;
    int line = 0;
    int pos = 0;
    qDebug() << "Subjectname: " << sublist[0].getName();
    qDebug() << "Anzahl der Mitschriften:" << sublist[0].getWrittenNotesSize();
    for(int i=0;i<sublist.length();i++){        
        qDebug() << "Subjectname: " << sublist[i].getName();
        qDebug() << "Anzahl der Mitschriften:" << sublist[i].getWrittenNotesSize();

        QFont font1;
        font1.setPointSize(14);
        QFont font2;
        font2.setPointSize(50);

        QPushButton *pButton = new QPushButton("Anzeigen");
        QGroupBox *groupbox = new QGroupBox(sublist[i].getName());
        groupbox->setFont(font1);
        QLabel *anzahlnotes = new QLabel(QString::number(sublist[i].getWrittenNotesSize()));
        anzahlnotes->setAlignment(Qt::AlignCenter);
        anzahlnotes->setFont(font2);
        QLabel *desc = new QLabel("Mitschriften");
        desc->setAlignment(Qt::AlignCenter);
        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(anzahlnotes);
        verticalLayout->addWidget(desc);
        verticalLayout->addWidget(pButton);
        groupbox->setLayout(verticalLayout);        
        if(i > a){
            a *= 2;
            line++;
            pos = 0;
        }
        ui->gridLayout->addWidget(groupbox,line,pos,1,1);
        pos++;
        connect(pButton, SIGNAL (clicked()), this, SLOT (openSubject()));

    }
}

void MainWindow::openNewWindow()
{
    newCre = new c_subject(); // Be sure to destroy you window somewhere
    newCre->show();
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
