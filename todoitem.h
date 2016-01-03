#ifndef TODOITEM_H
#define TODOITEM_H

#include <qdatetime.h>
#include <dbhandler.h>

class DBHandler;

class ToDoItem
{

private:
    int id = -1;
    int subject_id;
    QString description;
    QDateTime deadline;
    bool done;

public:
    ToDoItem();
    ToDoItem(QString subject_name, QString description, QDateTime deadline, bool done);


    QString getDescription();
    QDateTime getDeadline();
    int getSubjectID();
    bool getDone();

    void setDescription(QString description);
    void setDeadline(QDateTime deadline);
    void setDone(bool done);

    QString toString();
    int BooleantoInteger(bool complete);

};

#endif // TODOITEM_H
