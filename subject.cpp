#include "subject.h"

subject::subject()
{

}

QString subject::getName()
{
   return this->subject_name;
}

QString subject::getTeacher()
{
   return this->subject_teacher;
}

QList<QString> subject::getFrequentlyUsedTags()
{
   return this->frequentlyUsedTags;
}

int subject::getWrittenNotesSize()
{
   return this->notes.count();
}

QMap<QDateTime, WrittenNote> subject::getWrittenNotes()
{
   return this->notes;
}

QList<WrittenNote> subject::getWrittenNotes(QDateTime date)
{
   QList<WrittenNote> ChosenNotes;
   for(WrittenNote n : this->notes.values())
   {
       if((n.getTimestamp().msecsTo(date))*1000 <=  86400)
       {
           ChosenNotes.append(n);
       }
   }
   return ChosenNotes;
}

QList<WrittenNote> subject::getWrittenNotes(QString tag)
{
    QList<WrittenNote> ChosenNotes;
    for(WrittenNote n : this->notes.values())
    {
        if(n.getTags().contains(tag))
        {
            ChosenNotes.append(n);
        }
    }
    return ChosenNotes;
}

QList<WrittenNote> subject::getWrittenNotes(QList<QString> taglist)
{
    QList<WrittenNote> ChosenNotes;

    return ChosenNotes;
}

QList<WrittenNote> subject::getWrittenNotesBetween(QDateTime DateFirst,QDateTime  DateLast)
{
    QList<WrittenNote> ChosenNotes;
    for(WrittenNote n : this->notes.values())
    {
        if(DateFirst <= n.getTimestamp() && DateLast >= n.getTimestamp())
        {
            ChosenNotes.append(n);
        }
    }
    return ChosenNotes;
}

QList<WrittenNote> subject::getWrittenNotesWithWithout(QList<QString> tagListWith,QList<QString> tagListWithout)
{

}

void subject::addWrittenNote(WrittenNote wn)
{
    this->notes.insert(QDateTime::currentDateTime(), wn);
}

