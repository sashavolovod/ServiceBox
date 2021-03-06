#include <QtGui>
#include <QtCore>
#include <QtWidgets/QApplication>
#include <QMessageBox>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSystemTrayIcon>

#include "runguard.h"
#include "dbhelper.h"
#include "mainwindow.h"

bool DbHelper::firtsConnect = true;

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("gefest");
    QCoreApplication::setOrganizationDomain("gefest.org");
    QCoreApplication::setApplicationName("ServiceBox");
    QApplication app(argc, argv);

    RunGuard guard( "servicebox.app" );
        if (!guard.tryToRun())
        {
            QMessageBox::critical(0, QObject::tr("Systray"),
                                   QObject::tr("Уже запущена одна копия программы"));

            return 0;
        }

    Q_INIT_RESOURCE(systray);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);


    DbHelper dbHelper;

    if(dbHelper.getDb().isOpen()==true)
    {
        MainWindow window;
        window.show();
        return app.exec();
    }
    else
    {
        QMessageBox::critical(0, QObject::tr("Ошибка"),
                              QObject::tr("Не могу подключится к серверу базы данных"));
        return -1;
    }

}
