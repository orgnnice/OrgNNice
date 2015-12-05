#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include <QMap>
#include <QDateTime>
#include <writtennote.h>
#include <QList>

class DBHandler;

class subject
{

    static DBHandler dbh;
private:
    int id;
    QList <WrittenNote> notes;
    QString subject_name;

public:
    subject();
    subject(QString name, QList <WrittenNote> notes);

    static void setDBH(DBHandler db_handler);
    QString getName();
    int getId();
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
