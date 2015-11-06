#include "writtennote.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <attachement.h>


WrittenNote::WrittenNote()
{

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
