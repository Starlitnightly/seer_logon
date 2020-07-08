/**
 * @file nono.h
 * @brief nono主窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
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
#include <QFontDatabase>
#include <QLabel>
#include <QtGlobal>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>
#include <QJsonArray>
#include <QClipboard>
#include <QSettings>
#include <QMessageBox>
#include <QBuffer>


#include "ext.h"
#include "xy.h"
#include "pettip.h"

namespace Ui {
class Nono;
}
/**
 * @brief 重载标签（可点击）
 * 重载了标签，造了一个带有点击信号的标签类
 */
class ClickedLabel : public QLabel
{
    Q_OBJECT
signals:
    void Clicked(ClickedLabel* clicked);
public:
    ClickedLabel(QWidget *parent=0): QLabel(parent),m_str("")
    {
        setText(m_str);
    }

protected:
    void mouseReleaseEvent( QMouseEvent* );
private:
    QString m_str;
};
/**
 * @brief nono窗口类
 * 这个类跟nono相关
 */
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

    QMovie *movie;
    QMovie *movie1;
    QMovie *movie2;
    QMovie *movie3;
    QMovie *movie4;

    void getAccessToken(QString key, QString secret);
    void recognition();


private:
    Ui::Nono *ui;
    DWORD tmp1;

    QTime *time;
    QTimer *timer;

    QTime *time1;
    QTimer *timer1;

    int firetime;
    int firetime_min;
    int firetime_sec;
    bool hidecap;
    ClickedLabel *clabel;
    ClickedLabel *freshlabel;
    ClickedLabel *shibielabel;

    QString accessToken;
    QNetworkAccessManager *nam;
    Pettip *pt;
public slots:
    void slot_startedTimer_clicked(bool);
    void slot_stopedTimer_clicked(bool);
    void slot_timer_timeout();
    void slot_capture(bool tmp);

    void slot_nono_change();

    void slot_tip(QString content);
    void slot_hidecap();

    void slot_shibie();
    void slot_Fresh();

    void getAccessTokenRequestFinished(QNetworkReply* reply);
    void recognitionRequestFinished(QNetworkReply* reply);
    void showskill();
signals:
    void signal_fresh();
    void signal_sb();
    void signal_pet(QString name);
};



#endif // NONO_H
