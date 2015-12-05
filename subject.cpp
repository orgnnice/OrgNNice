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
