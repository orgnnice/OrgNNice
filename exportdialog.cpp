#include "exportdialog.h"
#include "ui_exportdialog.h"
#include "subject.h"
#include "dbhandler.h"
#include "main.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");

    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");

    for(int i = 0; i < allsubjects.length(); i++)
    {
        ui->comboBox->addItem(allsubjects[i].getName());
    }
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::on_buttonBox_rejected()
{
    this->close();
}

void ExportDialog::on_buttonBox_accepted()
{
    if (ui->radioButton->isChecked()) {
       eport = new ExportImport(QDir::homePath());
       eport->exportDatabase(ui->radioButton->isChecked(),ui->checkBox->isChecked(),ui->checkBox_3->isChecked(),ui->checkBox_2->isChecked(),"");
    }else if(ui->radioButton_2->isChecked()) {
       eport = new ExportImport(QDir::homePath());
       eport->exportDatabase(ui->radioButton->isChecked(),ui->checkBox->isChecked(),ui->checkBox_3->isChecked(),ui->checkBox_2->isChecked(),ui->comboBox->currentText());
    }

    //(bool all, bool todo, bool notes, bool waitFor, QString subject)

    qDebug() << ui->radioButton->isChecked();
    qDebug() << ui->checkBox->isChecked();
    qDebug() << ui->checkBox_2->isChecked();
    qDebug() << ui->comboBox->currentText();
    this->close();
}

void ExportDialog::on_radioButton_2_toggled(bool checked)
{
    ui->comboBox->setEnabled(true);
}

void ExportDialog::on_radioButton_toggled(bool checked)
{
    ui->comboBox->setEnabled(false);
}
