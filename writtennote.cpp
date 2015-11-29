#include "writtennote.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>

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
void WrittenNote::saveWrittenNote(QString text)
{
    this->text = text;
    this->timestamp = QDateTime::currentDateTime();

    QFile file ( this->path );
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );
        stream << text;
    }
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
