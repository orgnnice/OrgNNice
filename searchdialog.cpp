#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QDebug>
#include <QMessageBox>

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonBox_accepted()
{
    if(ui->radioButton_2->isChecked()){
    QList<QString> with = ui->lineEdit->text().replace( " ", "" ).split(",");
    QList<QString> without = ui->lineEdit_2->text().replace( " ", "" ).split(",");
    qDebug() << "With: " << with;
    qDebug() << "WithOut: " << without;
    QList<WrittenNote> result= selsub.getWrittenNotesWithWithout(with, without);
    if(result.length() > 0){
    qDebug() << "Search WrittenNote-ID: " << result[0].getTags();
    out = new SearchResult(this);
    out->setResult(result, "Hat Tags: " + with.join(", ")  + ", Ohne Tags: "+ without.join(", "));
    out->show();
    }else{
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Org'n'Nice");
        msgBox->setText("Für diese Suche konnte kein Ergebnis gefunden werden!");
        msgBox->exec();
    }
    }else if(ui->radioButton->isChecked()){
        qDebug() << "From: " << ui->dateTimeEdit->dateTime();
        qDebug() << "To: " << ui->dateTimeEdit_2->dateTime();
        QList<WrittenNote> result= selsub.getWrittenNotesBetween(ui->dateTimeEdit->dateTime(), ui->dateTimeEdit_2->dateTime());
        qDebug() << "Search WrittenNote-ID: " << result.length();
        out = new SearchResult(this);
        out->setResult(result, "Zeitraum von: " + ui->dateTimeEdit->dateTime().toString("dd.MM.yyyy") + ", bis: "+ ui->dateTimeEdit_2->dateTime().toString("dd.MM.yyyy"));
        out->show();
    }
}
