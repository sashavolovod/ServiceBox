#include "common.h"

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

    MainWindow window;
    window.show();

    return app.exec();
}
