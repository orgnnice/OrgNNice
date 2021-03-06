#ifndef SUBJECT_DETAIL_H
#define SUBJECT_DETAIL_H

#include <QMainWindow>
#include "mrichtextedit.h"
#include "subject.h"
#include "c_writtennote.h"
#include "searchdialog.h"

namespace Ui {
class subject_detail;
}

class subject_detail : public QMainWindow
{
    Q_OBJECT

public:
    explicit subject_detail(QWidget *parent = 0);
    ~subject_detail();
    Subject subdet;
    QList<WrittenNote> noteList;

public slots:
    void setSubDet(Subject cur);
    void textDet(int list);
    void update();
    void deleteWrittenNote(int item);
    void newtd(QString name);

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_addnew_clicked();

    void on_pushButton_clicked();

    void on_addnew_2_clicked();

private:
    Ui::subject_detail *ui;
    MRichTextEdit *rte;
    C_WrittenNote *newWrittenNote;
    SearchDialog *opensearch;
};

#endif // SUBJECT_DETAIL_H
