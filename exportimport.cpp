#include "exportimport.h"
#include "main.h"
#include "writtennote.h"
#include "subject.h"
#include "waitforlist.h"
#include "todoitem.h"

//#define debug

ExportImport::ExportImport(QString folderPath)
{
    qDebug() << "!!!   !!!!  !!    !!!!!   !!!!! >>>>>>>> EXPORT  - t e s t <<<<<<<<<<<<";
    qDebug() << "SQLITE DATABSE CREATED";
    QString file = (QDir::homePath() + QDir::separator() + "orgnniceExImport.db3");
    QByteArray bafile = file.toLatin1();
    const char *c_str2 = bafile.data();
    remove(c_str2);
    dbExImport = new DBHandler(QDir::homePath(), "orgnniceExImport.db3");
}

/**
 * @brief ExportImport::exportDatabase
 * @param all
 * @param todo
 * @param waitFor
 * @param subject
 */
int ExportImport::exportDatabase(bool all, bool todo, bool notes, bool waitFor, QString subject)
{
    QList<Subject> allSubjects;
    if(subject != "")
    {
        allSubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject where (name = '" + subject + "')");
    } else
    {
        allSubjects = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    }

    for(Subject chosenSub : allSubjects)
    {
        dbExImport->insertSubject(chosenSub.getName());
        int exportSubID = dbExImport->select("pk_id", "schoolSubject", "name = '" + chosenSub.getName() + "'").toInt();
        exportDatabasewithSubject(all, todo, notes, waitFor, chosenSub.getId(), exportSubID);
    }
}

int ExportImport::exportDatabasewithSubject(bool all, bool todo, bool notes, bool waitFor, int subject, int exportSubID)
{
    qDebug() << "EXPORT COMMAND EXECUTED";
    if(all)
    {
        QList<WrittenNote> noteList = pDBh->queryWithReturnNoteList("select * from note where(fk_schoolSubject = " + QString::number(subject) + ")");
        for(WrittenNote note : noteList)
        {
            note.setSubject_ID(exportSubID);
            dbExImport->insertWrittenNote(note);
        }

        QList<ToDoItem> todoList = pDBh->queryWithReturnToDoItemList("select * from todo where(fk_schoolSubject = " + QString::number(subject) + ")");
        for(ToDoItem todo : todoList)
        {
            todo.setSubjectID(exportSubID);
            dbExImport->insertTODOandReturnId(todo);
        }

        QList<WaitForList> waitForList = pDBh->queryWithReturnWaitForListList("select * from waitfor where(fk_schoolSubject = " + QString::number(subject) + ")");
        for(WaitForList waitfor : waitForList)
        {
            waitfor.setSubjectID(exportSubID);
            dbExImport->insertWaitForandReturnId(waitfor);
        }
    } else
    {
        if(notes)
        {
            QList<WrittenNote> noteList = pDBh->queryWithReturnNoteList("select * from note where(fk_schoolSubject = " + QString::number(subject) + ")");
            for(WrittenNote note : noteList)
            {
                note.setSubject_ID(exportSubID);
                dbExImport->insertWrittenNote(note);
            }
        } else if(todo)
        {
            QList<ToDoItem> todoList = pDBh->queryWithReturnToDoItemList("select * from todo where(fk_schoolSubject = " + QString::number(subject) + ")");
            for(ToDoItem todo : todoList)
            {
                todo.setSubjectID(exportSubID);
                dbExImport->insertTODOandReturnId(todo);
            }
        } else if(waitFor)
        {
            QList<WaitForList> waitForList = pDBh->queryWithReturnWaitForListList("select * from waitfor where(fk_schoolSubject = " + QString::number(subject) + ")");
            for(WaitForList waitfor : waitForList)
            {
                waitfor.setSubjectID(exportSubID);
                dbExImport->insertWaitForandReturnId(waitfor);
            }
        }
    }
}
