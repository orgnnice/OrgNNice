#include "writtennote.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <dbhandler.h>
#include <subject.h>
#include "main.h"

WrittenNote::WrittenNote()
{

}
WrittenNote::WrittenNote(int id, QString text, QList<QString> attachements, QList<QString> tags, QDateTime timestamp)
{
    this->id = id;
    this->text = text;
    this->timestamp = timestamp;
    this->tags = tags;
    this->attachements = attachements;
}

int id;
void WrittenNote::saveWrittenNote(Subject ASubject)
{
    WrittenNote note = *this;
    Subject temp = pDBh->queryWithReturnSubjectList("select * from schoolSubject where name = " + ASubject.getName() + ")")[0];
    pDBh->updateWrittenNote(note, temp.getId());
}

int WrittenNote::getId()
{
    return this->id;
}

QString WrittenNote::getContent()
{
    return this->text;
}

QDateTime WrittenNote::getTimestamp()
{
    return this->timestamp;
}

QList<QString> WrittenNote::getTags()
{
    return this->tags;
}

QList<QString> WrittenNote::getAttachement()
{
    return this -> attachements;
}

void WrittenNote::addAttachement(QString a)
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
