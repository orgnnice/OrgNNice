#include "dbhandler.h"
#include <writtennote.h>
#include <subject.h>

DBHandler::DBHandler(QString folderPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(folderPath + QDir::separator() + "orgnnice.db3");
    resourcesFolder = folderPath + QDir::separator() + "resources";
    QDir folder = QDir(folderPath);
    folder.mkdir("resources");
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
        query.exec("create table IF NOT EXISTS schoolSubject (pk_id INTEGER primary key AUTOINCREMENT, name varchar(100) unique)");
        query.exec("create table IF NOT EXISTS note (pk_id INTEGER primary key AUTOINCREMENT, content TEXT, ts TIMESTAMP, fk_schoolSubject INTEGER)");
        query.exec("create table IF NOT EXISTS tag (pk_id INTEGER primary key AUTOINCREMENT, tagname varchar(100))");
        query.exec("create table IF NOT EXISTS noteHasTag (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_tag INTEGER)");
        query.exec("create table IF NOT EXISTS attachement (pk_id INTEGER primary key  AUTOINCREMENT, filename varchar(100))");
        query.exec("create table IF NOT EXISTS noteHasAttachement (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_attachement INTEGER)");

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
    if(!query.isActive())
    {
        qDebug() << query.lastError();
    }


    return query.isActive();
}

/**
 * @brief DBHandler::queryWithReturnNoteList
 * @param Statement An SQL query which is whished to be executed. Note: Has to select the whole row (*)
 * @return A list of notes that got selected by Statement
 */
QList<WrittenNote> DBHandler::queryWithReturnNoteList(QString statement)
{
    WrittenNote * pNote;
    qDebug() << "DBHandler -> queryWithReturnNoteList(" << statement << ");";

    QList<WrittenNote> notes;
    QSqlQuery query(db);
    query.exec(statement);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString text = query.value(1).toString();
        QList<QString> attachements = attachementsFromNote(id);
        QList<QString> tags = tagsFromNote(id);
        int saver = query.value(1).toInt();
        QDateTime timestamp;
        timestamp.addMSecs(saver);
        pNote=new WrittenNote(id,text,attachements, tags, timestamp);
        notes.append(*pNote);
    }
    return notes;
}

/**
 * @brief DBHandler::tagsFromNote
 * @return List of all Tags that were added to the given note_id
 */
QList<QString> DBHandler::tagsFromNote(int noteid)
{
    QList<QString> tags;
    QSqlQuery query(db);
    QString command = "SELECT tagname FROM tag WHERE pk_id in (SELECT fk_tag FROM noteHasTag WHERE fk_note = " + QString::number(noteid) + ")";
    query.exec(command);
    while (query.next())
    {
        tags.append(query.value(0).toString());
    }
    return tags;
}

/**
 * @brief DBHandler::tagsFromNote
 * @return List of all Attachements that were added to the given note_id
 */
QList<QString> DBHandler::attachementsFromNote(int noteid)
{
    QList<QString> attachs;
    QSqlQuery query(db);
    query.exec("SELECT tagname FROM tag WHERE pk_id in (SELECT fk_tag FROM noteHasTag WHERE fk_note = " + QString::number(noteid) +")");
    while (query.next())
    {
        attachs.append(query.value(0).toString());
    }
    return attachs;
}

QList<Subject> DBHandler::queryWithReturnSubjectList(QString statement)
{
    Subject * pSubject;
    qDebug() << "DBHandler -> queryWithReturnSubjectList(" << statement << ");";
    QList<Subject> subjects;
    QSqlQuery query(db);
    query.exec(statement);
    while (query.next())
    {
        int id = query.value(0).toInt();
        QList<WrittenNote> notes = queryWithReturnNoteList("SELECT * FROM note WHERE fk_schoolSubject = " + QString::number(id) + ")");

        QString subject_name =  query.value(1).toString();
        pSubject = new Subject(id, notes, subject_name);
        subjects.append(*pSubject);
    }
    return subjects;
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
int DBHandler::insertSubject(QString name)
{
    qDebug() <<  "DBHandler -> insertSubject(" + name + ")";
    return insertAndReturnID("INSERT INTO schoolSubject (name) VALUES ('" + name + "')");
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
bool DBHandler::insertWrittenNote(WrittenNote note)
{
    //next 9 lines only for debugging
    QString tagString, attachementsString = "";
    for(int i=0; i<note.getTags().size(); i++)
    {
        tagString += note.getTags()[i];
    }
    for(int i = 0; i < note.getAttachement().size(); i++)
    {
        attachementsString += note.getAttachement()[i] + " ";
    }
    qDebug() <<  "DBHandler -> insertWrittenNote(" << note.getContent()  << ", " << note.getTimestamp().toMSecsSinceEpoch() << ", " << tagString <<  ", " << attachementsString << ", " <<  note.getSubject_ID() << ")";

    //begin:

    //insert note:
    int noteId = insertAndReturnID("INSERT INTO note (content, ts, fk_schoolSubject) VALUES ('" + note.getContent() + "', " + QString::number(note.getTimestamp().toMSecsSinceEpoch()) + ", " + QString::number(note.getSubject_ID()) + ")");
    note.setSubject_ID(noteId);

    //insert Tags
    QList<QString>::iterator i;
    for (i = note.getTags().begin(); i != note.getTags().end(); ++i)
    {
        int tagId = insertTagAndReturnId(*i);
        //insert to noteHasTag-table
        queryNoReturn("INSERT INTO noteHasTag (fk_note, fk_tag), VALUES (" + QString::number(noteId) + ", " + QString::number(tagId));


    }

    //insert Attachments
    for (QString attachement : note.getAttachement())
    {
        int attachementID = insertAttachementAndReturnId(attachement);
        //insert to noteHasAttachement-table
        queryNoReturn("INSERT INTO noteHasAttachement (fk_note, fk_attachement), VALUES (" + QString::number(noteId) + ", " + QString::number(attachementID));
    }
    return noteId != -1;
}

/**
 * @brief DBHandler::updateWrittenNote PROBLEM: NICHT MEHR VERWENDETE TAGS/Attachments BLEIBEN IN DER DATENBANK !!!!!!!!!!!FIX!!!!!!!!!!!!!
 * @param note: The updated Writtennote
 * @param fk_schoolSubject
 * @return
 */
bool DBHandler::updateWrittenNote(WrittenNote note)
{
    qDebug() << "DBHandler->updateWrittenNote(" << note.getId() << ")";

    int noteId = note.getId();

    //insert Tags
    queryNoReturn("DELETE FROM notehasTag where fk_note = " + QString::number(noteId) + ")");
    for (QString tempTag : note.getTags())
    {
        qDebug() << "selectrückgabe toint:" << select("COUNT(tagname)", "tag", "tagname = '"+ tempTag +"'").toInt();
        if(select("COUNT(tagname)", "tag", "tagname = '"+ tempTag +"'").toInt() < 1)
        {
            queryNoReturn("INSERT INTO tag (tagname) VALUES('"+tempTag+"')");
        }
        qDebug() << "  tag: " << tempTag;
        QString TagId = select("pk_id","tag","tagname = '"+ tempTag +"'").replace('"',"");
        queryNoReturn("INSERT INTO noteHasTag (fk_note, fk_tag) VALUES (" + QString::number(noteId) + "," + TagId+")");
    }

    //insert Attachments
    queryNoReturn("DELETE FROM noteHasAttachement where fk_note = " + QString::number(noteId) + ")");
    for (QString attachement : note.getAttachement())
    {
        QString attachementId = "-1";
        if(select("COUNT(filename)", "attachement", "filename = '"+ attachement +"'").toInt() < 1)
        {
            attachementId = QString::number(insertAttachementAndReturnId(attachement));
        }else{
            attachementId = select("pk_id","attachment","where filename = '"+ attachement +"'");
        }
        queryNoReturn("INSERT INTO noteHasAttachement (fk_note, fk_attachement) VALUES (" + QString::number(noteId) + ", " + attachementId + ")");
    }
    return noteId != -1;
}
/*
//insert note:
    int noteId = insertAndReturnID("UPDATE WrittenNote SET content = " + note.getContent() + ", ts = " + note.getTimestamp().toMSecsSinceEpoch() + ", fk_schoolSubject = " + fk_schoolSubject + " WHERE pk_id = " + note.getId() + ")");

    //insert Tags
    queryNoReturn("DELETE FROM notehasTag where fk_note = " + QString::number(noteId) + ")");
    QList<QString>::iterator i;
    for (i = note.getTags().begin(); i != note.getTags().end(); ++i)
    {
        if(select("COUNT(tagname)", "tag", "where tagname = \""+ *i+"\"").toInt() < 0)
        {
            queryNoReturn("INSERT INTO tag (tagname) VALUES("+*i+")");
        }
        QString TagId = select("pk_id","tag","where tagname = \""+ *i+"\"");
        queryNoReturn("INSERT INTO noteHasTag (fk_note, fk_attachement), VALUES (" + QString::number(noteId) + ", " + TagId);
    }

    //insert Attachments
    queryNoReturn("DELETE FROM noteHasAttachement where fk_note = " + QString::number(noteId) + ")");
    QList<QString>::iterator j;
    for (j = note.getAttachement().begin(); j != note.getAttachement().end(); ++j)
    {
        if(select("COUNT(filename)", "attachment", "where filename = \""+ *j +"\"").toInt() < 0)
        {
            //insert to noteHasAttachement-table
            queryNoReturn("INSERT INTO attachement (filename) VALUES("+*j+")");
        }
        QString AttachementId = select("pk_id","tag","where tagname = \""+ *j+"\"");
        queryNoReturn("INSERT INTO noteHasAttachement (fk_note, fk_attachement), VALUES (" + QString::number(noteId) + ", " + AttachementId);
    }
    return noteId != -1;
*/

/*bool DBHandler::insertWrittenNote(WrittenNote note)
{
    QList<QString> tags = note.getTags();
    //next 5 lines only for debugging
    QString tagString, attachementsString = "";
    for(int i=0; i<note.getTags().size(); i++)
    {
        tagString += note.getTags()[i];
    }
    Attachement attachements = note.getAttachement();
    for(int i = 0; i < attachements.size(); i++)
    {
        attachementsString += attachements[i] + " ";
    }
    qDebug() <<  "DBHandler -> insertWrittenNote(" << note.getText()  << ", " << note.getTs().toMSecsSinceEpoch() << ", " << tagString <<  ", " << attachementsString << ", " <<  note.getFk_schoolSubject() << ")";

    //begin:

    //insert note:
    int noteId = insertAndReturnID("INSERT INTO WrittenNote (content, ts, fk_schoolSubject) VALUES (" + note.getText() + ", " + ts.toMSecsSinceEpoch() + ", " + note.getFk_schoolSubject() + ")");

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
}*/

/**
 * @brief DBHandler::insertTagAndReturnId
 * @param tag
 * @return inserts tag and returns id of tag, if tag is already in the database, it returns the id of it.
 */
int DBHandler::insertTagAndReturnId(QString tag)
{
    qDebug() << "insertTagAndReturnId(" << tag << ")";
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

int DBHandler::insertAttachementAndReturnId(QString attachementPath)
{
    qDebug() << "DBHandler -> insertAttechementAndReturnId(" << attachementPath <<")";

    QStringList pieces = attachementPath.split(QDir::separator());
    QString name = pieces.value(pieces.length() - 1);


    int attatchmentId =  insertAndReturnID("INSERT INTO attachement(filename) VALUES('"+name+"')");
    qDebug() << "Attatchement from " << attachementPath << " inserted at " << attatchmentId;

    //copy File to Folder
    QString destPath = resourcesFolder + QDir::separator() + QString::number(attatchmentId) + "_" + name;
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
    if(!query.isActive()){
        qDebug() << "  Query failed -> returned '-1'";
        return -1;
    }
    int id = -1;
    while (query.next()) {
        id = query.value(0).toInt();
    }
    qDebug() <<  "  " << id;
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
    if (!where.startsWith("where")){
        where = "WHERE " + where + "";
    }
    QSqlQuery query(db);
    qDebug() << "  Statement: " << "SELECT " + coulum + " FROM " + table + " " + where;
    query.exec("SELECT " + coulum + " FROM " + table + " " + where);
    if(!query.isActive()){
        qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        return "-1";
    }

    while (query.next()) {
        result += query.value(0).toString();
    }
    qDebug() << "returnvalue:" << result;
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

        id = getLastIsertId(query);
        qDebug() <<  "  Last inserted ID is " << QString::number(id);
    }
    else{
        qDebug() <<  "  Statement failed. Error: " << query.lastError();
    }
    qDebug() <<  "  Retutnvalue: " << id;
    return id;
}

void DBHandler::deleteUnusedTags()
{
    QList<int> tags;
    QSqlQuery query(db);
    query.exec("Select pk_id from tag");
    while (query.next()) {
        tags.append(query.value(0).Int);
    }
    for(int i = 0; i <= tags.length(); i ++)
    {
        if(select("COUNT(pk_id)", "noteHasTag", "fk_Tag = '"+ QString::number(tags[i]) +"'") <= 0)
        {
            query.exec("delete * from note where (pk_id = " + QString::number(tags[i]) + ")");
        }
    }
}

void DBHandler::deleteUnusedAttachments()
{
    QList<int> tags;
    QSqlQuery query(db);
    query.exec("Select pk_id from attachment");
    while (query.next()) {
        tags.append(query.value(0).Int);
    }
    for(int i = 0; i < tags.length(); i ++)
    {
        if(select("COUNT(pk_id)", "noteHasAttachment", "fk_Tag = '"+ QString::number(tags[i]) +"'") <= 0)
        {
            query.exec("delete * from attachment where (pk_id = " + QString::number(tags[i]) + ")");
        }
    }
}

void DBHandler::deleteWrittenNote(int id)
{
    queryNoReturn("delete * from WrittenNote where (pk_id = " + QString::number(id) + ")");
    queryNoReturn("delete * from noteHasTag where (fk_note = " + QString::number(id) + ")");
    queryNoReturn("delete * from noteHasAttachment where (fk_note = " + QString::number(id) + ")");
}

void DBHandler::deleteSubject(int id)
{
    queryNoReturn("delete * from schoolSubject where (pk_id = " + QString::number(id) + ")");
    QList<int> note;
    QSqlQuery query(db);
    query.exec("Select pk_id note where (fk_schoolSubject = " + QString::number(id) + ")");
    while (query.next()) {
        note.append(query.value(0).Int);
    }
    for(int i = 0; i < note.length(); i ++)
    {
        deleteWrittenNote(note[i]);
    }
}

