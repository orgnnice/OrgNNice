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

    //dbhandler konstructor
    ToDoItem(int id, QString description, QDateTime deadline, bool done, int subject_id);

    QString getDescription();
    QDateTime getDeadline();
    int getSubjectID();
    bool getDone();
    int getID();




    void updateToDoItem();
    void deleteToDoItem();

    void setDescription(QString description);
    void setDeadline(QDateTime deadline);
    void setDone(bool done);

    QString toString();

};

#endif // TODOITEM_H
