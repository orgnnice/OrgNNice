#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QtSql/QtSql>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);

 QSqlDatabase db;
 db = QSqlDatabase::addDatabase("QSQLITE");
 db.setDatabaseName( QDir::homePath() + QDir::separator() + "orgnnice.db3");
 if (db.open())
 {
 QSqlQuery query(db);
    /*
    query.exec("create table person (id INTEGER primary key AUTOINCREMENT, firstname varchar(20), lastname varchar(20))");
    query.exec("insert into person (firstname, lastname) values('Danny', 'Young')");
    query.exec("insert into person (firstname, lastname) values('Christine', 'Holand')");
    query.exec("insert into person (firstname, lastname) values('Lars', 'Gordon')");
    query.exec("insert into person (firstname, lastname) values('Roberto', 'Robitaille')");
    query.exec("insert into person (firstname, lastname) values('Maria', 'Papadopoulos')");
    */
    query.exec("create table IF NOT EXISTS schoolSubject (pk_id INTEGER primary key AUTOINCREMENT, name varchar(100), fk_teacher INTEGER)");
    query.exec("create table IF NOT EXISTS note (pk_id INTEGER primary key AUTOINCREMENT, content TEXT, ts TIMESTAMP, fk_schoolSubject INTEGER)");
    query.exec("create table IF NOT EXISTS tag (pk_id INTEGER primary key AUTOINCREMENT, tagname varchar(100))");
    query.exec("create table IF NOT EXISTS noteHasTag (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_tag INTEGER)");
    query.exec("create table IF NOT EXISTS attachement (pk_id INTEGER primary key  AUTOINCREMENT, filename varchar(100))");
    query.exec("create table IF NOT EXISTS noteHasAttachement (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_attachement INTEGER)");
    query.exec("create table IF NOT EXISTS teacher (pk_id INTEGER primary key AUTOINCREMENT, firstname varchar(100), lastname varchar(100))");

    /*query.exec("SELECT firstname, lastname FROM person");
    while (query.next())
    {
           QString vorname = query.value(0).toString();
           QString nachname = query.value(1).toString();
           qDebug() << vorname << nachname;
    }*/

    //Foreign Keys

    //query.exec("ALTER TABLE note ADD CONSTRAINT fk_schoolSubjectNote FOREIGN KEY (fk_schoolSubject) REFERENCES schoolSubject (pk_id) on delete no action");
    //query.exec("ALTER TABLE schoolSubject ADD CONSTRAINT schoolSubject FOREIGN KEY (fk_teacher) REFERENCES teacher (pk_id) on delete no action");
    //query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
    //query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Attachement FOREIGN KEY (fk_attachement) REFERENCES attachement (pk_id) on delete no action");
    //query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
    //query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Tag FOREIGN KEY (fk_tag) REFERENCES tag (pk_id) on delete no action");
    db.close(); // for close connection
    }
 return app.exec();

}


