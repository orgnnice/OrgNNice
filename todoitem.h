#ifndef TODOITEM_H
#define TODOITEM_H

#include <qdatetime.h>
#include <dbhandler.h>

class DBHandler;

class ToDoItem
{

private:
    int id = -1;
    int fach_id;
    QString beschreibung;
    QDateTime deadline;

    bool done;

public:
    ToDoItem();
    ToDoItem(int fach_name, QString beschreibung, QDateTime deadline, bool done);


    QString getFach_name();
    QString getBeschreibung();
    QDateTime getDeadline();
    int getFach_id();

    void setBeschreibung(QString beschreibung);
    void setDeadline(QDateTime deadline);
    void setDone(bool done);

    QString toString();


};

#endif // TODOITEM_H
