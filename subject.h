#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include <QMap>
#include <QDateTime>
#include <writtennote.h>
#include <QList>

class subject
{
    QMap <QDateTime, WrittenNote> notes;
    QString subject_name;
    QString subject_teacher;
    QList frequentlyUsedTags;


public:
    subject();

    QString getName();
    QString getTeacher();
    QList getFrequentlyUsedTags();
    int getWrittenNotesSize();
    QList getWrittenNotes();
    QList getWrittenNotes(Date);
    QList getWrittenNotes(tag);
    QList getWrittenNotes(taglist);
    QList getWrittenNotesBetween(Date, Date);
    QList getWrittenNotesWithWithout(tagList, tagList);
    void addWrittenNote(WrittenNote);
};



#endif // SUBJECT_H
