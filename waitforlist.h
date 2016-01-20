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
    WaitForList(int id, QString description, bool done, int subject_id);


    QString getDescription();
    int getSubjectID();
    bool getDone();
    int getID();

    void updateWaitFor();
    void deleteWaitFor();

    void setDescription(QString description);
    void setDone(bool done);
    void setSubjectID(int id);

    QString toString();
};

#endif // WAITFORLIST_H
