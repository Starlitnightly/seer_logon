#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QLibrary>
#include <QDebug>
#include<qmessagebox.h>
#include<QFileInfo>
#include<Qdir>
#include<QFile>



bool g_bMuted;
/*
static void raisePrivilege()
{
    // to read memory of some processes, we need this
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) {
        if(LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
            AdjustTokenPrivileges(hToken, FALSE, &tp, NULL, NULL, 0);
        }
    }
    if(hToken) {
        CloseHandle(hToken);
    }
}*/

class CLoadQSS
{
public:
    static void setStyle(const QString &style)
    {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};



int main(int argc, char *argv[])
{
    //raisePrivilege();
    QApplication a(argc, argv);

    /*
    QFile qss(":style.qss");
    if( qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }
    else{
        qDebug("Open failed");
    }
    */

    MainWindow w;
    w.show();

    return a.exec();
}
