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



void Subject::setSubjectName(QString name)
{
    if(this->subject_name != name)
    {
        this->subject_name = name;
        pDBh->queryNoReturn("UPDATE schoolSubject SET NAME = '" + name + "' WHERE (pk_id = " + QString::number(this->id) + ")");
    }
}


QList<WrittenNote> Subject::getWrittenNotes()
{
   return this->notes;
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
    qDebug() <<"Subject -->  getWrittenNotes(QList<QString> taglist)";
    QString selectCall = "select * from note where (fk_schoolSubject = " + QString::number(this->getId()) + " AND pk_id IN (select fk_note from noteHasTag where (fk_tag in (select pk_id from tag where (tagname IN (";

    for (int i = 0; i < taglist.length(); i++)
    {
        if(i + 1 < taglist.length())
        {
            selectCall += "'" + taglist[i] + "', ";
        } else {
             selectCall += "'" + taglist[i]  + "'))))))";
        }
    }
    qDebug() << "selectcall:" << selectCall;
    return pDBh->queryWithReturnNoteList(selectCall);
}

QList<WrittenNote> Subject::getWrittenNotesBetween(QDateTime DateFirst, QDateTime  DateLast)
{
    QList<WrittenNote> chosenNotes;

    for (WrittenNote wr : this->getWrittenNotes())
    {
        if(wr.getTimestamp().operator >(DateFirst) &&
           wr.getTimestamp().operator <(DateLast))
        {
            chosenNotes.append(wr);
        }
    }


    return chosenNotes;
}


QList<WrittenNote> Subject::getWrittenNotesWithWithout(QList<QString> tagListWith, QList<QString> tagListWithout)
{
    qDebug() <<"Subject -->  getWrittenNotesWithWithout";

    QString selectCall = "select * from note where (fk_schoolSubject = " + QString::number(this->getId()) + " AND pk_id IN (select fk_note from noteHasTag where (fk_tag in (select pk_id from tag where (tagname IN (";
    for (int i = 0; i < tagListWith.length(); i++)
    {
        if(i + 1 < tagListWith.length())
        {
            selectCall += "'" + tagListWith[i] + "', ";
        } else {
             selectCall += "'" + tagListWith[i]  + "'))))) AND pk_id NOT IN (select fk_note from noteHasTag where (fk_tag in (select pk_id from tag where (tagname IN (";
        }
    }


    for (int i = 0; i < tagListWithout.length(); i++)
    {
        if(i + 1 < tagListWithout.length())
        {
            selectCall += "'" + tagListWithout[i] + "', ";
        } else {
             selectCall += "'" + tagListWithout[i] + "'))))))";
        }
    }
    qDebug() << "select call: "  << selectCall;
    return pDBh->queryWithReturnNoteList(selectCall);
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
   Subject tempSubject = pDBh->subjectFromID(this->id);
   this->subject_name = tempSubject.subject_name;
   this->notes = tempSubject.notes;



}
