#include "new_todo.h"
#include "ui_new_todo.h"
#include <new_todo.h>

new_toDo::new_toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_toDo)
{
    ui->setupUi(this);
}

new_toDo::~new_toDo()
{
    delete ui;
}

void new_toDo::on_buttonBox_accepted()
{
    //ToDoItem awsomeTodo = ToDoItem(ui->comboBox->accessibleName(),ui->textEdit->toPlainText(),ui->dateEdit->text(),false);
}