#ifndef WAITFORLIST_H
#define WAITFORLIST_H

#include <dbhandler.h>

class DBHandler;

class WaitForList
{

private:
    int id = -1;
    int subject_id;
    QString description;
    bool done;

public:
    WaitForList();
    WaitForList(QString subject_name, QString description, bool done);

    QString getDescription();
    int getSubjectID();
    bool getDone();
    int getID();

    void updateWaitFor();
    void deleteWaitFor();

    void setDescription(QString description);
    void setDone(bool done);

    QString toString();
};

#endif // WAITFORLIST_H
