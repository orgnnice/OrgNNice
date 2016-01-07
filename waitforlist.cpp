#include "waitforlist.h"
#include "dbhandler.h"
#include "main.h"

WaitForList::WaitForList()
{

}



WaitForList::WaitForList(QString subject_name, QString description, bool done)
{
    this->subject_id = pDBh->select("pk_id", "SchoolSubject", "name='" + subject_name + "'").replace('"', "").toInt();
    this->description = description;
    this->done = done;
    this->id = pDBh->insertWaitForandReturnId(*this);
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


