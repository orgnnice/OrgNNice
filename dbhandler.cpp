#include "dbhandler.h"
#include <writtennote.h>
#include <subject.h>
#include <todoitem.h>
#include <waitforlist.h>

DBHandler::DBHandler(QString folderPath, QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE", dbName);
    db.setDatabaseName(folderPath + QDir::separator() + dbName);
    //resourcesFolder = folderPath + QDir::separator() + "resources";
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

        query.exec("create table IF NOT EXISTS todo (pk_id INTEGER primary key AUTOINCREMENT, description TEXT, deadline TIMESTAMP, done INTEGER, fk_schoolSubject INTEGER)");
        query.exec("create table IF NOT EXISTS waitfor (pk_id INTEGER primary key AUTOINCREMENT, description TEXT, done INTEGER, fk_schoolSubject INTEGER)");


        query.exec("create table IF NOT EXISTS tag (pk_id INTEGER primary key AUTOINCREMENT, tagname varchar(100))");
        query.exec("create table IF NOT EXISTS noteHasTag (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_tag INTEGER)");
        query.exec("create table IF NOT EXISTS attachement (pk_id INTEGER primary key  AUTOINCREMENT, filename varchar(100) UNIQUE)");
        query.exec("create table IF NOT EXISTS noteHasAttachement (pk_id INTEGER primary key AUTOINCREMENT, fk_note INTEGER, fk_attachement INTEGER)");

        //Foreign Keys

        query.exec("ALTER TABLE note ADD CONSTRAINT fk_schoolSubjectNote FOREIGN KEY (fk_schoolSubject) REFERENCES schoolSubject (pk_id) on delete no action");
        query.exec("ALTER TABLE waitfor ADD CONSTRAINT fk_schoolSubjectWaitFor FOREIGN KEY (fk_schoolSubject) REFERENCES schoolSubject (pk_id) on delete cascade");
        query.exec("ALTER TABLE todo ADD CONSTRAINT fk_schoolSubjectTODO FOREIGN KEY (fk_schoolSubject) REFERENCES schoolSubject (pk_id) on delete cascade");
        query.exec("ALTER TABLE schoolSubject ADD CONSTRAINT schoolSubject FOREIGN KEY (fk_teacher) REFERENCES teacher (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasAttachement ADD CONSTRAINT cst_noteHasAttachement_Attachement FOREIGN KEY (fk_attachement) REFERENCES attachement (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Note FOREIGN KEY (fk_note) REFERENCES note (pk_id) on delete no action");
        query.exec("ALTER TABLE noteHasTag ADD CONSTRAINT cst_noteHasTag_Tag FOREIGN KEY (fk_tag) REFERENCES tag (pk_id) on delete no action");

        //Unique

        query.exec("CREATE UNIQUE INDEX tag_tagname ON tag(tagname)");
        query.exec("CREATE UNIQUE INDEX noteHasTag_unique ON noteHasTag(fk_note, fk_tag)");
        query.exec("CREATE UNIQUE INDEX noteHasAttachement_unique ON noteHasAttachement(fk_note, fk_attachement)");

        qDebug() << "Tables in database: " << db.tables();
    }
    else
    {
        qDebug() << "  Error: Database \"" << db.databaseName() << "\" did not open";
    }

}

void DBHandler::DBHandlerStateDebugOut()
{
    qDebug() << "  Database \"" << db.databaseName();
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

    qDebug() << query.isActive();
    while (query.next())
    {
        qDebug() << "adding note...";
        int id = query.value(0).toInt();
        QString text = query.value(1).toString();
        QList<QString> attachements = attachementsFromNote(id);
        QList<QString> tags = tagsFromNote(id);
        QByteArray saver_string = query.value(2).toString().toLatin1();
        qint64 saver = 0;
        for(int i = 0; i < saver_string.length(); i++)
        {
            saver = 10*saver + (saver_string[i] - '0');
        }
        QDateTime timestamp = QDateTime::fromMSecsSinceEpoch(saver);
        int subjID = query.value(3).toInt();
        pNote=new WrittenNote(id,text,attachements, tags, timestamp, subjID);
        notes.append(*pNote);
    }
    return notes;
}


/**
 * @brief DBHandler::queryWithReturnToDoItemList, <todo> test it
 * @param statement
 * @return
 */
QList<ToDoItem> DBHandler::queryWithReturnToDoItemList(QString statement)
{
    qDebug() << "DBHandler -> queryWithReturnToDoItemList(" << statement << ");";

    ToDoItem * pToDo;

    QList<ToDoItem> toDos;
    QSqlQuery query(db);
    query.exec(statement);
    qDebug() << "statement was: " << query.isActive();
    while (query.next())
    {
        qDebug() << "adding ToDo...";
        int id = query.value(0).toInt();
        QString description = query.value(1).toString();
        qDebug() << "-------------------------------------------------------------------------------------------------------------";
        QByteArray saver_string = query.value(2).toString().toLatin1();
        qint64 saver = 0;
        for(int i = 0; i < saver_string.length(); i++)
        {
            saver = 10*saver + (saver_string[i] - '0');
        }
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(saver);
        bool done = (query.value(3).toInt() == 0) ? false : true;
        int subjID = query.value(4).toInt();
        pToDo=new ToDoItem (id, description, dateTime, done, subjID);
        toDos.append(*pToDo);
    }
    return toDos;
}

/**
 * @brief DBHandler::queryWithReturnWaitForListList  <todo> to be tested
 * @param statement
 * @return
 */
QList<WaitForList> DBHandler::queryWithReturnWaitForListList(QString statement)
{
    qDebug() << "DBHandler -> queryWithReturnWaitForListList(" << statement << ");";


    WaitForList * WaitFor;

    QList<WaitForList> WaitFors;
    QSqlQuery query(db);
    query.exec(statement);
    qDebug() << "statement was: " << query.isActive();
    while (query.next())
    {
        qDebug() << "adding WaitFor...";
        int id = query.value(0).toInt();
        QString description = query.value(1).toString();
        bool done = (query.value(2).toInt() == 0) ? false : true;
        int subjID = query.value(3).toInt();
        WaitFor=new WaitForList (id, description, done, subjID);
        WaitFors.append(*WaitFor);
    }
    return WaitFors;
}





/**
 * @brief DBHandler::tagsFromNote
 * @return List of all Tags that were added to the given note_id
 */
QList<QString> DBHandler::tagsFromNote(int noteid)
{
    qDebug() << "DBHandler -> tagsFromNote, noteID:" << QString::number(noteid);
    QList<QString> tags;
    QSqlQuery query(db);
    QString command = "SELECT tagname FROM tag WHERE (pk_id in (SELECT fk_tag FROM noteHasTag WHERE (fk_note = " + QString::number(noteid) + ")))";
    query.exec(command);
    qDebug() << "tags:";
    while (query.next())
    {
        QString tag = query.value(0).toString();
        tags.append(tag);
        qDebug() << tag;
    }
    return tags;
}

/**
 * @brief DBHandler::attachementsFromNote
 * @return List of all Attachements that were added to the given note_id
 */
QList<QString> DBHandler::attachementsFromNote(int noteid)
{
    QList<QString> attachs;
    QSqlQuery query(db);
    query.exec("SELECT filename FROM attachement WHERE pk_id in (SELECT fk_attachement FROM noteHasAttachement WHERE fk_note = " + QString::number(noteid) +")");
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
    qDebug()  << query.isActive();
    while (query.next())
    {
        int id = query.value(0).toInt();
        QList<WrittenNote> notes = queryWithReturnNoteList("SELECT * FROM note WHERE (fk_schoolSubject = " + QString::number(id) + ")");
        QString subject_name =  query.value(1).toString();
        pSubject =  new Subject(id, notes, subject_name);
        subjects.append(*pSubject);
    }
    return subjects;
}








QList<Subject> DBHandler::getAllSubjects()
{
    QList<Subject> result;
    return queryWithReturnSubjectList("SELECT * FROM schoolSubject");
}

QList<WrittenNote> DBHandler::getAllNotesFromSubject(int subjectID)
{
    QList<WrittenNote> result;

    //get


    return result;
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
int DBHandler::insertWrittenNote(WrittenNote note)
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
    qDebug() << "NOTE ID selected is:" << QString::number(noteId);
    note.setNoteID(noteId);
    qDebug() << "NOTE ID in programm is:" << QString::number(note.getId());

    //insert Tags
    for (QString tag :  note.getTags())
    {
        insertWrittenTagToNote(noteId, tag);
    }

    //insert Attachments
    for (QString attachement : note.getAttachement())
    {
        int attachementID = insertAttachementAndReturnId(attachement);
        //insert to noteHasAttachement-table
        qDebug() << "" << "INSERT INTO noteHasAttachement (fk_note, fk_attachement) VALUES (" + QString::number(noteId) + ", " + QString::number(attachementID) + ")";
        queryNoReturn("INSERT INTO noteHasAttachement (fk_note, fk_attachement) VALUES (" + QString::number(noteId) + ", " + QString::number(attachementID) + ")");
    }
    qDebug() << "Note insertion was: " << (noteId != -1);
    return noteId;
}

int DBHandler::insertWaitForandReturnId(WaitForList WaitForItem)
{
    int id  = insertAndReturnID("INSERT INTO waitfor (description, done, fk_schoolSubject) VALUES ('" +  WaitForItem.getDescription() + "', " + QString::number(WaitForItem.getDone() > 0 ? 1 : 0) + "," + QString::number(WaitForItem.getSubjectID()) + ")");
    return id;
}

void DBHandler::updateWaitFor(WaitForList WaitForItem)
{
    queryNoReturn("UPDATE waitfor SET description = '" + WaitForItem.getDescription() + "' WHERE (pk_id = " + QString::number(WaitForItem.getID()) +")");
    queryNoReturn("UPDATE waitfor SET done = '" + QString::number(WaitForItem.getDone() > 0 ? 1 : 0) + "' WHERE (pk_id = " + QString::number(WaitForItem.getID()) +")");
}

void DBHandler::deleteWaitFor(WaitForList WaitforItem)
{
    qDebug() << "====================((((((=============================";
    qDebug() << queryNoReturn("DELETE FROM waitfor where (pk_id = " + QString::number(WaitforItem.getID()) + ")");
}

int DBHandler::insertTODOandReturnId(ToDoItem todoItem)
{
    int id  = insertAndReturnID("INSERT INTO todo (description, deadline, done, fk_schoolSubject) VALUES ('" +  todoItem.getDescription() + "', " + QString::number(todoItem.getDeadline().toMSecsSinceEpoch()) + ", " + QString::number(todoItem.getDone() > 0 ? 1 : 0) + "," + QString::number(todoItem.getSubjectID()) + ")");
    return id;
}


void DBHandler::updateTODO(ToDoItem todoItem)
{
    queryNoReturn("UPDATE todo SET description = '" + todoItem.getDescription() + "' WHERE (pk_id = " + QString::number(todoItem.getID()) +")");
    queryNoReturn("UPDATE todo SET deadline = '" + QString::number(todoItem.getDeadline().currentMSecsSinceEpoch()) + "' WHERE (pk_id = " + QString::number(todoItem.getID()) +")");
    queryNoReturn("UPDATE todo SET done = '" + QString::number(todoItem.getDone() > 0 ? 1 : 0) + "' WHERE (pk_id = " + QString::number(todoItem.getID()) +")");
    //queryNoReturn("UPDATE todo SET description = '" + todoItem.getDescription() + "' WHERE (pk_id = " + QString::number(todoItem.getID()) +")");
}

void DBHandler::deleteToDo(ToDoItem todoItem)
{
    queryNoReturn("DELETE FROM todo where (pk_id = " + QString::number(todoItem.getID()) + ")");
}

void DBHandler::insertWrittenTagToNote(int noteID, QString tag)
{
    qDebug() << "DBHandler::insertWrittenTagToNote"  << " params: " << QString::number(noteID) << ", " << tag;
    int tagId = insertTagAndReturnId(tag);
    queryNoReturn("INSERT INTO noteHasTag(fk_note, fk_tag) VALUES (" + QString::number(noteID) + ", " + QString::number(tagId) + ")");
}

void DBHandler::insertAttachementToNote(int noteId, QString attachement)
{
    qDebug() << "DBHandler::insertAttachementToNote"  << " params: " << QString::number(noteId) << ", " << attachement;
    int attachementID = insertAttachementAndReturnId(attachement);
    queryNoReturn("INSERT INTO noteHasAttachement(fk_note, fk_attachement) VALUES (" + QString::number(noteId) + ", " + QString::number(attachementID) + ")");
}



/**
 * @brief DBHandler::updateWrittenNote PROBLEM: NICHT MEHR VERWENDETE TAGS/Attachments BLEIBEN IN DER DATENBANK !!!!!!!!!!!FIX!!!!!!!!!!!!! -> Methode deleteUnused aufrufen bei beendigung des Programms
 * @param note: The updated Writtennote
 * @param fk_schoolSubject
 * @return
 */
bool DBHandler::updateWrittenNote(WrittenNote note)
{
    qDebug() << "DBHandler->updateWrittenNote(" << note.toString() << ")";


    int noteId = note.getId();
    if(noteId == -1){
        return false;
    }
    //insert Tags

    queryNoReturn("DELETE FROM noteHasTag where (fk_note = " + QString::number(noteId) + ")");
    for (QString tempTag : note.getTags())
    {
        insertWrittenTagToNote(note.getId(), tempTag);
    }

    //insert Attachments
    queryNoReturn("DELETE FROM noteHasAttachement where fk_note = " + QString::number(noteId) + ")");
    for (QString attachement : note.getAttachement())
    {
        insertAttachementToNote(note.getId(), attachement);
    }

    //content
    queryNoReturn("UPDATE note SET content = '" + note.getContent() + "' WHERE (pk_id = " + QString::number(note.getId()) +")");


    //Date:
    queryNoReturn("UPDATE note SET ts = " + note.getTimestamp().toString() + " WHERE (pk_id = " + QString::number(note.getId()) +")");

    return true;
}


/**
 * @brief DBHandler::insertTagAndReturnId
 * @param tag
 * @return inserts tag and returns id of tag, if tag is already in the database, it returns the id of it.
 */
int DBHandler::insertTagAndReturnId(QString tag)
{
    qDebug() << "insertTagAndReturnId(" << tag << ")";
    int tagId= -1;
    if(select("COUNT(tagname)", "tag", "where (tagname = '"+ tag+"')").toInt() < 1)
    {
        tagId =  insertAndReturnID("INSERT INTO tag(tagname) VALUES('"+tag+"')");
        qDebug() << "tag " << tag << "was inserted at" << tagId;
    }else
    {
        tagId =  select("pk_id", "tag", "where (tagname = '"+ tag+"')").toInt();
        qDebug() << "tag " << tag << "allready exists at" << tagId;
    }
    return tagId;
}





/**
 * @brief DBHandler::insertAttechementAndReturnId
 * @param attachementPath
 * @return pk_id in database of the inserted Attachement.
 *
 *
 */

int DBHandler::insertAttachementAndReturnId(QString attachementPath)
{
    qDebug() << "DBHandler -> insertAttechementAndReturnId(" << attachementPath <<")";

    int attatchmentId =  insertAndReturnID("INSERT INTO attachement(filename) VALUES('"+attachementPath+"')");
    if (attatchmentId = -1){
        attatchmentId = select("pk_id", "attachement", "filename = '" + attachementPath + "'").toInt();
    }

    qDebug() << "Attatchement from " << attachementPath << " inserted at " << attatchmentId;

    //copying files would require more debugging and work. since time is short, the easy way will be good enough for now.

    /*
    //copy File to Folder
    QString destPath = resourcesFolder + QDir::separator() + QString::number(attatchmentId) + "_" + name;
    QFile::copy(attachementPath, destPath);
    qDebug() << "Attatchement copied from " << attachementPath << " to " << destPath;

    */

    return attatchmentId;
}


void DBHandler::removeAttachement(WrittenNote note, QString attachmentpath)
{
    if(select("count(" + attachmentpath +")", "attachement", "filename = " + attachmentpath).toInt() > 0){
        queryNoReturn("DELETE FROM attachement WHERE (filename = " + attachmentpath + ")");
    }


    //QFile::remove(attachmentpath);
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
        where = "WHERE (" + where + ")";
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
 *
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
    query.exec("Select pk_id from attachement");
    while (query.next()) {
        tags.append(query.value(0).Int);
    }
    for(int i = 0; i < tags.length(); i ++)
    {
        if(select("COUNT(pk_id)", "noteHasAttachement", "fk_Tag = '"+ QString::number(tags[i]) +"'") <= 0)
        {
            query.exec("delete * from attachement where (pk_id = " + QString::number(tags[i]) + ")");
        }
    }
}

void DBHandler::deleteWrittenNote(int id)
{
    queryNoReturn("delete * from WrittenNote where (pk_id = " + QString::number(id) + ")");
    queryNoReturn("delete * from noteHasTag where (fk_note = " + QString::number(id) + ")");
    queryNoReturn("delete * from noteHasAttachement where (fk_note = " + QString::number(id) + ")");
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

