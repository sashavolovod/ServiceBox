#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "servicetablemodel.h"
#include "service.h"
#include "common.h"

class ServiceTableModel;


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

    QList<Service> serviceList;

    void createActions();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTableView *table_view;
    ServiceTableModel *model;
    QSplitter *splitter;

    void load_data();
    void saveSettings();
    void updateDetail(int id);

private slots:
    void setIcon();
    void about();   // вывод сообщения о программе
    void aboutQt(); // вывод информации о библиотеке Qt
    void onSelectionChanged(const QItemSelection &, const QItemSelection &);
};

#endif //MAINWINDOW_H
