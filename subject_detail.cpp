#include "subject_detail.h"
#include "ui_subject_detail.h"

subject_detail::subject_detail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subject_detail)
{
    ui->setupUi(this);
}

subject_detail::~subject_detail()
{
    delete ui;
}
