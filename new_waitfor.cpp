#include "new_waitfor.h"
#include "ui_new_waitfor.h"

New_WaitFor::New_WaitFor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_WaitFor)
{
    ui->setupUi(this);
}

New_WaitFor::~New_WaitFor()
{
    delete ui;
}

void New_WaitFor::on_buttonBox_rejected()
{
    this->close();
}
