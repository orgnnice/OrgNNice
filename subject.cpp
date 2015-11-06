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

QList subject::getFrequentlyUsedTags()
{
   return this->frequentlyUsedTags;
}

int subject::getWrittenNotesSize()
{
   return this->notes.count();
}

QList subject::getWrittenNotes()
{
   return this->notes;
}

QList subject::getWrittenNotes(QDateTime date)
{
   QList ChosenNotes = new QList();
   for(auto n : this->notes.values())
   {
       if(n.timestamp - date <=  86400)
       {
           ChosenNotes.append(n);
       }
   }
   return ChosenNotes;
}

QList subject::getWrittenNotes(QString tag)
{
    QList ChosenNotes = new QList();
    for(auto n : this->notes.values())
    {
        if(n.tags.contains(tag))
        {
            ChosenNotes.append(n);
        }
    }
    return ChosenNotes;
}

QList subject::getWrittenNotes(QList taglist)
{

}

QList subject::getWrittenNotesBetween(QDateTime DateFirst,QDateTime  DateLast)
{
    QList ChosenNotes = new QList();
    for(auto n : this->notes.values())
    {
        if(DateFirst <= n.timestamp && DateLast >= n.timestamp)
        {
            ChosenNotes.append(n);
        }
    }
    return ChosenNotes;
}

QList subject::getWrittenNotesWithWithout(tagList, tagList)
{

}

void subject::addWrittenNote(WrittenNote wn)
{
    this->notes.insert(QDateTime::currentDateTime(), wn);
}

