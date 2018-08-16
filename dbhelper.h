#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QString>
#include <QSettings>
#include <QMessageBox>

#include "logindialog.h"


class DbHelper
{
public:
    DbHelper();
    QSqlDatabase getDb();
private:
    QSqlDatabase db;
    QString sHost;
    int iPort;
    QString sDatabase;
    QString sLogin;
    QString sPassword;

    bool connect();
    void saveSettings();
};

#endif // DBHELPER_H
