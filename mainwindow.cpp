#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <subject.h>
#include <exportdialog.h>
#include <dbhandler.h>
#include <QGroupBox>
#include <main.h>
#include <QFileDialog>
#include <exportimport.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");

    connect(ui->actionExport, SIGNAL(triggered(bool)),
            this, SLOT(on_export_2_clicked()));
    connect(ui->actionImport, SIGNAL(triggered(bool)),
            this, SLOT(on_import_2_clicked()));
    connect(ui->actionToDo_Liste, SIGNAL(triggered(bool)),
            this, SLOT(on_toDobut_clicked()));
    connect(ui->actionWaitFor_Liste, SIGNAL(triggered(bool)),
            this, SLOT(on_waitForbut_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
qDebug() << "Started Update";
}

void MainWindow::setSubList(QList<Subject> list)
{

    ui->addnew_2->setStyleSheet("#addnew_2{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#addnew_2:hover{color: #000; border: 1px solid #446CB3;}");
    ui->addnew_2->setMinimumSize(QSize(30, 30));
    ui->addnew_2->setMaximumSize(QSize(30, 30));

    this->sublist = list;
    int a = 2;
    int line = 0;
    int pos = 0;
    qDebug() << "Länge: " << sublist.length();
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
        QLabel *subjectName = new QLabel(sublist[i].getName());
        subjectName->setFont(font1);
        subjectName->setObjectName(QStringLiteral("subjectName"));
        subjectName->setStyleSheet("#subjectName{background-color: #fff; font-family: 'Yu Gothic UI Semibold';}");
        QPushButton *pButton = new QPushButton("Anzeigen");
        pButton->setStyleSheet("QPushButton{color: #23121C; background-color: #51C185; border: 1px solid #26A65B; font-family: 'Yu Gothic UI';}"
                                                  "QPushButton:hover{color: #000; border: 1px solid #446CB3;}");
        pButton->setFont(font3);
        pButton->setMinimumSize(QSize(100, 32));
        pButton->setMaximumSize(QSize(100, 32));
        QGroupBox *groupbox = new QGroupBox();
        groupbox->setObjectName(QStringLiteral("groupBox"));
        groupbox->setStyleSheet("#groupBox{background-color: #fff; border: 1px solid #aaa; border-radius: 2px;}");
        groupbox->setFont(font1);
        groupbox->setMinimumSize(QSize(200, 225));
        groupbox->setMaximumSize(QSize(200, 225));
        groupbox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        QLabel *anzahlnotes = new QLabel(QString::number(sublist[i].getWrittenNotesSize()));
        anzahlnotes->setObjectName(QStringLiteral("mitschriftAnzahl"));
        anzahlnotes->setStyleSheet("#mitschriftAnzahl{background-color: #fff; color: #51C185; font-family: 'Yu Gothic UI Semibold';}");
        anzahlnotes->setAlignment(Qt::AlignCenter);
        anzahlnotes->setFont(font2);
        QLabel *desc = new QLabel("Mitschriften");
        desc->setFont(font3);
        desc->setAlignment(Qt::AlignCenter);
        desc->setObjectName(QStringLiteral("mitschriftenLabel"));
        desc->setStyleSheet("#mitschriftenLabel{background-color: #fff; font-family: 'Yu Gothic UI';}");
        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(subjectName, 0, Qt::AlignCenter);
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

void MainWindow::subDetail(int index){
    qDebug() << index;
    detSubject = new subject_detail();
    detSubject->setSubDet(sublist[index]);
    detSubject->show();
}

void MainWindow::on_toDobut_clicked()
{
    toList = new toDo();
    toList->setItemList(todoItems);
    toList->show();
}

void MainWindow::on_import_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Database File"),QDir::homePath(), tr("Database Files (*.db *.db3)"));
    qDebug() << "Selected File: " << fileName;
    ExportImport(fileName).importDatabase();
    QApplication::quit();

}

void MainWindow::on_export_2_clicked()
{
    exportDia = new ExportDialog();
    exportDia->show();
}

void MainWindow::on_waitForbut_clicked()
{
    waitList = new WaitFor();
    waitList->setItemList(waitItems);
    waitList->show();

}

void MainWindow::on_addnew_2_clicked()
{
    newCre = new c_subject(); // Be sure to destroy you window somewhere
    //newCre->parmain=this;
    newCre->show();
}
