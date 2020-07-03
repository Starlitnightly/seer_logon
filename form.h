#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QThread>
#include <QDebug>

#include "ext.h"


namespace Ui {
class Form;
class Work;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private:
    Ui::Form *ui;

public slots:
    void test();
};

class Work: public QThread
{
    Q_OBJECT

public:
    Work(QObject *parent = 0)
        : QThread(parent)
    {
    }
protected:
    void run();
signals:
    void done();
};

//自动勇者之塔
class Tower: public QThread
{
    Q_OBJECT

public:
    bool status;
    int now;
    Tower(QObject *parent = 0)
        : QThread(parent)
    {
        status=false;
    }
protected:
    void run();
signals:
    void done();
};


#endif // FORM_H
