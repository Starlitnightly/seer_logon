/**
 * @file cdkform.cpp
 * @brief 一键输入cdk窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "cdkform.h"
#include "ui_cdkform.h"
/**
 * @brief 一键输入cdk窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
CdkForm::CdkForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CdkForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);
    int fontId = QFontDatabase::addApplicationFont(allpath + "/font/RuiZiZhenYanTiMianFeiShangYong-2.ttf");
    //qDebug() << "fontId = "<< fontId;
    QString nonot = QFontDatabase::applicationFontFamilies(fontId).at(0);
    //qDebug() <<"fontname = " <<nonot;
    QFont font1(nonot,12);
    ui->label->setFont(font1);//设置控件自定义字体

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(autocdk()));
    connect(ui->pushButton_2,SIGNAL(clicked(bool)),this,SLOT(clearcdk()));
}
/**
 * @brief 一键输入cdk窗口析构函数
 * @return 无
 */
CdkForm::~CdkForm()
{
    delete ui;
}
/**
 * @brief cdk输入框清空函数
 * @return 无
 */
void CdkForm::clearcdk(){
    ui->textEdit->clear();
}
/**
 * @brief 自动输入cdk函数
 * @return 无
 */
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
