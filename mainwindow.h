#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "servicetablemodel.h"
#include "service.h"
#include "messageedit.h"
#include "common.h"
#include "comboboxitem.h"
#include "addservicedialog.h"

#include <QTimer>

#include <QString>
#include <QHBoxLayout>
#include <QPushButton>

class ServiceTableModel;
class MessageEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void createUI(); // функция создания графического интерфейса
    bool sendMessage(QString str);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    QTextEdit *teLog;    // окно редактирования
    MessageEdit *teMessage;// окно написания сообщения

    QMenuBar *mnuBar;    // главное меню приложения
    QAction *quitAction;
    QAction *actAbout;   // вывод окна о программе
    QAction *actAboutQt; // вывод окна о библиотеке Qt
    QAction *actAdd;

    QPushButton *btnReady;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;

    QList<Service> serviceList;
    QList<ComboBoxItem> groups;
    QList<ComboBoxItem> equpments;

    void createActions();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTableView *table_view;
    ServiceTableModel *model;
    QSplitter *splitter;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QWidget *rightWidget;

    QTimer *timer;

    void load_data();

    void saveSettings();
    void updateDetail(int id);
    int getSelectedId();
    void getComboBoxItems();

protected slots:
    void setIcon();
    void about();   // вывод сообщения о программе
    void aboutQt(); // вывод информации о библиотеке Qt
    void onSelectionChanged(const QItemSelection &, const QItemSelection &);
    void update();
    bool changeStatus();
    void addService();
};

#endif //MAINWINDOW_H
