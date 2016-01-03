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
    qDebug() << "==========================================================" << this->subject_id;
    this->description = description;
    this->deadline = deadline;
    this->done = done;
    qDebug() << "DBHandler::insertTODOandReturnId"  << this->toString();
    this->id = pDBh->insertTODOandReturnId(*this);
}



QString ToDoItem::toString()
{
    QString result = "TODO: ";
    result += this->description + " | Deadline: " + this->deadline.toString() + " | Done: " + QString::number((this->getDone() > 0 ? 1 : 0)) + " | Fachname: " + QString::number(this->subject_id) + " | ID: " + QString::number(this->id);
    return result;
}

int ToDoItem::BooleantoInteger(bool complete)
{
    switch(complete)
    {
    case true: return 1;

    case false: return 0;
    }
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


void ToDoItem::setDescription(QString beschreibung)
{

}

void ToDoItem::setDeadline(QDateTime deadline)
{

}

void ToDoItem::setDone(bool done)
{

}

