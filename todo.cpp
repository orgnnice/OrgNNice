#include "todo.h"
#include "ui_todo.h"
#include "qdebug.h"
#include "dbhandler.h"
#include "main.h"
#include "qcheckbox.h"

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
        label_date->setMinimumSize(QSize(120, 25));
        label_date->setMaximumSize(QSize(120 , 25));
        label_date->setFont(font1);

        horizontalLayout->addWidget(label_date, 0, Qt::AlignVCenter);

        QLabel *label_desc = new QLabel(toItems[i].getDescription());
        label_desc->setMinimumSize(QSize(310, 25));
        label_desc->setMaximumSize(QSize(16777215, 16777215));
        label_desc->setFont(font1);

        horizontalLayout->addWidget(label_desc, 0, Qt::AlignVCenter);
        int a = toItems[i].getSubjectID();
        qDebug() << "Name of Subject: " << pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a));
        //QLabel *label_subj = new QLabel(pDBh->select("subject_name", "SchoolSubject", "id='" + toItems[i].getSubjectID() + "'"));
        QLabel *label_subj = new QLabel(pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a)));
        label_subj->setMinimumSize(QSize(145, 25));
        label_subj->setMaximumSize(QSize(145, 25));
        label_subj->setFont(font1);

        horizontalLayout->addWidget(label_subj, 0, Qt::AlignVCenter);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(60, 25));
        checkBox->setMaximumSize(QSize(60, 25));
        checkBox->setStyleSheet(QStringLiteral("padding-left: 25px;"));

        horizontalLayout->addWidget(checkBox, 0, Qt::AlignVCenter);

        ui->verticalLayout_2->addLayout(horizontalLayout);
    }
}
