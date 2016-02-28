#include "c_subject.h"
#include "ui_c_subject.h"
#include <subject.h>
#include <qdebug.h>
#include <QProcess>
#include <QMainWindow>
#include <mainwindow.h>

c_subject::c_subject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::c_subject)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
    //sparmain->hide();
}

c_subject::~c_subject()
{
    delete ui;
}

void c_subject::on_buttonBox_accepted()
{
    qDebug() << "hierr" << ui->subname->text();
    Subject awesomeNewSubject = Subject(ui->subname->text());
    qDebug() << "hierr" << ui->subname->text();
    MainWindow *parent1 = qobject_cast<MainWindow*>(parent());
    qDebug() << parent1;
    if (parent1)
            parent1->close();
    this->close();
}
