#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql/QtSql>
#include <QFile>

class WrittenNote;
class Subject;
class DBHandler
{
private:
    QSqlDatabase db;
    QString resourcesFolder;
    QList<QString> tagsFromNote(int noteid);
    QList<QString> attachementsFromNote(int noteid);

public:
    DBHandler(QString resFolderPath);
    DBHandler();
    void closeDatabase();
    void createDatabaseIfNotExists();
    bool queryNoReturn(QString query);
    QList<WrittenNote> queryWithReturnNoteList(QString statement);
    QList<Subject> queryWithReturnSubjectList(QString statement);

    int insertSubject(QString name);
    bool insertWrittenNote(QString text, QDateTime ts, int fk_schoolSubject, QList<QString> tags, QList<QString> attachements);
    bool insertWrittenNote(WrittenNote note);
    bool updateWrittenNote(WrittenNote note);

    int insertTagAndReturnId(QString tag);
    int insertAttachementAndReturnId(QString attachementPath);
    int insertAndReturnID(QString statement);
    int getLastIsertId(QSqlQuery query);
    QString select (QString coulum, QString table, QString where);

};

#endif // DBHANDLER_H
