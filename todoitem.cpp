#include "todoitem.h"

ToDoItem::ToDoItem()
{

}


//<todo> dbhandler is missing (insertTODOandReturnId or something like that).

/**
 * @brief ToDoItem::ToDoItem
 * @param fach_name
 * @param beschreibung
 * @param deadline
 * @param done
 */
ToDoItem::ToDoItem(QString fach_name, QString beschreibung, QDateTime deadline, bool done)
{
    this->fach_name = fach_name;
    this->beschreibung = beschreibung;
    this->deadline = deadline;
    this->done = done;

}

QString ToDoItem::getFach_name()
{

}

QString ToDoItem::getBeschreibung()
{

}

QDateTime ToDoItem::getDeadline()
{

}

void ToDoItem::setFach_name(QString name)
{

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

