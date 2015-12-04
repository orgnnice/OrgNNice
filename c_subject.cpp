#include "c_subject.h"
#include "ui_c_subject.h"

c_subject::c_subject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::c_subject)
{
    ui->setupUi(this);
}

c_subject::~c_subject()
{
    delete ui;
}
