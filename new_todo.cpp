#include "new_todo.h"
#include "ui_new_todo.h"
#include <new_todo.h>
#include <QDebug>
#include "dbhandler.h"
#include "main.h"
#include "subject.h"
#include "todoitem.h"

new_toDo::new_toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_toDo)
{
    ui->setupUi(this);

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

void new_toDo::on_buttonBox_accepted()
{
    ToDoItem awsomeTodo = ToDoItem(ui->comboBox->itemText(ui->comboBox->currentIndex()),ui->textEdit->toPlainText(),ui->dateTimeEdit->dateTime(),false);
    qDebug() << ui->comboBox->itemText(ui->comboBox->currentIndex());
    qDebug() << ui->textEdit->toPlainText();
    qDebug() << ui->dateTimeEdit->dateTime();
    this->close();
}

void new_toDo::on_buttonBox_rejected()
{
    this->close();
}
