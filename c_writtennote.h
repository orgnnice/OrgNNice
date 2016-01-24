#ifndef C_WRITTENNOTE_H
#define C_WRITTENNOTE_H

#include <QDialog>

namespace Ui {
class C_WrittenNote;
}

class C_WrittenNote : public QDialog
{
    Q_OBJECT

public:
    explicit C_WrittenNote(QWidget *parent = 0);
    ~C_WrittenNote();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::C_WrittenNote *ui;
};

#endif // C_WRITTENNOTE_H
