#include "writtennote.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <dbhandler.h>
#include <subject.h>

WrittenNote::WrittenNote()
{

}
WrittenNote::WrittenNote(QString text, QList<QString> tags, QList<Attachement> attachements, QDateTime timestamp)
{
    this->text = text;
    this->timestamp = timestamp;
    this->tags = tags;
    this->attachements = attachements;
}

int id;
void WrittenNote::saveWrittenNote(subject ASubject)
{
    subject temp = dbh.queryWithReturnSubjectList("select * from schoolSubject where name = " + ASubject.getName() + ")")[0];
    dbh.updateWrittenNote(this, temp.getId());
}


void WrittenNote::setDBH(DBHandler db_handler)
{
    dbh = db_handler;
}

QString WrittenNote::getContent() const
{
    return this->text;
}

QDateTime WrittenNote::getTimestamp() const
{
    return this->timestamp;
}

QList<QString> WrittenNote::getTags() const
{
    return this->tags;
}

QList<Attachement> WrittenNote::getAttachement() const
{
    return this -> attachements;
}

void WrittenNote::addAttachement(Attachement a)
{
    this->attachements.append(a);
}

void WrittenNote::setDate(QDateTime time)
{
    this->timestamp = time;
}


void WrittenNote::addTag(QString newTag)
{
    this->tags.append(newTag);
}
