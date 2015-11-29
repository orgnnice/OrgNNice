#include "writtennote.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <dbhandler.h>
WrittenNote::WrittenNote()
{

}
WrittenNote::WrittenNote(QString text, QList<QString> tags, QList<Attachement> attachements, QDateTime timestamp, DBHandler dbh)
{
    this->text = text;
    this->timestamp = timestamp;
    this->tags = tags;
    this->attachements = attachements;
    this->dbh = dbh;
}

int id;
void WrittenNote::saveWrittenNote(QString text)
{
    this->text = text;
    this->timestamp = QDateTime::currentDateTime();
    dbh.insertWrittenNote(this);

}




QDateTime WrittenNote::getTimestamp() const
{
    return this->timestamp;
}

QList<QString> WrittenNote::getTags() const
{
    return this->tags;
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
