#ifndef DBHELPER_H
#define DBHELPER_H

#include "common.h"


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
