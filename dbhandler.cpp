#include "dbhandler.h"

DBHandler::DBHandler()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName( QDir::homePath() + QDir::separator() + "orgnnice.db3");
}

