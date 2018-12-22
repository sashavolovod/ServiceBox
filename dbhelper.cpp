#include "dbhelper.h"

DbHelper::DbHelper()
{
    QSettings settings;
    sHost = settings.value("host", "localhost").toString();
    iPort = settings.value("port", 5432).toInt();
    sDatabase = settings.value("database", "texac_db").toString();
    sLogin = settings.value("login", "").toString();
    sPassword = settings.value("password", "").toString();
    sPassword = decodeText(sPassword, PASS_PHRASE + QHostInfo::localHostName());
}

void DbHelper::saveSettings()
{
    QSettings settings;
    settings.setValue("host", sHost);
    settings.setValue("port", iPort);
    settings.setValue("database", sDatabase);
    settings.setValue("login", sLogin);
    settings.setValue("password",  encodeText(sPassword,PASS_PHRASE + QHostInfo::localHostName()));
    settings.sync();
}

QSqlDatabase DbHelper::getDb()
{
    LoginDialog d;
    bool f=false;
    d.setModal(true);


    while(1)
    {
        /*
        if(firtsConnect==true)
        {
            firtsConnect=false;
            if(d.exec()==QDialog::Rejected)
                break;
            else
            {
                sHost = d.sHost;
                iPort = d.iPort;
                sDatabase = d.sDatabase;
                sLogin = d.sLogin;
                sPassword = d.sPassword;
            }
        }
*/
        if(connect()==true)
        {
            saveSettings();
            break;
        }

        if(f==true)
        {
            QMessageBox::critical(0, "Ошибка подключения к серверу базы данных", db.lastError().text());
        }

        f=true;
        if(d.exec()==QDialog::Rejected)
            break;
        else
        {
            sHost = d.sHost;
            iPort = d.iPort;
            sDatabase = d.sDatabase;
            sLogin = d.sLogin;
            sPassword = d.sPassword;
        }
    }
    return db;
}

bool DbHelper::connect()
{
    if(QSqlDatabase::contains(QSqlDatabase::defaultConnection))
        db = QSqlDatabase::database();
    else
        db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(sHost);
    db.setPort(iPort);
    db.setDatabaseName(sDatabase);
    db.setUserName(sLogin);
    db.setPassword(sPassword);

    if(db.open())
    {
        qDebug() << "connected";
        return true;
    }
    else
        return false;
}
