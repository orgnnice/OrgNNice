#include "todo.h"
#include "ui_todo.h"
#include "qdebug.h"

toDo::toDo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::toDo)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
}

toDo::~toDo()
{
    delete ui;
}

void toDo::on_addnew_clicked()
{
    add_toDo = new new_toDo();
    add_toDo->show();
}

void toDo::setItemList(QList<ToDoItem> current)
{
    this->toItems = current;
    qDebug() << toItems.length();
    for(int i=0;i<toItems.length();i++)
    {
        qDebug() << "Aufgabe: " << toItems[i].getDescription();

        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(7);

        QFont font1;
        font1.setPointSize(11);

        QLabel *label_date = new QLabel(toItems[i].getDeadline().toString());
        label_date->setMinimumSize(QSize(0, 50));
        label_date->setMaximumSize(QSize(16777215, 50));
        label_date->setFont(font1);

        horizontalLayout->addWidget(label_date, 0, Qt::AlignTop);

        QLabel *label_desc = new QLabel(toItems[i].getDescription());
        label_desc->setMinimumSize(QSize(450, 50));
        label_desc->setMaximumSize(QSize(16777215, 50));
        label_desc->setFont(font1);

        horizontalLayout->addWidget(label_desc, 0, Qt::AlignTop);

        QLabel *label_subj = new QLabel("Fachname");
        label_subj->setMinimumSize(QSize(100, 50));
        label_subj->setMaximumSize(QSize(16777215, 50));
        label_subj->setFont(font1);

        horizontalLayout->addWidget(label_subj, 0, Qt::AlignTop);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(100, 50));
        checkBox->setMaximumSize(QSize(100, 50));
        checkBox->setStyleSheet(QStringLiteral("padding-left: 25px;"));

        horizontalLayout->addWidget(checkBox, 0, Qt::AlignTop);

        ui->verticalLayout_2->setSpacing(6);
        ui->verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        ui->verticalLayout_2->setContentsMargins(0, 0, 0, 0);

        ui->verticalLayout_2->addLayout(horizontalLayout);
    }
}
