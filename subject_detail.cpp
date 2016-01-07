#include "subject_detail.h"
#include "ui_subject_detail.h"

subject_detail::subject_detail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subject_detail)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
}

subject_detail::~subject_detail()
{
    delete ui;
}

void subject_detail::on_pushButton_2_clicked()
{
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->show();
}

void subject_detail::on_pushButton_6_clicked()
{
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->show();
}

void subject_detail::on_pushButton_4_clicked()
{
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->show();
}

void subject_detail::on_pushButton_3_clicked()
{
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->show();
}

void subject_detail::on_pushButton_5_clicked()
{
    /*MRichTextEdit *rte = new MRichTextEdit(this);
    QGridLayout *gl = new QGridLayout(this);
    this->addWidget(rte,0,0,1,1);
    this->setWindowTitle(QObject::tr("Org'N'Nice"));
    this->setMinimumWidth (400);
    this->setMinimumHeight(400);
    this->show();*/
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->show();
}
