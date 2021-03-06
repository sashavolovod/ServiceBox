#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtCore>

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSplitter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSettings>
#include <QTableWidgetItem>
#include <QMenuBar>
#include <QHeaderView>
#include <QSound>

#include "servicetablemodel.h"
#include "servicedetailtablemodel.h"
#include "service.h"
#include "messageedit.h"
#include "comboboxitem.h"
#include "addservicedialog.h"
#include "servicedetail.h"

class MessageEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void createUI(); // функция создания графического интерфейса
    bool sendMessage(QString str);

protected:
    QDateTime lastMessageDate;
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
    QTextEdit *teLog;    // окно редактирования
    MessageEdit *teMessage;// окно написания сообщения

    QMenuBar *mnuBar;    // главное меню приложения
    QAction *quitAction;
    QAction *actAbout;   // вывод окна о программе
    QAction *actAboutQt; // вывод окна о библиотеке Qt
    QAction *actAdd;

    QPushButton *btnReady;
    QPushButton *btnNotReady;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;

    QList<Service> serviceList;
    QList<ServiceDetail> *serviceDetailList;
    QList<ComboBoxItem> groups;
    QList<ComboBoxItem> equpments;

    void createActions();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QTableView *table_view;
    QTableView *tableDetailView;
    ServiceTableModel *model;
    ServiceDetailTableModel *detailModel;

    QVBoxLayout *leftVBoxLayout;
    QHBoxLayout *filterLayout;
    //QCheckBox *chkOnlyNotWorking;
    QComboBox *cbStatus;
    QLineEdit *leFilter;

    QSplitter *hSplitter;
    QSplitter *vSplitter;
    QVBoxLayout *vLayout;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *hLayout;
    QWidget *rightWidget;
    QWidget *leftWidget;

    QTimer *timer;

    QString currentUser;
    int currentUserId;
    int rules;


    void getCurrentUser();

    void load_data();

    void saveSettings();
    void updateDetail(int id);
    void updateServiceDetailList(int equipmentId);
    int  getSelectedId();
    void getComboBoxItems();
    void checkNewMessages();

protected slots:
    void setIcon();
    void about();   // вывод сообщения о программе
    void aboutQt(); // вывод информации о библиотеке Qt

    void onSelectionChanged(const QItemSelection &, const QItemSelection &);
    void onDetailSelectionChanged(const QItemSelection &, const QItemSelection &);
    void update();
    bool changeStatus();
    bool changeStatus2();
    void addService();
    void applyFilter();
};

#endif //MAINWINDOW_H
