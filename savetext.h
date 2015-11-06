#ifndef SAVETEXT_H
#define SAVETEXT_H

#include <QMainWindow>

namespace Ui {
class saveText;
}

class saveText : public QMainWindow
{
    Q_OBJECT

public:
    explicit saveText(QWidget *parent = 0);
    ~saveText();

private:
    Ui::saveText *ui;

private slots:
    void on_SaveButton_clicked();
};

#endif // SAVETEXT_H
