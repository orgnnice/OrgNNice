#include "writtennote.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <dbhandler.h>
#include <subject.h>
#include "main.h"

int WrittenNote::getSubject_ID() const
{
    return subject_ID;
}

void WrittenNote::setSubject_ID(int value)
{
    subject_ID = value;
}

WrittenNote::WrittenNote()
{

}

/**
 * @brief WrittenNote::WrittenNote
 * @param id
 * @param text
 * @param attachements
 * @param tags
 * @param timestamp
 *
 * To be called after selecting fron database.
 *
 */
WrittenNote::WrittenNote(int id, QString text, QList<QString> attachements, QList<QString> tags, QDateTime timestamp, int subject_ID)
{
    this->id = id;
    this->text = text;
    this->timestamp = timestamp;
    this->tags = tags;
    this->attachements = attachements;
    this->subject_ID = subject_ID;
}


/**
 * @brief WrittenNote::WrittenNote
 *
 * inserts the note.
 *
 */

WrittenNote::WrittenNote(QString content, QDateTime ts, QString subject_name)
{
    this->text = content;
    this->timestamp = ts;
    this->subject_ID = pDBh->select("pk_id", "SchoolSubject", "name='" + subject_name + "'").replace('"', "").toInt();
    qDebug() << "subject_id of " << subject_name << "is" << pDBh->select("pk_id", "SchoolSubject", "name='" + subject_name + "'");
    this->id = pDBh->insertWrittenNote(*this);
}






WrittenNote::WrittenNote(QString content, QDateTime ts, int subject_ID)
{
    this->text = content;
    this->timestamp = ts;
    this->subject_ID = subject_ID;
    this->id = pDBh->insertWrittenNote(*this);
}

void WrittenNote::setContent(QString text){
    this->text = text;

    //change content of Note in Database

    pDBh->queryNoReturn("UPDATE note SET content = '" + text + "' WHERE (pk_id = " + QString::number(this->id) +")");


}



QString WrittenNote::toString()
{
    QString retrunString = "ID: " + QString::number(getId()) + "; content: " + getContent() + "; sunbject-ID:" + QString::number(getSubject_ID()) + "; Timestamp" +  getTimestamp().toString();

    QList<QString> tags = getTags();
    QList<QString> attachements = getAttachement();
    retrunString += "; Tags:";
    for (QString t: tags)
    {
       retrunString += " " + t ;
    }
    retrunString += "; Attatchements:";

    for (QString a: attachements)
    {
       retrunString +=  " " + a;
    }
    return  retrunString + ";";
}

void WrittenNote::deleteWrittenNote() {
    pDBh->deleteWrittenNote(this->getId());
}

void WrittenNote::saveWrittenNote()
{
    pDBh->updateWrittenNote(*this);
}

int WrittenNote::getId()
{
    return this->id;
}

void WrittenNote::setNoteID(int noteId)
{
    this->id = noteId;
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

void WrittenNote::addAttachement(QString attachement)
{
    this->attachements.append(attachement);
    pDBh->insertAttachementToNote(this->id, attachement);

}



void WrittenNote::addTag(QString newTag)
{
    qDebug() << "WrittenNote->addTag->" << QString::number(getId()) <<   " tag: " << newTag;
    this->tags.append(newTag);
    //<todo>
    //messes up everything ->
    pDBh->insertWrittenTagToNote(this->id, newTag);
}


void WrittenNote::setDate(QDateTime time)
{
    this->timestamp = time;
}


void WrittenNote::removeTag(QString tag)
{
    this->tags.removeAt(tags.indexOf(tag));
    pDBh->updateWrittenNote(*this);
}

void WrittenNote::removeAttachement(QString)
{

}
