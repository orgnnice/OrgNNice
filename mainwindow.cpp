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
    int a = 2;
    int line = 0;
    int pos = 0;
    selected = sublist[0];
    qDebug() << "Subjectname: " << sublist[0].getName();
    qDebug() << "Anzahl der Mitschriften:" << sublist[0].getWrittenNotesSize();
    for(int i=0;i<sublist.length();i++){        
        qDebug() << "Subjectname: " << sublist[i].getName();
        qDebug() << "Anzahl der Mitschriften:" << sublist[i].getWrittenNotesSize();

        QFont font1;
        font1.setPointSize(14);
        QFont font2;
        font2.setPointSize(50);
        QFont font3;
        font3.setPointSize(10);

        QSignalMapper* signalMapper = new QSignalMapper(this);
        QPushButton *pButton = new QPushButton("Anzeigen");
        pButton->setFont(font3);
        pButton->setMinimumSize(QSize(100, 32));
        pButton->setMaximumSize(QSize(100, 32));
        QGroupBox *groupbox = new QGroupBox(sublist[i].getName());
        groupbox->setFont(font1);
        groupbox->setMinimumSize(QSize(200, 225));
        groupbox->setMaximumSize(QSize(200, 225));
        groupbox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QLabel *anzahlnotes = new QLabel(QString::number(sublist[i].getWrittenNotesSize()));
        anzahlnotes->setAlignment(Qt::AlignCenter);
        anzahlnotes->setFont(font2);
        QLabel *desc = new QLabel("Mitschriften");
        desc->setFont(font3);
        desc->setAlignment(Qt::AlignCenter);
        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(anzahlnotes);
        verticalLayout->addWidget(desc);
        verticalLayout->addWidget(pButton, 0, Qt::AlignHCenter);
        groupbox->setLayout(verticalLayout);        
        if(i > a){
            a += 3;
            line++;
            pos = 0;
        }
        ui->gridLayout->addWidget(groupbox,line,pos,1,1);
        pos++;
        connect(pButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(pButton, i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(subDetail(int)));

    }
}

void MainWindow::openNewWindow()
{
    newCre = new c_subject(); // Be sure to destroy you window somewhere
    newCre->show();
}

void MainWindow::subDetail(int index){
    qDebug() << index;
    detSubject = new subject_detail();
    detSubject->setSubDet(sublist[index]);
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

void MainWindow::on_toDobut_clicked()
{
    toList = new toDo();
    toList->show();
}
