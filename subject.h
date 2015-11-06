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

    QString getName();
    QString getTeacher();
    QList<QString> getFrequentlyUsedTags();
    int getWrittenNotesSize();
    QMap <QDateTime, WrittenNote> getWrittenNotes();
    QList<WrittenNote> getWrittenNotes(QDateTime Date);
    QList<WrittenNote> getWrittenNotes(QString tag);
    QList<WrittenNote> getWrittenNotes(QList<QString> taglist);
    QList<WrittenNote> getWrittenNotesBetween(QDateTime DateFrom, QDateTime DateTo);
    QList<WrittenNote> getWrittenNotesWithWithout(QList<QString> tagListWith,QList<QString> tagListWithout);
    void addWrittenNote(WrittenNote);
};



#endif // SUBJECT_H
