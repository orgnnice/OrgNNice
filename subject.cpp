#include "subject.h"

subject::subject()
{

}

QString subject::getName(subject theSubject)
{
   return theSubject.subject_name;
}

QString subject::getTeacher(subject theSubject)
{
   return theSubject.subject_teacher;
}

QList<QString> subject::getFrequentlyUsedTags(subject theSubject)
{
   return theSubject.frequentlyUsedTags;
}

int subject::getWrittenNotesSize(subject theSubject)
{
   return theSubject.notes.count();
}

QMap<QDateTime, WrittenNote> subject::getWrittenNotes(subject theSubject)
{
   return theSubject.notes;
}

QList<WrittenNote> subject::getWrittenNotes(subject theSubject, QDateTime date)
{
   QList<WrittenNote> chosenNotes;
   for(WrittenNote n : theSubject.notes.values())
   {
       if((n.getTimestamp().msecsTo(date))*1000 <=  86400)
       {
           chosenNotes.append(n);
       }
   }
   return chosenNotes;
}

QList<WrittenNote> subject::getWrittenNotes(subject theSubject, QString tag)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : theSubject.notes.values())
    {
        if(n.getTags().contains(tag))
        {
            chosenNotes.append(n);
        }
    }
    return chosenNotes;
}

QList<WrittenNote> subject::getWrittenNotes(subject theSubject, QList<QString> taglist)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : theSubject.notes.values())
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

QList<WrittenNote> subject::getWrittenNotesBetween(subject theSubject, QDateTime DateFirst,QDateTime  DateLast)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : theSubject.notes.values())
    {
        if(DateFirst <= n.getTimestamp() && DateLast >= n.getTimestamp())
        {
            chosenNotes.append(n);
        }
    }
    return chosenNotes;
}

QList<WrittenNote> subject::getWrittenNotesWithWithout(subject theSubject, QList<QString> tagListWith,QList<QString> tagListWithout)
{
    QList<WrittenNote> chosenNotes;
    for(WrittenNote n : theSubject.notes.values())
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

void subject::addWrittenNote(subject theSubject, WrittenNote wn)
{
    theSubject.notes.insert(QDateTime::currentDateTime(), wn);
}
