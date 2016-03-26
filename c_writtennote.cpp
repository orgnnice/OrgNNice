#include "c_writtennote.h"
#include "ui_c_writtennote.h"
#include <writtennote.h>
#include <qdebug.h>
#include <subject.h>
#include <subject_detail.h>

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
    WrittenNote newNote = WrittenNote("Neue Mitschrift", QDateTime().currentDateTime(), crein.getId());
    newNote.addTag(ui->tags->text());
    crein.updateSubject();
    qDebug() << "Anzahl Mitschriften: " << crein.getWrittenNotesSize();
    this->close();
    subject_detail* parent = qobject_cast<subject_detail*>(this->parent());
    // check parent is not null
    parent->update(crein);
}

void  C_WrittenNote::setSubject(Subject cur)
{
    this->crein = cur;
}
