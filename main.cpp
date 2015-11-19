#include <QApplication>
#include <QtSql/QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("orgnnice.db3");
    if (db.open())
    {
        QSqlQuery query(db);

        //Tables

        query.exec("create table IF NOT EXISTS subject (id int primary key AUTINCREMENT, name varchar(100), fk_teacher int)");
        query.exec("create table IF NOT EXISTS note (pk_id int primary key AUTINCREMENT, content TEXT, Timestamp DATETIME, fk_subject int)");
        query.exec("create table IF NOT EXISTS tag (pk_id int primary key AUTINCREMENT, text varchar(100))");
        query.exec("create table IF NOT EXISTS noteHasTag (pk_id int primary key AUTINCREMENT, fk_noteId int, fk_tagId int))");
        query.exec("create table IF NOT EXISTS attachement (pk_id int primary key  AUTINCREMENT, filename varchar(100))");
        query.exec("create table IF NOT EXISTS noteHasAttachement (pk_id int primary key AUTINCREMENT, fk_note int, fk_attachement int)");
        query.exec("create table IF NOT EXISTS teacher (pk_id int primary key AUTOINCREMENT, firstname varchar(100), lastname varchar(100))");

        //Foreign Keys

        query.exec("ALTER TABLE note ADD CONSTRAINT fk_SubjectNote FOREIGN KEY (fk_subject) REFERENCES subject (pk_id) on delete no action");
        query.exec("ALTER TABLE subject ADD CONSTRAINT subject FOREIGN KEY (fk_teacher) REFERENCES teacher (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Attachement FOREIGN KEY (fk_attachement) REFERENCES attachement (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Tag FOREIGN KEY (fk_tag) REFERENCES tag (pk_id) on delete no action");
    }

    return a.exec();
}
