#include "c_writtennote.h"
#include "ui_c_writtennote.h"
#include <writtennote.h>
#include <qdebug.h>

C_WrittenNote::C_WrittenNote(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C_WrittenNote)
{
    ui->setupUi(this);
}

C_WrittenNote::~C_WrittenNote()
{
    delete ui;
}

void C_WrittenNote::on_buttonBox_rejected()
{
    this->close();
}

void C_WrittenNote::on_buttonBox_accepted()
{

}
