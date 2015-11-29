#include "subject.h"

subject::subject()
{

}

QString subject::getName()
{
   return subject_name;
}

QString subject::getTeacher(subject theSubject)
{
   return theSubject.subject_teacher;
}


int subject::getWrittenNotesSize()
{
   return notes.count();
}

QList<WrittenNote> subject::getWrittenNotes()
{
   return notes;

}

QList<WrittenNote> subject::getWrittenNotes(QDateTime date)
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

QList<WrittenNote> subject::getWrittenNotes(QString tag)
{
    QList<WrittenNote> chosenNotes;

    QList<QString>::iterator i;
    for (i = notes.begin(); i != notes.end(); ++i)
    {
        chosenNotes.append(i);
    }
    return chosenNotes;
}

QList<WrittenNote> subject::getWrittenNotes(QList<QString> taglist)
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

QList<WrittenNote> subject::getWrittenNotesBetween(QDateTime DateFirst, QDateTime  DateLast)
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

QList<WrittenNote> subject::getWrittenNotesWithWithout(QList<QString> tagListWith, QList<QString> tagListWithout)
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

void subject::addWrittenNote(WrittenNote note)
{
    notes.append(note);
}
