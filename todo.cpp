#include "todo.h"
#include "ui_todo.h"

toDo::toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::toDo)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
}

toDo::~toDo()
{
    delete ui;
}
