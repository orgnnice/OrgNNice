#ifndef WRITTENNOTE_H
#define WRITTENNOTE_H

#include <QString>
#include <QDateTime>


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
    void addTag(tag newTag);
    WrittenNote();
};

#endif // WRITTENNOTE_H
