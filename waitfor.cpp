#include "waitfor.h"
#include "ui_waitfor.h"

WaitFor::WaitFor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitFor)
{
    ui->setupUi(this);
}

WaitFor::~WaitFor()
{
    delete ui;
}

void WaitFor::on_addnew_waitfor_clicked()
{
    add_waitFor = new New_WaitFor();
    add_waitFor->show();
}
