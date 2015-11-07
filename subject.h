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
    QList<QString> frequentlyUsedTags;


public:
    subject();

    QString getName(subject theSubject);
    QString getTeacher(subject theSubject);
    QList<QString> getFrequentlyUsedTags(subject theSubject);
    int getWrittenNotesSize(subject theSubject);
    QMap <QDateTime, WrittenNote> getWrittenNotes(subject theSubject);
    QList<WrittenNote> getWrittenNotes(subject theSubject, QDateTime Date);
    QList<WrittenNote> getWrittenNotes(subject theSubject, QString tag);
    QList<WrittenNote> getWrittenNotes(subject theSubject, QList<QString> taglist);
    QList<WrittenNote> getWrittenNotesBetween(subject theSubject, QDateTime DateFrom, QDateTime DateTo);
    QList<WrittenNote> getWrittenNotesWithWithout(subject theSubject, QList<QString> tagListWith,QList<QString> tagListWithout);
    void addWrittenNote(subject theSubject, WrittenNote);
};



#endif // SUBJECT_H
