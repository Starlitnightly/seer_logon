#ifndef CHANGESP_H
#define CHANGESP_H

#include <QWidget>
#include <QModelIndex>
#include <QString>
#include <QDirModel>
#include <QDebug>
#include <QAxWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QVariant>

#include "ext.h"
#include "xy.h"

namespace Ui {
class Changesp;
}
//非法确认
class ffAutoC: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    ffAutoC(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};

class Changesp : public QWidget
{
    Q_OBJECT

public:
    explicit Changesp(QWidget *parent = 0);
    ~Changesp();

    QAxWidget **sp;
    QDirModel *model;
    QString path;

    QString bag_status;
    QStringList bag;
    void Putsp_home();
    void Opensphome();
    void Searchsp(HWND pid,QString name);
    void Putsp_bag();



private:
    Ui::Changesp *ui;
public slots:
    void slot_treeView_pressed(QModelIndex modeIndex);
    void slot_pre_bag();
    void slot_savebag();
    void slot_auto_bag();
};


#endif // CHANGESP_H
