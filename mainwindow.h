#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QDialog>
#include <QTextEdit>
#include <QtCore>
#include <QMenuBar>
#include <QTableView>
#include <QSplitter>
#include <servicetablemodel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void createUI(); // функция создания графического интерфейса


protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    QTextEdit *teLog;    // окно редактирования
    QTextEdit *teMessage;// окно написания сообщения

    QMenuBar *mnuBar;    // главное меню приложения
    QAction *quitAction;
    QAction *actAbout;   // вывод окна о программе
    QAction *actAboutQt; // вывод окна о библиотеке Qt

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;

    void createActions();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTableView *table_view;
    ServiceTableModel *model;
    QSplitter *splitter;

    void load_data(ServiceTableModel *model);
    void saveSettings();

private slots:
    void setIcon();
    void about();   // вывод сообщения о программе
    void aboutQt(); // вывод информации о библиотеке Qt
};

#endif //MAINWINDOW_H
