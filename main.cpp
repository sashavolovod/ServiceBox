#include <QDebug>
#include <QFile>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

int main()
{
    QFile file("~/dbcred.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "no config file\n";
        return -1;
    }
    QTextStream in(&file);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(in.readLine());
    db.setDatabaseName(in.readLine());
    db.setUserName(in.readLine());
    db.setPassword(in.readLine());

    if(db.open())
    {
        qDebug() <<"opened" ;
        db.close();
    }

    return 0;
}
