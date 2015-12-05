#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql/QtSql>
#include <QFile>
#include <attachement.h>

class WrittenNote;
class subject;
class DBHandler
{
private:
    QSqlDatabase db;
    QString resourcesFolder;
    QList<QString> tagsFromNote(int noteid);
    QList<Attachement> attachementsFromNote(int noteid);

public:
    DBHandler(QString resFolderPath);
    DBHandler();
    void closeDatabase();
    void createDatabaseIfNotExists();
    bool queryNoReturn(QString query);
    QList<WrittenNote> queryWithReturnNoteList(QString statement);
    QList<subject> queryWithReturnSubjectList(QString statement);

    bool insertSubject(QString name, QString fk_teacherID);
    bool insertWrittenNote(QString text, QDateTime ts, int fk_schoolSubject, QList<QString> tags, QList<QString> attachements);
    bool insertWrittenNote(WrittenNote note);
    bool updateWrittenNote(WrittenNote note, int fk_Subject);

    int insertTagAndReturnId(QString tag);
    int insertAttechementAndReturnId(QString attachementPath);
    int insertAndReturnID(QString statement);
    int getLastIsertId(QSqlQuery query);
    QString select (QString coulum, QString table, QString where);

};

#endif // DBHANDLER_H
