#include "subject_detail.h"
#include "ui_subject_detail.h"

subject_detail::subject_detail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subject_detail)
{
    ui->setupUi(this);
    connect(pushButton_2, SIGNAL(click()), this, SLOT(openNote()));
    connect(pushButton_3, SIGNAL(click()), this, SLOT(openNote()));
    connect(pushButton_4, SIGNAL(click()), this, SLOT(openNote()));
    connect(pushButton_5, SIGNAL(click()), this, SLOT(openNote()));
    connect(pushButton_6, SIGNAL(click()), this, SLOT(openNote()));
    connect(pushButton_8, SIGNAL(click()), this, SLOT(openNote()));
}

subject_detail::~subject_detail()
{
    delete ui;
}

void subject_detail::openNote()
{
   newWindow = new MRichTextEdit(this); // Be sure to destroy you window somewhere
   newWindow->show();
}
