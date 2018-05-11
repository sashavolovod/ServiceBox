#include <QtGui>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include "mainwindow.h"

MainWindow::MainWindow()
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
    setWindowTitle("Учет ремонта оборудования");
    resize(800, 600);
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
    //table_view->reset();

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
