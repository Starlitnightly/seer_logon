#include "cdkform.h"
#include "ui_cdkform.h"

CdkForm::CdkForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CdkForm)
{
    ui->setupUi(this);
    int fontId = QFontDatabase::addApplicationFont(QDir::currentPath() + "/font/RuiZiZhenYanTiMianFeiShangYong-2.ttf");
    //qDebug() << "fontId = "<< fontId;
    QString nonot = QFontDatabase::applicationFontFamilies(fontId).at(0);
    //qDebug() <<"fontname = " <<nonot;
    QFont font1(nonot,12);
    ui->label->setFont(font1);//设置控件自定义字体

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(autocdk()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(clearcdk()));
}

CdkForm::~CdkForm()
{
    delete ui;
}

void CdkForm::clearcdk(){
    ui->textEdit->clear();
}

void CdkForm::autocdk(){
    QString c,c1,c2,c3,c4;
    c=ui->textEdit->toPlainText();
    c1=c.mid(0,4);
    c2=c.mid(4,8);
    c3=c.mid(8,12);
    c4=c.mid(12,16);

    dm.MoveTo(297,112);
    dm.LeftDown();
    dm.MoveTo(335,112);
    foreach(QChar k, c1)
        PostMessage(Pid, WM_CHAR, k.unicode(), 0);
    Delay(100);
    dm.LeftUp();

    dm.MoveTo(412,112);
    dm.LeftDown();
    dm.MoveTo(449,112);
    foreach(QChar k, c2)
        PostMessage(Pid, WM_CHAR, k.unicode(), 0);
    Delay(100);
    dm.LeftUp();

    dm.MoveTo(526,112);
    dm.LeftDown();
    dm.MoveTo(560,112);
    foreach(QChar k, c3)
        PostMessage(Pid, WM_CHAR, k.unicode(), 0);
    Delay(100);
    dm.LeftUp();

    dm.MoveTo(642,112);
    dm.LeftDown();
    dm.MoveTo(674,112);
    foreach(QChar k, c4)
        PostMessage(Pid, WM_CHAR, k.unicode(), 0);
    Delay(100);

    dm.MoveTo(485,159);
    dm.LeftClick();
    dm.LeftUp();
}
