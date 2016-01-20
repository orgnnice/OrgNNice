#include "todoitem.h"
#include <dbhandler.h>
#include "main.h"

ToDoItem::ToDoItem()
{

}




/**
 * @brief ToDoItem::ToDoItem
 * @param fach_name
 * @param beschreibung
 * @param deadline
 * @param done
 */
ToDoItem::ToDoItem(QString subject_name, QString description, QDateTime deadline, bool done)
{
    this->subject_id = pDBh->select("pk_id", "SchoolSubject", "name='" + subject_name + "'").replace('"', "").toInt();
    this->description = description;
    this->deadline = deadline;
    this->done = done;
    qDebug() << "DBHandler::insertTODOandReturnId"  << this->toString();
    this->id = pDBh->insertTODOandReturnId(*this);
}

/**
 * @brief ToDoItem::ToDoItem to be called by DBHandler to select Todos from the database
 * @param subject_id
 * @param description
 * @param deadline
 * @param done
 */
ToDoItem::ToDoItem(int id, QString description, QDateTime deadline, bool done, int subject_id)
{
    this->subject_id = subject_id;
    this->description = description;
    this->deadline = deadline;
    this->done = done;
    this->id = id;
}


void ToDoItem::updateToDoItem()
{

    pDBh->updateTODO(*this);
}

void ToDoItem::deleteToDoItem()
{
    pDBh->deleteToDo(*this);
}

void ToDoItem::setSubjectID(int id)
{
    this->subject_id = id;
}

QString ToDoItem::toString()
{
    QString result = "TODO: ";
    result += this->description + " | Deadline: " + this->deadline.toString() + " | Done: " + QString::number((this->getDone() > 0 ? 1 : 0)) + " | Fachname: " + QString::number(this->subject_id) + " | ID: " + QString::number(this->id);
    return result;
}


int ToDoItem::getID()
{
    return this->id;
}

int ToDoItem::getSubjectID()
{
    return this->subject_id;
}

bool ToDoItem::getDone()
{
    return this->done;
}

QString ToDoItem::getDescription()
{
    return this->description;
}

QDateTime ToDoItem::getDeadline()
{
    return this->deadline;
}


void ToDoItem::setDescription(QString description)
{
    this->description = description;
}

void ToDoItem::setDeadline(QDateTime deadline)
{
    this->deadline = deadline;
}

void ToDoItem::setDone(bool done)
{
    this->done = done;
}

