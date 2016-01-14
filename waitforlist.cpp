#include "waitforlist.h"
#include "dbhandler.h"
#include "main.h"

WaitForList::WaitForList()
{

}


/**
 * @brief WaitForList::WaitForList to be called to insert a new WaitFor
 * @param subject_name
 * @param description
 * @param done
 */
WaitForList::WaitForList(QString subject_name, QString description, bool done)
{
    this->subject_id = pDBh->select("pk_id", "SchoolSubject", "name='" + subject_name + "'").replace('"', "").toInt();
    this->description = description;
    this->done = done;
    this->id = pDBh->insertWaitForandReturnId(*this);
}


/**
 * @brief WaitForList::WaitForList To be called by DB Handler
 * @param id
 * @param description
 * @param done
 * @param subject_id
 */
WaitForList::WaitForList(int id, QString description, bool done, int subject_id)
{
    qDebug() << "WaitForList::WaitForList(int id, QString description, bool done, int subject_id)";
    this->subject_id = subject_id;
    this->description = description;
    this->done = done;
    this->id = id;
}


void WaitForList::updateWaitFor()
{
    pDBh->updateWaitFor(*this);
}

void WaitForList::deleteWaitFor()
{
    pDBh->deleteWaitFor(*this);
}

QString WaitForList::toString()
{
    QString result = "TODO: ";
    result += this->description + " | Done: " + QString::number((this->getDone() > 0 ? 1 : 0)) + " | Fachname: " + QString::number(this->subject_id) + " | ID: " + QString::number(this->id);
    return result;
}


int WaitForList::getID()
{
    return this->id;
}

int WaitForList::getSubjectID()
{
    return this->subject_id;
}

bool WaitForList::getDone()
{
    return this->done;
}

QString WaitForList::getDescription()
{
    return this->description;
}


void WaitForList::setDescription(QString description)
{
    this->description = description;
}

void WaitForList::setDone(bool done)
{
    this->done = done;
}


