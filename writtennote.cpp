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
WrittenNote::WrittenNote(int id, QString text, QList<QString> attachements, QList<QString> tags, QDateTime timestamp)
{
    this->id = id;
    this->text = text;
    this->timestamp = timestamp;
    this->tags = tags;
    this->attachements = attachements;
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
    pDBh->insertWrittenNote(*this);
}


WrittenNote::WrittenNote(QString content, QDateTime ts, int subject_ID)
{
    this->text = content;
    this->timestamp = ts;
    this->subject_ID = subject_ID;
    pDBh->insertWrittenNote(*this);
}


void WrittenNote::deleteWrittenNote() {
    pDBh->queryNoReturn("delete * from WrittenNote where (pk_id = " + QString::number(this->getId()) + ")");
    pDBh->queryNoReturn("delete * from noteHasTag where (fk_note = " + QString::number(this->getId()) + ")");
    pDBh->queryNoReturn("delete * from noteHasAttachment where (fk_note = " + QString::number(this->getId()) + ")");
}

void WrittenNote::saveWrittenNote(Subject ASubject)
{
    pDBh->updateWrittenNote(*this);
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
    pDBh->updateWrittenNote(*this);
}

void WrittenNote::setDate(QDateTime time)
{
    this->timestamp = time;
}


void WrittenNote::addTag(QString newTag)
{
    qDebug() << "WrittenNote->addTag->" << newTag;
    this->tags.append(newTag);
    pDBh->updateWrittenNote(*this);
}

void WrittenNote::removeTag(QString tag)
{
    this->tags.removeAt(tags.indexOf(tag));
    pDBh->updateWrittenNote(*this);
}
