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
ToDoItem::ToDoItem(int fach_id, QString beschreibung, QDateTime deadline, bool done)
{
    this->fach_id = fach_id;
    this->beschreibung = beschreibung;
    this->deadline = deadline;
    this->done = done;
    this->id = pDBh->insertTODOandReturnId(*this);
}



QString ToDoItem::toString()
{
    QString result = "TODO: ";
    result += this->beschreibung + " | Deadline: " + this->deadline.toString() + " | Done: " + this->done + " | Fachname: " + this->fach_id + " | ID: " + QString::number(this->id);
    return result;
}



QString ToDoItem::getFach_name()
{

}

int ToDoItem::getFach_id()
{
    return this->fach_id;
}


QString ToDoItem::getBeschreibung()
{
    return this->beschreibung;
}

QDateTime ToDoItem::getDeadline()
{
    return this->deadline;
}


void ToDoItem::setBeschreibung(QString beschreibung)
{

}

void ToDoItem::setDeadline(QDateTime deadline)
{

}

void ToDoItem::setDone(bool done)
{

}

