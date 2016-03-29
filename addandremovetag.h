#ifndef ADDANDREMOVETAG_H
#define ADDANDREMOVETAG_H

#include <QDialog>
#include <writtennote.h>

namespace Ui {
class AddAndRemoveTag;
}

class AddAndRemoveTag : public QDialog
{
    Q_OBJECT

public:
    explicit AddAndRemoveTag(QWidget *parent = 0);
    ~AddAndRemoveTag();
    WrittenNote selwr;

public slots:
    void setWrittenNote(WrittenNote cur);

    void clearLayout(QLayout *layout);

    void update();
private slots:
    void on_pushButton_clicked();
    void deleteTag(QString seltag);

private:
    Ui::AddAndRemoveTag *ui;
};

#endif // ADDANDREMOVETAG_H
