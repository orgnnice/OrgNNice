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
    QString selectCall = "select * from note where (fk_schoolSubject = (select pk_id from schoolSubject where (name = " + this->getName(); + " AND pk_id = (select nodeId from noteHasTag where (TagId in(select pk_id from tag where (tagname in (";

    for (int i = 0; i < taglist.length(); i++)
    {
        if(i - 1 < taglist.length())
        {
            selectCall += taglist[i] + ", ";
        } else {
             selectCall += taglist[i]  + "))))))))";
        }
    }
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
    QString selectCall = "select * from note where (fk_schoolSubject = (select pk_id from schoolSubject where (name = " + this->getName() + " AND pk_id = (select nodeId from noteHasTag where (TagId in (select pk_id from tag where (tagname in (";

    for (int i = 0; i < tagListWith.length(); i++)
    {
        if(i - 1 < tagListWith.length())
        {
            selectCall += tagListWith[i] + ", ";
        } else {
             selectCall += tagListWith[i]  + ")) AND tagname NOT IN (";
        }
    }

    for (int i = 0; i < tagListWithout.length(); i++)
    {
        if(i - 1 < tagListWithout.length())
        {
            selectCall += tagListWithout[i] + ", ";
        } else {
             selectCall += tagListWithout[i] + ")))))))";
        }
    }
    pDBh->queryWithReturnNoteList(selectCall);
    return chosenNotes;
}

void Subject::addWrittenNote(WrittenNote note)
{
    notes.append(note);
}


void Subject::deleteSubject()
{
    pDBh->deleteSubject(this->getId());
}

void Subject::updateSubject()
{
    pDBh->queryNoReturn("update schoolSubject set name = " + this->getName() +"where (pk_id = " + QString::number(this->getId()) + ")");
}
