#include "exportimport.h"
#include "main.h"
#include "writtennote.h"

ExportImport::ExportImport(QString folderPath)
{
    qDebug() << "SQLITE DATABSE CREATED";
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
    if(subject != "")
    {
        dbExImport->insertSubject(subject);
        return exportDatabasewithSubject(all, todo, notes, waitFor, pDBh->select("pk_id", "SchoolSubject", "name='" + subject + "'").replace('"', "").toInt());
    } else
    {
        if(all)
        {
            QList<WrittenNote> noteList = pDBh->queryWithReturnNoteList("select * from note");
            for(int i = 0; i < noteList.length(); i++)
            {
                dbExImport->insertWrittenNote(noteList[i]);
            }
        } else
        {
            if(notes)
            {
                QList<WrittenNote> noteList = pDBh->queryWithReturnNoteList("select * from note");
                for(int i = 0; i < noteList.length(); i++)
                {
                    dbExImport->insertWrittenNote(noteList[i]);
                }

            }else if(todo)
            {

            } else if(waitFor)
            {

            }

        }
    }
}

int ExportImport::exportDatabasewithSubject(bool all, bool todo, bool notes, bool waitFor, int subject)
{
    qDebug() << "EXPORT COMMAND EXECUTED";
    if(all)
    {
        QList<WrittenNote> noteList = pDBh->queryWithReturnNoteList("select * from note where(fk_schoolSubject = " + QString::number(subject) + ")");
        for(int i = 0; i < noteList.length(); i++)
        {
            dbExImport->insertWrittenNote(noteList[i]);
        }
    } else
    {
        if(notes)
        {
            QList<WrittenNote> noteList = pDBh->queryWithReturnNoteList("select * from note where(fk_schoolSubject = " + QString::number(subject) + ")");
            for(int i = 0; i < noteList.length(); i++)
            {
                dbExImport->insertWrittenNote(noteList[i]);
            }
        } else if(todo)
        {

        } else if(waitFor)
        {

        }
    }
}
