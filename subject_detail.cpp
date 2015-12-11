#include "subject_detail.h"
#include "ui_subject_detail.h"

Subject_detail::Subject_detail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Subject_detail)
{
    ui->setupUi(this);
}

Subject_detail::~Subject_detail()
{
    delete ui;
}
