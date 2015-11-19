#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    saveText w;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("orgnnice.db3");
    if (db.open())
    {
        QSqlQuery query(db);
        query.exec("create table IF NOT EXISTS subject (id int primary key, firstname varchar(20), lastname varchar(20))");
        query.exec("constraint fk_noteTag");
        query.exec("create table IF NOT EXISTS note (id int primary key, firstname varchar(20), lastname varchar(20))");
        query.exec("create table IF NOT EXISTS tag (id int primary key, firstname varchar(20), lastname varchar(20))");
        query.exec("create table IF NOT EXISTS NoteHasTag (id int primary key, firstname varchar(20), lastname varchar(20))");
        query.exec("create table IF NOT EXISTS Attachement (id int primary key, firstname varchar(20), lastname varchar(20))");
        query.exec("create table IF NOT EXISTS NoteHasAttachement (id int primary key, firstname varchar(20), lastname varchar(20))");
    }

    w.show();

    return a.exec();
}
