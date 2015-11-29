#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include <QMap>
#include <QDateTime>
#include <writtennote.h>
#include <QList>
#include <dbhandler.h>
class subject
{

private:
    QList <WrittenNote> notes;
    QString subject_name;
    DBHandler dbh;

public:
    subject();
    subject(QString name, DBHandler dbh);


    QString getName();
    int getWrittenNotesSize();
    QList<WrittenNote> getWrittenNotes();
    QList<WrittenNote> getWrittenNotes(QDateTime Date);
    QList<WrittenNote> getWrittenNotes(QString tag);
    QList<WrittenNote> getWrittenNotes(QList<QString> taglist);
    QList<WrittenNote> getWrittenNotesBetween(QDateTime DateFrom, QDateTime DateTo);
    QList<WrittenNote> getWrittenNotesWithWithout(QList<QString> tagListWith,QList<QString> tagListWithout);
    void addWrittenNote(WrittenNote note);


};



#endif // SUBJECT_H
