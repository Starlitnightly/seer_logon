#ifndef CDKFORM_H
#define CDKFORM_H

#include <QWidget>

#include "nono.h"

namespace Ui {
class CdkForm;
}

class CdkForm : public QWidget
{
    Q_OBJECT

public:
    explicit CdkForm(QWidget *parent = 0);
    ~CdkForm();
public slots:
    void autocdk();
    void clearcdk();

private:
    Ui::CdkForm *ui;
};

#endif // CDKFORM_H
