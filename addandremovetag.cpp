#include "addandremovetag.h"
#include "ui_addandremovetag.h"
#include "qdebug.h"
#include "QSignalMapper"
#include "mrichtextedit.h"

AddAndRemoveTag::AddAndRemoveTag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAndRemoveTag)
{
    ui->setupUi(this);
    this->setWindowTitle("Org'n'Nice");
}

AddAndRemoveTag::~AddAndRemoveTag()
{
    delete ui;
}

void AddAndRemoveTag::setWrittenNote(WrittenNote cur) {
    ui->pushButton->setObjectName(QStringLiteral("addNewTag"));
    ui->pushButton->setStyleSheet("#addNewTag{background-color: #ddd; color: #23121C; border: 1px solid #bbb;}"
                                          "#addNewTag:hover{color: #000; border: 1px solid #446CB3;}");
    selwr = cur;
    QList<QString> tags = selwr.getTags();
    qDebug() << selwr.getTags().length();
    for(int i=0;i<tags.length();i++)
    {
        QSignalMapper* signalMapper = new QSignalMapper(this);
        QHBoxLayout *itemLayout = new QHBoxLayout();
        QFont font1;
        font1.setPointSize(9);

        QLabel *label_Tagname = new QLabel(tags[i]);
        label_Tagname->setFont(font1);
        itemLayout->addWidget(label_Tagname);

        QSpacerItem *hSpacer;
        hSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
        itemLayout->addSpacerItem(hSpacer);

        QPushButton *pButton = new QPushButton();
        pButton->setObjectName(QStringLiteral("deleteTagButton"));
        QPixmap pixmap = QPixmap (":/images/icons/icon_waste_white.png");
        pButton->setIcon(QIcon(pixmap));
        pButton->setIconSize(QSize(20, 20));
        pButton->setMinimumSize(QSize(25, 25));
        pButton->setMaximumSize(QSize(25, 25));
        pButton->setStyleSheet("#deleteTagButton{background-color: #F22613; color: #23121C; border: 1px solid #000; border-radius: 2px;}"
                               "#deleteTagButton:hover{color: #000; border: 1px solid #888;}");
        itemLayout->addWidget(pButton);

        ui->verticalLayout_2->addLayout(itemLayout);
        connect(pButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(pButton, tags[i]);
        connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(deleteTag(QString)));
    }
    QSpacerItem *vSpacer;
    vSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout_2->addSpacerItem(vSpacer);
}

void AddAndRemoveTag::clearLayout(QLayout *layout){
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

void AddAndRemoveTag::on_pushButton_clicked()
{
    selwr.addTag(ui->lineEdit->text());
    ui->lineEdit->setText("");
    this->update();
    MRichTextEdit* parent = qobject_cast<MRichTextEdit*>(this->parent());
    // check parent is not null
    parent->update();
}

void AddAndRemoveTag::deleteTag(QString seltag) {
    qDebug() << "Delete Tag: " << seltag;
    selwr.removeTag(seltag);
    this->update();
    MRichTextEdit* parent = qobject_cast<MRichTextEdit*>(this->parent());
    // check parent is not null
    parent->update();
}

void AddAndRemoveTag::update() {
while(ui->verticalLayout_2->count() > 0) {
        if(ui->verticalLayout_2->itemAt(0)->layout()){
            QLayout* layout = ui->verticalLayout_2->itemAt(0)->layout();
            qDebug() << "Taken Layout: " << ui->verticalLayout_2->itemAt(0)->layout();
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
        }else{
            ui->verticalLayout_2->removeItem(ui->verticalLayout_2->itemAt(0));
        }

    }
this->setWrittenNote(selwr);
}
