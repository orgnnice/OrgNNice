#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonBox_accepted()
{
    if(ui->radioButton_2->isChecked()){
    QList<QString> with;
    QList<QString> without;
    with << ui->lineEdit->text();
    without << ui->lineEdit_2->text();
    qDebug() << "With: " << with;
    qDebug() << "WithOut: " << without;
    QList<WrittenNote> result= selsub.getWrittenNotesWithWithout(with, without);
    qDebug() << "Search WrittenNote-ID: " << result[0].getTags();
    out = new SearchResult();
    out->setResult(result, "Hat Tags: Ohne Tags: ");
    out->show();
    }else if(ui->radioButton->isChecked()){
        qDebug() << "From: " << ui->dateTimeEdit->dateTime();
        qDebug() << "To: " << ui->dateTimeEdit_2->dateTime();
        QList<WrittenNote> result= selsub.getWrittenNotesBetween(ui->dateTimeEdit->dateTime(), ui->dateTimeEdit_2->dateTime());
        qDebug() << "Search WrittenNote-ID: " << result.length();
    }
}
