#ifndef TODOITEM_H
#define TODOITEM_H

#include <qdatetime.h>



class ToDoItem
{

private:
    int id;
    QString fach_name;
    QString beschreibung;
    QDateTime deadline;

    bool done;

public:
    ToDoItem();
    ToDoItem(QString fach_name, QString beschreibung, QDateTime deadline, bool done);


    QString getFach_name();
    QString getBeschreibung();
    QDateTime getDeadline();

    void setFach_name(QString name);
    void setBeschreibung(QString beschreibung);
    void setDeadline(QDateTime deadline);
    void setDone(bool done);



};

#endif // TODOITEM_H
