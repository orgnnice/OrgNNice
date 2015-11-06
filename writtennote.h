#ifndef WRITTENNOTE_H
#define WRITTENNOTE_H

#include <QString>
#include <QDateTime>
#include <attachement.h>


class WrittenNote
{
private:
    int id;
    QString text;
    QList<Attachement> attachements;
    QList<QString> tags;
    QString path;
    QDateTime timestamp;

public:
    void setDate(QDateTime);
    void saveWrittenNote(QString);
    void addAttachement(Attachement);
    void addTag(QString newTag);
    QDateTime getTimestamp();
    QList<QString> getTags();
    WrittenNote();
};

#endif // WRITTENNOTE_H
