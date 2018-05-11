#include <QtGui>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include "mainwindow.h"

MainWindow::MainWindow()
{
    createUI();
}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, "Учет ремонта оборудования",
                                 "Учет ремонта оборудования продолжит работать в качестве фоновой задачи. "
                                 "Для завершения работы монитора выберете пункт <b>Выход</b> из контекстного меню");
        hide();
        event->ignore();
    }
}

void MainWindow::setIcon()
{
    QIcon icon(":/images/monitor.ico");
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
}

void MainWindow::createActions()
{
    // создание объектов главного окна
    actAbout = new QAction("О программе...", this);
    connect(actAbout, SIGNAL(triggered()), this, SLOT(about()));
    actAboutQt = new QAction("О библиотеке Qt...", this);
    connect(actAboutQt, SIGNAL(triggered()), this, SLOT(aboutQt()));

    // действия контестное меню
    minimizeAction = new QAction("Свернуть", this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction("Развернуть", this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

    restoreAction = new QAction("Восстановить", this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction("Выход", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    setIcon();
}

// создание элементов управления главного окна
void MainWindow::createUI()
{
    createActions();
    createTrayIcon();
    trayIcon->show();

    /*
    table_view = new QTableView;
    model = new ProcessTableModel;
    table_view->setModel(model); // устанавливаем модель
    table_view->resizeColumnsToContents();
    table_view->horizontalHeader()->setStretchLastSection(true);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(table_view);
    setLayout(layout);
    */


    // создание панели инструментов
/*
    toolbar = new QToolBar();
    addToolBar(toolbar);
*/
    // создание редактора для вывода журнала работы приложения
    teLog = new QTextEdit(this);
    setCentralWidget(teLog); // главный виджет окна
/*
    // настройка строки состояния
    label = new QLabel("Нажмите кнопку <b>Старт</b> для начала проверки");
    statusBar()->addWidget(label,1);
*/


    // добавление элементов в панель инструментов
/*
    toolbar->addAction(actStartScan);
    toolbar->addAction(actStopScan);
    toolbar->addSeparator();
    toolbar->addAction(actShowSettingDialog);
*/
    // создание главного меню приложения
    mnuBar = new QMenuBar(this);
    QMenu *mnuFile = new QMenu("Файл");
    mnuFile->addAction(quitAction);
/*
    QMenu *mnuService = new QMenu("Сервис");
    mnuService->addAction(actStartScan);
    mnuService->addAction(actStopScan);
    mnuService->addSeparator();
    mnuService->addAction(actShowSettingDialog);
*/

    QMenu *mnuHelp = new QMenu("Справка");
    mnuHelp->addAction(actAboutQt);
    mnuHelp->addSeparator();
    mnuHelp->addAction(actAbout);

    mnuBar->addMenu(mnuFile);
//    mnuBar->addMenu(mnuService);
    mnuBar->addMenu(mnuHelp);
    setMenuBar(mnuBar);

    resize(800, 600);
    setWindowTitle("Учет ремонта оборудования");
    setWindowIcon(QIcon(":/images/antivirus.ico"));
}

// вывод собщения о библиотеке Qt
void MainWindow::aboutQt()
{
   QMessageBox::aboutQt(this,"О библиотеке Qt");
}

// вывод сообщения о программе
void MainWindow::about()
{
    QMessageBox::information(this, tr("О программе"),tr("<b>Учет ремонта оборудования</b> - программа для учета ремонта оборудования  ИнЦ.<br><br><b>Разработчик:</b> инженер-программист ИнЦ Воловод А.А.<br><b>Тел:</b> 66-16"));
}
