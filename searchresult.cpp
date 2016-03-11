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

    for(int i=0;i<res.length();i++){
        QPushButton *pButton = new QPushButton(ui->scrollAreaWidgetContents);
        QSignalMapper* signalMapper = new QSignalMapper(this);
        QPixmap pixmap = QPixmap (":/new/images/icon_writtennote_with_text.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setObjectName(QStringLiteral("mitschriftButton"));
        pButton->setIconSize(QSize(50, 100));
        pButton->setAutoExclusive(false);
        pButton->setMinimumWidth(70);
        pButton->setMinimumHeight(100);
        pButton->setStyleSheet("#mitschriftButton{background-color: #fff; color: #23121C; border: 1px solid #446CB3;}"
                                      "#mitschriftButton:hover{background-color: #446CB3; border: 1px solid #fff;}");
        qDebug() << res[i].getTimestamp();
        QLabel *labelFilename = new QLabel(res[i].getTimestamp().toString("dd.MM.yyyy"));
        QSpacerItem *vSpacer;
        vSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QVBoxLayout *verticalLayout = new QVBoxLayout;
        verticalLayout->addWidget(pButton, 0, Qt::AlignHCenter);
        verticalLayout->addWidget(labelFilename, 0, Qt::AlignHCenter);
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
