/**
 * @file changesp.cpp
 * @brief 一键换背包窗口及其相关
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#include "changesp.h"
#include "ui_changesp.h"

/**
 * @brief 换背包精灵头像预览控件初始化函数
 * @param tmp 控件相关的指针
 * @return 无
 */
void change_init(QAxWidget *tmp){
    tmp->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
}
/**
 * @brief 换背包精灵头像预览控件关闭函数
 * @param tmp 控件相关的指针
 * @return 无
 */
void deletesp(QAxWidget *tmp){
    tmp->setControl(QString::fromUtf8("{d27cdb6e-ae6d-11cf-96b8-444553540000}"));
}
/**
 * @brief 换背包精灵头像预览函数
 * @param tmp 控件相关的指针
 * @param url 精灵预览的地址
 * @return 无
 */
void change_sp(QAxWidget *tmp,QString url){
    deletesp(tmp);
    tmp->setControl(QString::fromUtf8("{8856F961-340A-11D0-A96B-00C04FD705A2}"));//注册组件ID
    tmp->dynamicCall("Navigate(QString)",url);
}

/**
 * @brief 一键换背包窗口构造函数
 * @param parent 父类指针
 * @return 无
 */
Changesp::Changesp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Changesp)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose,false);
    sp=new QAxWidget*[12];
    for(int i=0;i<12;i++)
        sp[i]=NULL;
    sp[0]=ui->axWidget;
    sp[1]=ui->axWidget_2;
    sp[2]=ui->axWidget_3;
    sp[3]=ui->axWidget_4;
    sp[4]=ui->axWidget_5;
    sp[5]=ui->axWidget_6;
    sp[6]=ui->axWidget_7;
    sp[7]=ui->axWidget_8;
    sp[8]=ui->axWidget_9;
    sp[9]=ui->axWidget_10;
    sp[10]=ui->axWidget_11;
    sp[11]=ui->axWidget_12;
    for(int i=0;i<12;i++)
        change_init(sp[i]);

    model = new QDirModel;
    ui->treeView->setModel(model);
    path=allpath+"/薄荷味的seer背包";
    ui->treeView->setRootIndex(model->index(path));

    connect(ui->treeView,SIGNAL(pressed(QModelIndex)),this,SLOT(slot_treeView_pressed(QModelIndex)));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(slot_pre_bag()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(slot_savebag()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(slot_auto_bag()));
}
/**
 * @brief 预览输入背包函数
 * @return 无
 */
void Changesp::slot_pre_bag(){
    QString tmp=ui->textEdit->toPlainText();
    QStringList sections = tmp.split(QRegExp("[|]"));
    QString webstr=QString("http://seer.61.com/resource/pet/head/"+sections[1]+".swf");//设置要打开的网页
    for(int i=0;i<12;i++)
        deletesp(sp[i]);
    for(int i=0;i<sections.length();i++){
        qDebug()<<sections[i];
        webstr=QString("http://seer.61.com/resource/pet/head/"+sections[i]+".swf");
        bag<<sections[i];
        qDebug()<<bag[i];
        change_sp(sp[i],webstr);
        bag<<sections[i];
    }

    qDebug()<<webstr;
}
/**
 * @brief 保存已输入背包函数
 * @return 无
 */
void Changesp::slot_savebag(){
    QFileDialog saveDialog;
    //设置对话框打开的模式，是打开文件还是保存文件
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);
    //设置对话框的标题
    saveDialog.setWindowTitle("0.0");
    //设置对话框的打开路径(只是路径，加上文件名失效)
    saveDialog.setDirectory(allpath+"/seer背包");
    //设置对话框默认显示文件名
    saveDialog.selectFile("1");
    //设置文件过滤器
    saveDialog.setNameFilter("*.txt");
    //设置默认选中文件保存类型
    saveDialog.selectNameFilter("*.txt");

    if (saveDialog.exec() == QFileDialog::AcceptSave) {
         //保存文件的路径(包含文件名)
        QString saveFile = saveDialog.selectedFiles().first();
        //保存文件的路径
        QString savePath = saveDialog.directory().path();
        //获得文件过滤器类型
        QString filter = saveDialog.selectedNameFilter();

        QFile file(saveFile);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
        {
            QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
        }
        QTextStream stream(&file);
        stream<<ui->textEdit->toPlainText();

        file.close();
    }


}
/**
 * @brief 背包txt选中函数
 * @param modeIndex 文件树tree的类型
 * @return 无
 */
void Changesp::slot_treeView_pressed(QModelIndex modeIndex)
{
    ui->treeView->resizeColumnToContents(modeIndex.row());
    QString selectedRowTxt = ui->treeView->model()->itemData(modeIndex).values()[0].toString();
    QFile file(path+"/"+selectedRowTxt);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    ui->textEdit->setText(value);
}
/**
 * @brief 一键换背包窗口析构函数
 * @return 无
 */
Changesp::~Changesp()
{
    delete ui;
    delete []sp;
    delete model;
}
/**
 * @brief 背包精灵全部入库函数
 * @return 无
 */
void Changesp::Putsp_home(){
    QVariant x,y;
    while(dm.FindPic(0,0,1000,600,"黑色入库.bmp","000000",0.8,0,x,y)==-1){
        dm.MoveTo(633,268);
        dm.LeftClick();
        if(dm.FindPic(0,0,1000,600,"识别仓库.bmp|识别仓库2.bmp","000000",0.8,0,x,y)!=-1)
            break;
        Delay(500);
    }
}
/**
 * @brief 打开精灵仓库函数
 * @return 无
 */
void Changesp::Opensphome(){
    QVariant x,y;
    while(dm.FindPic(0,0,1000,600,"识别仓库.bmp|识别仓库2.bmp","000000",0.8,0,x,y)==-1){
        dm.MoveTo(849,470);
        dm.LeftClick();
        Delay(500);
    }
}
/**
 * @brief 精灵仓库搜索精灵函数
 * @return 无
 */
void Changesp::Searchsp(HWND pid, QString name){
    QVariant x,y;
    dm.MoveTo(901,103);
    dm.LeftDown();
    dm.MoveTo(839,103);
    QString s=name;
    foreach(QChar c, s)
        PostMessage(pid, WM_CHAR, c.unicode(), 0);
    dm.LeftUp();
    while(dm.FindPic(620, 115, 794, 186, "搜索结果.bmp","000000",0.8,0,x,y)==-1){
        dm.MoveTo(925,108);
        dm.LeftClick();
        Delay(100);
    }
}
/**
 * @brief 仓库精灵放入背包函数
 * @return 无
 */
void Changesp::Putsp_bag(){
    for(int i=0;i<15;i++){
        dm.MoveTo(216,489);
        dm.LeftClick();
        Delay(100);
    }
    for(int i=0;i<15;i++){
        dm.MoveTo(925,137);
        dm.LeftClick();
        Delay(100);
    }
}
/**
 * @brief 自动非法确认-线程启动函数
 * @return 无
 */
void ffAutoC::run(){
    QVariant x,y;
    while(status==true){
        if(dm.FindPic(406, 322, 562, 402,"放入背包确认.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(400, 200, 600, 300, "数据非法.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }
        if(dm.FindPic(0,0,1000,600,"消息盒子x.bmp","000000",0.8,0,x,y)!=-1){
            dm.MoveTo(x.toInt(),y.toInt());
            dm.LeftClick();
        }

        Delay(1000);
    }
}
/**
 * @brief 一键换背包主函数
 * @return 无
 */
void Changesp::slot_auto_bag(){
    Delay(100);
    ffAutoC *tmp=new ffAutoC(this);
    tmp->status=true;
    tmp->start();
    Putsp_home();
    Opensphome();
    QString tmp1=ui->textEdit->toPlainText();
    QStringList sections = tmp1.split(QRegExp("[|]"));
    bag.clear();
    for(int i=0;i<sections.length();i++){
        bag<<sections[i];
    }
    for(int i=0;i<bag.length();i++){
        Searchsp(Pid,bag[i]);
        Putsp_bag();
        Delay(200);
    }
    tmp->status=false;
    Delay(1000);
    delete tmp;
    qDebug()<<"success bag";

}
