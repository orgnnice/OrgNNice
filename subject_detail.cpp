#include "subject_detail.h"
#include "ui_subject_detail.h"
#include <QDebug>
#include <QDialog>
#include <QSignalMapper>
#include "main.h"
#include <QList>
#include "subject.h"
#include "mainwindow.h"
#include "qshortcut.h"

subject_detail::subject_detail(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::subject_detail)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");

    QShortcut *shortcut = new QShortcut(QKeySequence(tr("Ctrl+n")),
                             this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_addnew_2_clicked()));
}

subject_detail::~subject_detail()
{
    delete ui;
}

void subject_detail::setSubDet(Subject cur)
{
    this->subdet = cur;
    qDebug() << "Subjectname: " << subdet.getName();
    qDebug() << "Anzahl der Mitschriften:" << subdet.getWrittenNotesSize();
    ui->label_2->setText(subdet.getName());
    ui->label_3->setText(QString::number(subdet.getWrittenNotesSize()) + " Mitschriften");

    ui->addnew_2->setStyleSheet("#addnew_2{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#addnew_2:hover{color: #000; border: 1px solid #446CB3;}");

    ui->pushButton_2->setStyleSheet("#pushButton_2{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                              "#pushButton_2:hover{color: #000; border: 1px solid #446CB3;}");

    //QList<Subject> all = pDBh->queryWithReturnSubjectList("SELECT * FROM schoolsubject");
    int a = 2;
    int line = 0;
    int col = 0;
    noteList = subdet.getWrittenNotes();

    for(int i=0;i<subdet.getWrittenNotesSize();i++){
        QFont font1;
        font1.setPointSize(12);

        QPushButton *pButton = new QPushButton(ui->scrollAreaWidgetContents);
        QSignalMapper* signalMapper = new QSignalMapper(this);
        QSignalMapper* deleteMapper = new QSignalMapper(this);
        QPixmap pixmap = QPixmap (":/images/icons/icon_writtennote_with_text.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setObjectName(QStringLiteral("mitschriftButton"));
        pButton->setIconSize(QSize(70, 100));
        pButton->setAutoExclusive(false);
        pButton->setMinimumWidth(80);
        pButton->setMinimumHeight(110);
        pButton->setStyleSheet("#mitschriftButton{background-color: #fff; color: #23121C; border: 1px solid #446CB3; border-radius: 2px;}"
                                      "#mitschriftButton:hover{background-color: #446CB3; border: 1px solid #fff;}");
        qDebug() << noteList[i].getTimestamp();
        QLabel *labelFilename = new QLabel(noteList[i].getTimestamp().toString("dd.MM.yyyy"));
        labelFilename->setStyleSheet(QStringLiteral("font-family: 'Yu Gothic UI';"));
        labelFilename->setFont(font1);
        QSpacerItem *vSpacer;
        vSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QPushButton *deleteButton = new QPushButton("");
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        QPixmap pixmapDelete = QPixmap (":/images/icons/icon_x.png");
        deleteButton->setIcon(QIcon(pixmapDelete));
        deleteButton->setIconSize(QSize(15, 15));
        deleteButton->setStyleSheet("#deleteButton{background-color: transparent; border: 0px; border-radius: 2px;}"
                                                  "#deleteButton:hover{color: #F22613; border: 1px solid #830000;}");
        deleteButton->setMinimumSize(QSize(20, 20));
        deleteButton->setMaximumSize(QSize(20, 20));

        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(pButton, 0, Qt::AlignHCenter);
        verticalLayout->addWidget(labelFilename,0, Qt::AlignCenter);
        verticalLayout->addWidget(deleteButton,0, Qt::AlignCenter);
        verticalLayout->addItem(vSpacer);
        if(i > a){
            a += 3;
            line++;
            col = 0;
        }
        //ui->gridLayout->addLayout(verticalLayout,line,col,1,1);
        ui->gridLayout->addLayout(verticalLayout,line,col,1,1);
        col++;
        connect(pButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(pButton, i);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(textDet(int)));

        connect(deleteButton, SIGNAL(clicked()), deleteMapper, SLOT(map()));
        deleteMapper->setMapping(deleteButton, i);
        connect(deleteMapper, SIGNAL(mapped(int)), this, SLOT(deleteWrittenNote(int)));
    }
}

void subject_detail::textDet(int index){
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Org'n'Nice");
    rte = new MRichTextEdit(dialog); // Be sure to destroy you window somewhere
    rte->setText(noteList[index].getContent().replace("^", "'"));
    rte->setNote(noteList[index]);
    rte->cur = subdet;
    dialog->show();
}

void subject_detail::deleteWrittenNote(int item){
    noteList[item].deleteWrittenNote();
    this->update();
}

void subject_detail::newtd(QString name)
{
    MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
    // check parent is not null
    parent->new_toDo(name);
}

void subject_detail::on_pushButton_2_clicked()
{
    opensearch = new SearchDialog(this);
    opensearch->selsub = subdet;
    opensearch->show();
}

void subject_detail::on_addnew_2_clicked()
{
    newWrittenNote = new C_WrittenNote(this);
    newWrittenNote->setSubject(subdet);// Be sure to destroy you window somewhere
    newWrittenNote->show();
}

void subject_detail::update()
{
qDebug() << "Started Update";
qDebug() << "Name des ersten Subject";
subdet.updateSubject();
while(ui->gridLayout->count() > 0) {
            QLayout* layout = ui->gridLayout->itemAt(0)->layout();

            QLayoutItem * item;
            QLayout * sublayout;
            QWidget * widget;
            while ((item = layout->takeAt(0))) {
                if ((sublayout = item->layout()) != 0) {/* do the same for sublayout*/}
                else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
                else {delete item;}
            }
            // then finally
            delete layout;
    }

this->setSubDet(subdet);
MainWindow* parent = qobject_cast<MainWindow*>(this->parent());
// check parent is not null
parent->update();
}

