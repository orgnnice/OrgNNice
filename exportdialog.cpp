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
