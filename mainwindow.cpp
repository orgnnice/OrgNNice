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
        QSignalMapper* deleteMapper = new QSignalMapper(this);
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
        QPushButton *deleteButton = new QPushButton("");
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        QPixmap pixmap = QPixmap (":/images/icons/icon_x.png");
        deleteButton->setIcon(QIcon(pixmap));
        deleteButton->setIconSize(QSize(15, 15));
        deleteButton->setStyleSheet("#deleteButton{background-color: #fff; border: 0px; border-radius: 2px;}"
                                                  "#deleteButton:hover{color: #F22613; border: 1px solid #830000;}");
        deleteButton->setFont(font3);
        deleteButton->setMinimumSize(QSize(20, 20));
        deleteButton->setMaximumSize(QSize(20, 20));

        QVBoxLayout *verticalLayout = new QVBoxLayout;        
        verticalLayout->addWidget(deleteButton, 0, Qt::AlignRight);
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

        connect(deleteButton, SIGNAL(clicked()), deleteMapper, SLOT(map()));
        deleteMapper->setMapping(deleteButton, i);
        connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(deleteSubject(int)));
    }
}

void MainWindow::subDetail(int index){
    qDebug() << index;
    detSubject = new subject_detail(this);
    detSubject->setSubDet(sublist[index]);
    detSubject->show();
}

void MainWindow::deleteSubject(int item){
    qDebug() << item;
    sublist[item].deleteSubject();
}

void MainWindow::on_pushButton_10_clicked()
{
    detSubject = new subject_detail(); // Be sure to destroy you window somewhere
    detSubject->show();
}

void MainWindow::on_addnew_clicked()
{
    newCre = new c_subject(this); // Be sure to destroy you window somewhere
    //newCre->parmain=this;
    newCre->show();
    //connect();
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
    toList = new toDo(this);
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
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::on_export_2_clicked()
{
    exportDia = new ExportDialog();
    exportDia->show();
}

void MainWindow::on_waitForbut_clicked()
{
    waitList = new WaitFor(this);
    waitList->setItemList(waitItems);
    waitList->show();

}

void MainWindow::on_addnew_2_clicked()
{
    newCre = new c_subject(this); // Be sure to destroy you window somewhere
    //newCre->parmain=this;
    newCre->show();
}

void MainWindow::update()
{
qDebug() << "Started Update";
QList<Subject> allsubs = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
this->setSubList(allsubs);
}


void MainWindow::updateLists()
{
qDebug() << "Started Update";
QList <WaitForList> allw =  pDBh->queryWithReturnWaitForListList("SELECT * FROM waitfor");
QList <ToDoItem> allt =  pDBh->queryWithReturnToDoItemList("SELECT * FROM todo");
this->waitItems = allw;
this->todoItems = allt;
}
