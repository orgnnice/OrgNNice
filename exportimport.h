#ifndef EXPORTIMPORT_H
#define EXPORTIMPORT_H

#include <QtSql/QtSql>
#include <dbhandler.h>


class ExportImport
{
private:
    DBHandler* dbExImport;

public:
    ExportImport(QString folderPath);


    int exportDatabase(bool all, bool todo, bool notes, bool waitFor, QString subject);
    int exportDatabasewithSubject(bool all, bool todo, bool notes, bool waitFor, int subject, int exportSubID);

    int importDatabase();
    int importDatabasewithSubject(int subject, int exportSubID);
};

#endif // EXPORTIMPORT_H
