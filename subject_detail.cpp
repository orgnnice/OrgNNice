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
    //QDialog *dialog = new QDialog();
    rte = new MRichTextEdit(this); // Be sure to destroy you window somewhere
    rte->show();
}
