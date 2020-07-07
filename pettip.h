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
