#ifndef ATOKEN_H
#define ATOKEN_H

#include <QWidget>

namespace Ui {
class Atoken;
}

class Atoken : public QWidget
{
    Q_OBJECT

public:
    explicit Atoken(QWidget *parent = 0);
    ~Atoken();

private:
    Ui::Atoken *ui;
};

#endif // ATOKEN_H
