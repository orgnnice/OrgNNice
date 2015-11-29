#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <QtSql/QtSql>
#include <writtennote.h>
#include <subject.h>
#include <QFile>

class DBHandler
{
private:
    QSqlDatabase db;
    QString resourcesFolder;
    QList<QString> tagsFromNote(int noteid);
    QList<Attachement> attachementsFromNote(int noteid);

public:
    DBHandler(QString resFolderPath);
    void closeDatabase();
    void createDatabaseIfNotExists();
    bool queryNoReturn(QString query);
    QList<WrittenNote> queryWithReturnNoteList(QString statement);
    QList<subject> queryWithReturnSubjectList(QString statement);

    bool insertSubject(QString name, QString fk_teacherID);
    bool insertWrittenNote(QString text, QDateTime ts, int fk_schoolSubject, QList<QString> tags, QList<QString> attachements);
    int insertTagAndReturnId(QString tag);
    int insertAttechementAndReturnId(QString attachementPath);
    int insertAndReturnID(QString statement);
    int getLastIsertId(QSqlQuery query);
    QString select (QString coulum, QString table, QString where);

};

#endif // DBHANDLER_H
