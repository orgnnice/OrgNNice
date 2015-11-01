#include "savetext.h"
#include "ui_savetext.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <writtennote.h>

saveText::saveText(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::saveText)
{
    ui->setupUi(this);
}

saveText::~saveText()
{
    delete ui;
}

void saveText::on_SaveButton_clicked()
{
    WrittenNote obj1;
    QString text = "text";
    obj1.saveWrittenNote(ui -> textEdit -> toPlainText());
}
