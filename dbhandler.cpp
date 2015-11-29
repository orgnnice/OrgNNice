#include "dbhandler.h"


DBHandler::DBHandler(QString resFolderPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(resFolderPath + QDir::separator() + "orgnnice.db3");
    resourcesFolder = resFolderPath + QDir::separator() + "resources";
    createDatabaseIfNotExists();
}


/**
 * @brief WrittenNote::createDatabase
 * Creates the structure of the database, if it does not exists allready.
 * To be called at every start
 */
void DBHandler::createDatabaseIfNotExists()
{
    qDebug() << "DBHandler -> createDatabaseIfNotExists()";
    if (db.open())
    {
        qDebug() << "  Success: Database " << db.databaseName() << " successfully opend";
        QSqlQuery query(db);
        query.exec("create table IF NOT EXISTS schoolSubject (pk_id INTEGER primary key AUTOINCREMENT, name varchar(100), fk_teacher INTEGER)");
        query.exec("create table IF NOT EXISTS note (pk_id INTEGER primary key AUTOINCREMENT, content TEXT, ts TIMESTAMP, fk_schoolSubject INTEGER)");
        query.exec("create table IF NOT EXISTS tag (pk_id INTEGER primary key AUTOINCREMENT, tagname varchar(100)) unique");
        query.exec("create table IF NOT EXISTS noteHasTag (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_tag INTEGER)");
        query.exec("create table IF NOT EXISTS attachement (pk_id INTEGER primary key  AUTOINCREMENT, filename varchar(100))");
        query.exec("create table IF NOT EXISTS noteHasAttachement (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_attachement INTEGER)");
        query.exec("create table IF NOT EXISTS teacher (pk_id INTEGER primary key AUTOINCREMENT, firstname varchar(100), lastname varchar(100))");

        //Foreign Keys

        query.exec("ALTER TABLE note ADD CONSTRAINT fk_schoolSubjectNote FOREIGN KEY (fk_schoolSubject) REFERENCES schoolSubject (pk_id) on delete no action");
        query.exec("ALTER TABLE schoolSubject ADD CONSTRAINT schoolSubject FOREIGN KEY (fk_teacher) REFERENCES teacher (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Attachement FOREIGN KEY (fk_attachement) REFERENCES attachement (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Tag FOREIGN KEY (fk_tag) REFERENCES tag (pk_id) on delete no action");

        //Unique

        query.exec("CREATE UNIQUE INDEX tag_tagname ON tag(tagname)");

        qDebug() << "Tables in database: " << db.tables();
    }
    else
    {
        qDebug() << "  Error: Database \"" << db.databaseName() << "\" did not open";
    }

}


bool DBHandler::queryNoReturn(QString statement)
{
    qDebug() << "DBHandler -> queryNoReturn(" << statement << ");";
    QSqlQuery query(db);
    query.exec(statement);
    qDebug() << "Satement was:"  << query.isActive();
    return query.isActive();
}

QList<WrittenNote> DBHandler::queryWithReturnNoteList(QString statement)
{
    QList<WrittenNote>
    qDebug() << "DBHandler -> queryWithReturnNoteList(" << statement << ");";

}




QList<subject> DBHandler::queryWithReturnSubjectList(QString statement)
{
    qDebug() << "DBHandler -> queryWithReturnSubjectList(" << statement << ");";
}


void DBHandler::closeDatabase()
{
    db.close();
}

/**
 * @brief DBHandler::insertSubject
 * @todo refactoring with string-functions a la format in Java.
 * @todo Get teacherId To name
 */
bool DBHandler::insertSubject(QString name, QString fk_teacherID)
{
    qDebug() <<  "DBHandler -> insertSubject(" + name + ", " + fk_teacherID + ")";
    return queryNoReturn("INSERT INTO schoolSubject (name, fk_teacher) VALUES (" + name + ", " + fk_teacherID + ")");
}


/**
 * @brief DBHandler::insertWrittenNote
 * @param text
 * @param ts
 * @param fk_schoolSubject
 * @param tags
 * @param attachements
 * @return true, if everything was succesful, false when the note could not be inserted.
 */
bool DBHandler::insertWrittenNote(QString text, QDateTime ts, int fk_schoolSubject, QList<QString> tags, QList<QString> attachements)
{
    //next 5 lines only for debugging
    QString tagString, attachementsString = "";
    for(int i=0; i<tags.size(); i++)
    {
        tagString += tags[i];
    }
    for(int i = 0; i < attachements.size(); i++)
    {
        attachementsString += attachements[i] + " ";
    }
    qDebug() <<  "DBHandler -> insertWrittenNote(" << text  << ", " << ts.toMSecsSinceEpoch() << ", " << tagString <<  ", " << attachementsString << ", " <<  fk_schoolSubject << ")";

    //begin:

    //insert note:
    int noteId = insertAndReturnID("INSERT INTO WrittenNote (content, ts, fk_schoolSubject) VALUES (" + text + ", " + ts.toMSecsSinceEpoch() + ", " + fk_schoolSubject + ")");

    //insert Tags
    QList<QString>::iterator i;
    for (i = tags.begin(); i != tags.end(); ++i)
    {
        int tagId = insertTagAndReturnId(*i);
        //insert to noteHasTag-table
        queryNoReturn("INSERT INTO noteHasTag (fk_note, fk_tag), VALUES (" + QString::number(noteId) + ", " + QString::number(tagId));
    }

    //insert Attatchments
    QList<QString>::iterator j;
    for (j = attachements.begin(); j != tags.end(); ++j)
    {
        int attachementID = insertAttechementAndReturnId(*j);
        //insert to noteHasAttachement-table
        queryNoReturn("INSERT INTO noteHasAttachement (fk_note, fk_attachement), VALUES (" + QString::number(noteId) + ", " + QString::number(attachementID));
    }


    return noteId != -1;
}


/**
 * @brief DBHandler::insertTagAndReturnId
 * @param tag
 * @return inserts tag and returns id of tag, if tag is already in the database, it returns the id of it.
 */
int DBHandler::insertTagAndReturnId(QString tag)
{
    int tagId= -1;
    if(select("COUNT(tagname)", "tag", "where tagname = \""+ tag+"\"").toInt() > 0)
    {

        tagId =  insertAndReturnID("INSERT INTO tag(tagname) VALUES("+tag+")");
        qDebug() << "tag " << tag << "was inserted at" << tagId;
    }else
    {
        tagId =  select("pk_id", "tag", "where tagname = \""+ tag+"\"").toInt();
        qDebug() << "tag " << tag << "allready exists at" << tagId;
    }
    return tagId;
}





/**
 * @brief DBHandler::insertAttechementAndReturnId
 * @param attachementPath
 * @return pk_id in database of the inserted Attachement.
 * @info copies the attachement as well.
 *
 */

int DBHandler::insertAttechementAndReturnId(QString attachementPath)
{
    qDebug() << "DBHandler -> insertAttechement(" << attachementPath <<")";

    QStringList pieces = attachementPath.split(QDir::separator());
    QString name = pieces.value(pieces.length() - 1);

    int attatchmentId =  insertAndReturnID("INSERT INTO attachement(filename) VALUES("+name+")");
    qDebug() << "Attatchement from " << attachementPath << " inserted at " << attatchmentId;

    //copy File to Folder
    QString destPath = resourcesFolder + QDir::separator() + attatchmentId + "_" + name;
    QFile::copy(attachementPath, destPath);
    qDebug() << "Attatchement copied from " << attachementPath << " to " << destPath;

    return attatchmentId;
}

/**
 * @brief DBHandler::getLastIsertId
 * @param query
 * @return if the statement failed -1, ifnot last_inserted_id.
 */
int DBHandler::getLastIsertId(QSqlQuery query)
{
    qDebug() <<  "DBHandler -> getLastIsertId()";
    query.exec("SELECT last_insert_rowid()");
    if(query.isActive()){
        qDebug() << "Query failed -> returned '-1'";
        return -1;
    }
    int id = -1;
    while (query.next()) {
        id = query.value(0).toInt();
    }
    qDebug() <<  "DBHandler -> getLastIsertId() -> " << id;
    return id;
}


/**
 * @brief DBHandler::select
 * @param coulum
 * @param table
 * @param where
 * @return a String with every returned Value, if statement failed: -1
 */
QString DBHandler::select(QString coulum, QString table, QString where)
{
    QString result  = "";

    qDebug() <<  "DBHandler -> select(" << coulum << ", " <<  table  << ", " << where;
    if (where != ""){
        where = "WHERE " + where + "";
    }
    QSqlQuery query(db);
    query.exec("SELECT " + coulum + " FROM " + table + " " + where);
    if(!query.isActive()){
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        return "-1";
    }

    while (query.next()) {
        result += query.value(0).toString();
    }
    return result;
}

// SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();


/**
 * @brief DBHandler::insertAndReturnID
 * @param statement
 * @return id of last inserted id after statement. if the statement failed, it returns -1
 */
int DBHandler::insertAndReturnID(QString statement)
{
    qDebug() <<  "DBHandler -> insertAndReturnID(" << statement << ")";
    int id = -1;
    QSqlQuery query(db);
    query.exec(statement);

    if(query.isActive())
    {
        int id = getLastIsertId(query);
        qDebug() <<  "Last inserted ID is " << QString::number(id);
    }
    else{
        qDebug() <<  "Statement failed. returned -1";
    }
    return id;
}


