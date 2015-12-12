#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include <QMap>
#include <QDateTime>
#include <writtennote.h>
#include <QList>

class DBHandler;

class Subject
{

    //static DBHandler dbh;
private:
    int id;
    QList <WrittenNote> notes;
    QString subject_name;

public:

    Subject();
    //to be called by the DBHandler
    Subject(int id, QList <WrittenNote> notes, QString name);


    //to crate a new Subject.
    Subject(QString name);

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
    void deleteSubject();
    void updateSubject();
    QString toString();


};

#endif // SUBJECT_H
