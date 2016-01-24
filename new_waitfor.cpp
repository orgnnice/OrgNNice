#include "new_waitfor.h"
#include "ui_new_waitfor.h"
#include "dbhandler.h"
#include "main.h"
#include "subject.h"
#include "waitforlist.h"

New_WaitFor::New_WaitFor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_WaitFor)
{
    ui->setupUi(this);

    QList<Subject> allsubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");

    for(int i = 0; i < allsubjects.length(); i++)
    {
        ui->comboBox->addItem(allsubjects[i].getName());
    }
}

New_WaitFor::~New_WaitFor()
{
    delete ui;
}

void New_WaitFor::on_buttonBox_rejected()
{
    this->close();
}

void New_WaitFor::on_buttonBox_accepted()
{
    WaitForList newWait = WaitForList(ui->comboBox->itemText(ui->comboBox->currentIndex()),ui->textEdit->toPlainText(),false);
    qDebug() << ui->comboBox->itemText(ui->comboBox->currentIndex());
    qDebug() << ui->textEdit->toPlainText();
    this->close();
}
