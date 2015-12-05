#include "subject.h"
#include <dbhandler.h>
Subject::Subject()
{




}


Subject::Subject(QString name, QList <WrittenNote> notes){
    this->subject_name = name;
    this->notes = notes;
}




QString Subject::getName()
{
   return subject_name;
}

QString Subject::getId()
{
   return id;
}

int Subject::getWrittenNotesSize()
{
   return notes.count();
}


void Subject::setDBH(DB_luki_Handler db_handler)
{
    dbh = db_handler;
}


QList<WrittenNote> Subject::getWrittenNotes()
{
   return notes;

}

QList<WrittenNote> Subject::getWrittenNotes(QDateTime date)
{
   QList<WrittenNote> chosenNotes;
   for(WrittenNote n : notes.values())
   {
       if((n.getTimestamp().msecsTo(date))*1000 <=  86400)
       {
           chosenNotes.append(n);
       }
   }
   //methode("select * from
   return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotes(QString tag)
{
    QList<WrittenNote> chosenNotes;

    QList<QString>::iterator i;
    for (i = notes.begin(); i != notes.end(); ++i)
    {
        chosenNotes.append(i);
    }
    return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotes(QList<QString> taglist)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : notes))
    {
        int amount = 0;
        for(QString tag : taglist)
        {
            if(n.getTags().contains(tag))
            {
                amount++;
            } else
            {
                break;
            }
        }
        if(amount == taglist.count())
        {
            chosenNotes.append(n);
        }
    }
    return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotesBetween(QDateTime DateFirst, QDateTime  DateLast)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : notes)
    {
        if(DateFirst <= n.getTimestamp() && DateLast >= n.getTimestamp())
        {
            chosenNotes.append(n);
        }
    }
    return chosenNotes;
}

QList<WrittenNote> Subject::getWrittenNotesWithWithout(QList<QString> tagListWith, QList<QString> tagListWithout)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : notes)
    {
        int amountWith = 0;
        int amountWithout = 0;
        for(QString tag : tagListWith)
        {
            if(n.getTags().contains(tag))
            {
                amountWith++;
            }
        }
        for(QString tag : tagListWithout)
        {
            if(n.getTags().contains(tag))
            {
                amountWithout++;
            }
        }
        if(amountWith == tagListWith.count() && amountWithout == tagListWithout.count())
        {
            chosenNotes.append(n);
        }
    }

    return chosenNotes;
}

void Subject::addWrittenNote(WrittenNote note)
{
    notes.append(note);
}
