#include "subject.h"
#include <dbhandler.h>
#include "main.h"

Subject::Subject()
{




}


Subject::Subject(int id, QList <WrittenNote> notes, QString name){
    this->id = id;
    this->subject_name = name;
    this->notes = notes;
}



/**
 * @brief Subject
 * @param name
 * insertes created Subject into database.
 * returns and saves id.
 */
Subject::Subject(QString name)
{
    this->subject_name = name;
    this->id = pDBh->insertSubject(name);
    this->notes = QList<WrittenNote>();
}




QString Subject::toString()
{
    return ("name: " + getName() + "; Id: " + QString::number(getId()));
}


QString Subject::getName()
{
   return subject_name;
}

int Subject::getId()
{
   return id;
}

int Subject::getWrittenNotesSize()
{
   return notes.count();
}


QList<WrittenNote> Subject::getWrittenNotes()
{
   return notes;

}

QList<WrittenNote> Subject::getWrittenNotes(QDateTime date)
{
   QList<WrittenNote> chosenNotes;

   //methode("select * from
   return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotes(QString tag)
{
    QList<WrittenNote> chosenNotes;
//methode("select * from
    return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotes(QList<QString> taglist)
{
    QList<WrittenNote> chosenNotes;
//methode("select * from
    return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotesBetween(QDateTime DateFirst, QDateTime  DateLast)
{
    QList<WrittenNote> chosenNotes;
//methode("select * from
    return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotesWithWithout(QList<QString> tagListWith, QList<QString> tagListWithout)
{
    QList<WrittenNote> chosenNotes;
//methode("select * from
    return chosenNotes;
}

void Subject::addWrittenNote(WrittenNote note)
{
    notes.append(note);
}

//Sill has to delete the objects out of note hastasg and note has Attachment
void Subject::deleteSubject()
{
    pDBh->queryNoReturn("delete * from schoolSubject where (pk_id = " + QString::number(this->getId()) + ")");
    pDBh->queryNoReturn("delete * from note where (fk_schoolSubject = " + QString::number(this->getId()) + ")");

}
void Subject::updateSubject()
{
    pDBh->queryNoReturn("update schoolSubject set name = " + this->getName() +"where (pk_id = " + QString::number(this->getId()) + ")");
}
