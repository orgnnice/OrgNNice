#include "new_todo.h"
#include "ui_new_todo.h"
#include <new_todo.h>
#include <QDebug>
#include "dbhandler.h"
#include "main.h"
#include "subject.h"
#include "todoitem.h"
#include "todo.h"
#include "qdebug.h"

new_toDo::new_toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_toDo)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    this->setWindowTitle("Org'n'Nice");

    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");

    for(int i = 0; i < allsubjects.length(); i++)
    {
        ui->comboBox->addItem(allsubjects[i].getName());
    }
}

new_toDo::~new_toDo()
{
    delete ui;
}

void new_toDo::setSubName(QString subname)
{
    int index = ui->comboBox->findText(subname);
    qDebug() << "Selektierter Index: " << index;
    ui->comboBox->setCurrentIndex(index);
}

void new_toDo::on_buttonBox_accepted()
{
    QDateTime date = ui->dateTimeEdit->dateTime();
    ToDoItem awsomeTodo = ToDoItem(ui->comboBox->itemText(ui->comboBox->currentIndex()),ui->textEdit->toPlainText(),date,false);
    qDebug() << ui->comboBox->itemText(ui->comboBox->currentIndex());
    qDebug() << ui->textEdit->toPlainText();
    qDebug() << ui->dateTimeEdit->dateTime();
    qDebug() << ui->dateTimeEdit->dateTime().toMSecsSinceEpoch();
    this->close();
    toDo* parent = qobject_cast<toDo*>(this->parent());
    // check parent is not null
    parent->update();
}

void new_toDo::on_buttonBox_rejected()
{
    this->close();
}
