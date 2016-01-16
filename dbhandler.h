#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QtSql/QtSql>
#include <QFile>

class WrittenNote;
class Subject;
class ToDoItem;
class WaitForList;

class DBHandler
{
private:
    QSqlDatabase db;
    //QString resourcesFolder;
    QList<QString> tagsFromNote(int noteid);
    QList<QString> attachementsFromNote(int noteid);

public:
    DBHandler(QString resFolderPath, QString dbName);
    DBHandler();
    void closeDatabase();
    void createDatabaseIfNotExists();
    bool queryNoReturn(QString query);
    QList<WrittenNote> queryWithReturnNoteList(QString statement);
    QList<Subject> queryWithReturnSubjectList(QString statement);
    QList<ToDoItem> queryWithReturnToDoItemList(QString statement);
    QList<WaitForList> queryWithReturnWaitForListList(QString statement);

    QList<Subject> getAllSubjects();
    QList<WrittenNote> getAllNotesFromSubject(int subjectID);

    void DBHandlerStateDebugOut();



    int insertSubject(QString name);
    bool insertWrittenNote(QString text, QDateTime ts, int fk_schoolSubject, QList<QString> tags, QList<QString> attachements);
    int insertWrittenNote(WrittenNote note);

    void insertWrittenTagToNote(int noteID, QString tag);
    void insertAttachementToNote(int noteId, QString attachement);


    bool updateWrittenNote(WrittenNote note);

    int insertTagAndReturnId(QString tag);
    int insertAttachementAndReturnId(QString attachementPath);
    int insertAndReturnID(QString statement);
    int getLastIsertId(QSqlQuery query);
    QString select (QString coulum, QString table, QString where);


    int insertTODOandReturnId(ToDoItem todoItem);
    void updateTODO(ToDoItem todoItem);
    void deleteToDo(ToDoItem todoItem);

    int insertWaitForandReturnId(WaitForList WaitForItem);
    void updateWaitFor(WaitForList WaitForItem);
    void deleteWaitFor(WaitForList WaitforItem);

    void deleteUnusedTags();
    void deleteUnusedAttachments();
    void deleteWrittenNote(int id);
    void deleteSubject(int id);
    void removeAttachement(WrittenNote note, QString attachmentpath);
};

#endif // DBHANDLER_H
