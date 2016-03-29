#include "waitfor.h"
#include "ui_waitfor.h"
#include "qcheckbox.h"
#include "dbhandler.h"
#include "main.h"
#include "subject.h"
#include "mainwindow.h"
#include "QShortcut"

WaitFor::WaitFor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitFor)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");

    QShortcut *shortcut = new QShortcut(QKeySequence(tr("Ctrl+n")),
                             this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_addnew_waitfor_clicked()));
}

WaitFor::~WaitFor()
{
    delete ui;
}

void WaitFor::on_addnew_waitfor_clicked()
{
    add_waitFor = new New_WaitFor(this);
    add_waitFor->show();
}

void WaitFor::setItemList(QList<WaitForList> current)
{
    ui->addnew_waitfor->setStyleSheet("#addnew_waitfor{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#addnew_waitfor:hover{color: #000; border: 1px solid #446CB3;}");
    ui->addnew_waitfor->setMinimumSize(QSize(30, 30));
    ui->addnew_waitfor->setMaximumSize(QSize(30, 30));

    this->waitItems = current;
    for(int i=0;i<waitItems.length();i++)
    {
        QSignalMapper* checkedMapper = new QSignalMapper(this);
        QSignalMapper* deleteMapper = new QSignalMapper(this);

        QWidget *fixedWidget = new QWidget;
        QHBoxLayout *horizontalLayout = new QHBoxLayout(fixedWidget);
        horizontalLayout->setSpacing(7);
        fixedWidget->setFixedHeight(35);

        QFont font1;
        font1.setPointSize(9);

        QLabel *label_desc = new QLabel(waitItems[i].getDescription());
        label_desc->setMinimumSize(QSize(390, 25));
        label_desc->setMaximumSize(QSize(16777215, 25));
        label_desc->setFont(font1);
        horizontalLayout->addWidget(label_desc, 0, Qt::AlignTop);

        int a = waitItems[i].getSubjectID();
        //QString z = pDBh->select("name", "SchoolSubject", "pk_id='" + a + "'").replace('"',"");
        //QLabel *label_subj = new QLabel(pDBh->select("subject_name", "SchoolSubject", "id='" + toItems[i].getSubjectID() + "'"));
        QLabel *label_subj = new QLabel(pDBh->select("name", "SchoolSubject", "pk_id=" + QString::number(a)));
        label_subj->setMinimumSize(QSize(160, 25));
        label_subj->setMaximumSize(QSize(160, 25));
        label_subj->setFont(font1);
        horizontalLayout->addWidget(label_subj, 0, Qt::AlignTop);

        QCheckBox *checkBox = new QCheckBox();
        checkBox->setMinimumSize(QSize(25, 25));
        checkBox->setMaximumSize(QSize(25, 25));
        checkBox->setChecked(waitItems[i].getDone());
        horizontalLayout->addWidget(checkBox, 0, Qt::AlignTop);

        QPushButton *pButton = new QPushButton();
        QPixmap pixmap = QPixmap (":/images/icons/icon_waste_white.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setIconSize(QSize(20, 20));
        pButton->setObjectName(QStringLiteral("deleteButton"));
        pButton->setMinimumSize(QSize(25, 25));
        pButton->setMaximumSize(QSize(25, 25));
        pButton->setStyleSheet("#deleteButton{background-color: #F22613; color: #23121C; border: 1px solid #000; border-radius: 2px;}"
                               "#deleteButton:hover{color: #000; border: 1px solid #888;}");
        horizontalLayout->addWidget(pButton, 0, Qt::AlignTop);

        ui->verticalLayout_2->addWidget(fixedWidget, 0, Qt::AlignTop);

        QFrame *line_2 = new QFrame();
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        ui->verticalLayout_2->addWidget(line_2);

        connect(checkBox, SIGNAL(clicked()), checkedMapper, SLOT(map()));
        checkedMapper->setMapping(checkBox, i);
        connect(checkedMapper, SIGNAL(mapped(int)), this, SLOT(checkWaitFor(int)));

        connect(pButton, SIGNAL(clicked()), deleteMapper, SLOT(map()));
        deleteMapper->setMapping(pButton, i);
        connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(deleteWaitFor(int)));
    }
}

void WaitFor::checkWaitFor(int item){
    if(waitItems[item].getDone()) {
        waitItems[item].setDone(false);
        qDebug() << waitItems[item].getDone();
    }else{
        waitItems[item].setDone(true);
        qDebug() << waitItems[item].getDone();
    }
    waitItems[item].updateWaitFor();
    this->update();
}

void WaitFor::deleteWaitFor(int item){
    waitItems[item].deleteWaitFor();
    this->update();
}

void WaitFor::clearLayout(QLayout *layout){
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void WaitFor::update()
{
qDebug() << "Started Update";
qDebug() << "Name des ersten Subject";
QList <WaitForList> allwfs =  pDBh->queryWithReturnWaitForListList("SELECT * FROM waitfor");
this->clearLayout(ui->verticalLayout_2);
this->setItemList(allwfs);
MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
// check parent is not null
parent->updateLists();
}
