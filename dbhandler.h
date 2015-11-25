#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <QtSql/QtSql>
#include <writtennote.h>

class DBHandler
{
private:
    static QSqlDatabase db;

public:
    DBHandler();

    void queryNoReturn(QString query);
    List<WrittenNote> queryWithReturnNoteList(QString query);
};

#endif // DBHANDLER_H
