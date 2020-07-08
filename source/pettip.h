/**
 * @file pettip.h
 * @brief 精灵技能快查窗口头文件
 * @author starlitnightly
 * @email Starlitnightly@163.com
 * @version 1.0.0
 * @date 2020-07-09
 * @license GPL
 */
#ifndef PETTIP_H
#define PETTIP_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QWidget>
#include <QTextCodec>
#include <QString>
#include <QUrl>
#include <QRegExp>
#include <QFile>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

namespace Ui {
class Pettip;
}
/**
 * @brief 精灵技能快查窗口类
 * 这个类写了整整一天，格式化精灵技能真难
 */
class Pettip : public QWidget
{
    Q_OBJECT

public:
    explicit Pettip(QWidget *parent = 0);
    ~Pettip();
    QString petname;
    QJsonObject jsonObject;
    QJsonParseError parseJsonErr;

    QNetworkAccessManager *m_manager;
public slots:
    void slot_tip();
    void slot_replayFinished(QNetworkReply *reply);
    void slot_getname(QString name);
    void slot_buttonget();
signals:
    void sendmes(QString msg);
private:
    Ui::Pettip *ui;
};

#endif // PETTIP_H
