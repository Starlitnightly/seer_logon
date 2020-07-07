#include "atoken.h"
#include "ui_atoken.h"

Atoken::Atoken(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Atoken)
{
    ui->setupUi(this);
}

Atoken::~Atoken()
{
    delete ui;
}
