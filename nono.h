#ifndef NONO_H
#define NONO_H

#include <QWidget>
#include <QMovie>
#include <QMouseEvent>
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <Qdir>

#include "ext.h"

namespace Ui {
class Nono;
}

class Nono : public QWidget
{
    Q_OBJECT

public:
    explicit Nono(QWidget *parent = 0);
    ~Nono();

    QPoint mouseMovePos;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Nono *ui;

    QTime *time;
    QTimer *timer;
    int firetime;
    int firetime_min;
    int firetime_sec;
public slots:
    void slot_startedTimer_clicked(bool);
    void slot_stopedTimer_clicked(bool);
    void slot_timer_timeout();
    void slot_capture(bool tmp);
};

#endif // NONO_H
