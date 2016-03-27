#include "searchresult.h"
#include "ui_searchresult.h"
#include <QDebug>
#include <QDialog>
#include <QSignalMapper>
#include "main.h"
#include <QList>
#include "subject.h"
#include <QPushButton>

SearchResult::SearchResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchResult)
{
    ui->setupUi(this);
}

SearchResult::~SearchResult()
{
    delete ui;
}

void SearchResult::setResult(QList<WrittenNote> cur, QString message)
{
    this->res = cur;
    //ui->label_2->setText(message);
    int a = 2;
    int line = 0;
    int col = 0;
    ui->label->setText(message);
    for(int i=0;i<res.length();i++){
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
        qDebug() << res[i].getTimestamp();
        QLabel *labelFilename = new QLabel(res[i].getTimestamp().toString("dd.MM.yyyy"));
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
        verticalLayout->addWidget(labelFilename, 0, Qt::AlignCenter);
        verticalLayout->addWidget(deleteButton, 0, Qt::AlignCenter);
        verticalLayout->addItem(vSpacer);
        if(i > a){
            a += 3;
            line++;
            col = 0;
        }
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

void SearchResult::textDet(int index){
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Org'n'Nice");
    rte = new MRichTextEdit(dialog); // Be sure to destroy you window somewhere
    rte->setText(res[index].getContent().replace("^", "'"));
    rte->setNote(res[index]);
    dialog->show();
}

void SearchResult::deleteWrittenNote(int item){
    res[item].deleteWrittenNote();
}
