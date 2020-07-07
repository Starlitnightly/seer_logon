#ifndef ATOKEN_H
#define ATOKEN_H

#include <QWidget>
#include "nono.h"
#include <QString>

namespace Ui {
class Atoken;
}

class Atoken : public QWidget
{
    Q_OBJECT

public:
    explicit Atoken(QWidget *parent = 0);
    ~Atoken();

    QTime *time;
    QTimer *timer;
    void closeEvent(QCloseEvent *event);
    QString uu;
public slots:
    void slot_timer_timeout();
    void slot_agree();

private:
    Ui::Atoken *ui;
};

#endif // ATOKEN_H
