#include "common.h"
#include "messageedit.h"

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
                                 "Для завершения работы программы выберете пункт <b>Выход</b> из контекстного меню");
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
    teLog->setReadOnly(true);
    teMessage = new MessageEdit(this);
    btnReady = new QPushButton("Выполнено", this);
    connect(btnReady, SIGNAL (pressed()), this, SLOT (changeStatus()));

    table_view = new QTableView;
    ServiceTableModel *model = new ServiceTableModel;
    load_data();
    getComboBoxItems();

    model->setList(&serviceList);
    table_view->setModel(model);
    table_view->setColumnHidden(0,true);
    table_view->setColumnWidth(1,100);
    table_view->setColumnWidth(2,150);
    table_view->horizontalHeader()->setStretchLastSection(true);
    table_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(table_view->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(onSelectionChanged(const QItemSelection &, const QItemSelection &)));
    table_view->selectRow(0);

    splitter = new QSplitter;

    splitter->addWidget(table_view);
    rightWidget = new QWidget();
    vLayout = new QVBoxLayout();
    hLayout = new QHBoxLayout();

    rightWidget->setLayout(vLayout);
    vLayout->addWidget(teLog, 1);
    teMessage->setFixedHeight(75);

    vLayout->addLayout(hLayout);
    hLayout->addWidget(teMessage);
    hLayout->addWidget(btnReady);

    splitter->addWidget(rightWidget);
    splitter->setSizes(QList<int>({150, INT_MAX}));

    setCentralWidget(splitter); // главный виджет окна
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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    //addService();
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

void MainWindow::load_data()
{
    QSqlDatabase db = QSqlDatabase::database();
    QString sql("SELECT "
                  "equipment_service_id as id, "
                  "equipment_services_date as date, "
                  "equipment_name as name, "
                  "status "
                "FROM "
                  "equipments inner join equipment_services on equipment_services.equipment_id = equipments.equipment_id "
                "ORDER BY date; "
                );
    QSqlQuery query;

    db.open();
    if(db.isOpen())
    {
        query.exec(sql);
        serviceList.clear();
        while (query.next())
        {
            Service s;
            s.id = query.value(0).toInt();
            s.date = query.value(1).toDateTime();
            s.name = query.value(2).toString();
            s.status = query.value(3).toInt();
            serviceList << s;
        }

        db.close();
    }
}

void saveSettings()
{
}

void MainWindow::onSelectionChanged(const QItemSelection &sel, const QItemSelection &desel)
{
    updateDetail(getSelectedId());
}

void MainWindow::updateDetail(int id)
{
    QSqlDatabase db = QSqlDatabase::database();
    QString sql("SELECT "
                "  equipment_service_detail id, "
                "  equipment_user_name user_name, "
                "  note, "
                "  date "
                "FROM equipment_service_details INNER JOIN equipment_users on   equipment_user_id = equipment_users "
                "WHERE equipment_services_id = :id "
                "ORDER BY date; "
                );
    QSqlQuery query;

    db.open();
    if(db.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", id);
        if(query.exec()==false)
            QMessageBox::critical(this, "Ошибка получения информации с базы данных", query.lastError().text());;

        teLog->clear();
        while (query.next())
        {
            QString str = QString("%1 [%2]: %3")
                    .arg(query.value(1).toString())
                    .arg(query.value(3).toDateTime().toString("dd.MM.yyyy hh:mm:ss"))
                    .arg(query.value(2).toString());

            teLog->append(str);
            teLog->append("");
        }
        query.clear();
        db.close();
    }
}

bool MainWindow::sendMessage(QString str)
{
    QSqlDatabase db = QSqlDatabase::database();
    QString sql("insert into equipment_service_details(equipment_services_id, equipment_users, note) VALUES  (:id, :user_id, :note);");
    QSqlQuery query;
    bool result;

    int i = table_view->currentIndex().row();
    QModelIndex index = table_view->model()->index(i, 0);
    int id = index.data().toInt();

    db.open();
    if(db.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":id", id);
        query.bindValue(":user_id", 1);
        query.bindValue(":note", str);
        result = query.exec();
        if(result == false)
            QMessageBox::critical(this, "Ошибка сохранения", query.lastError().text());
        else
            updateDetail(id);
    }

    query.clear();
    db.close();
    return result;
}



void MainWindow::update()
{
    updateDetail(getSelectedId());
}

int MainWindow::getSelectedId()
{
    int i = table_view->currentIndex().row();
    // qDebug() << "i = " << i;
    QModelIndex index = table_view->model()->index(i, 0);
    // qDebug() << "index = " << index;
    return index.data().toInt();
}

bool MainWindow::changeStatus()
{
    int new_status;
    Service s = serviceList.at(table_view->currentIndex().row());
    switch (s.status)
    {
        case 0:
            new_status = 1;
        break;
        case 1:
            new_status = 2;
        break;
        case 2:
            new_status = 0;
        break;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QString sql("update equipment_services set status = :status where equipment_service_id = :service_id;");
    QSqlQuery query;
    bool result;

    db.open();
    if(db.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":status", new_status);
        query.bindValue(":service_id", s.id);
        result = query.exec();
        if(result == false)
            QMessageBox::critical(this, "Ошибка сохранения", query.lastError().text());
        else
            load_data();
    }

    query.clear();
    db.close();
    return result;
}

void MainWindow::getComboBoxItems()
{
    QSqlDatabase db = QSqlDatabase::database();
    QString sql("select equipment_id as id, equipment_type_id as parent_id, equipment_name || ' ( инв. №' ||  equipment_code || ')' as name from equipments order by name;");
    QSqlQuery query;

    db.open();
    if(db.isOpen())
    {
        query.exec(sql);
        equpments.clear();
        while (query.next())
        {
            ComboBoxItem item;
            item.id = query.value(0).toInt();
            item.parentId = query.value(1).toInt();
            item.name = query.value(2).toString();
            equpments << item;
        }
        query.clear();
        query.exec("select equipment_types_id as id, equipment_type_name as name from equipment_types order by name;");
        groups.clear();
        while (query.next())
        {
            ComboBoxItem item;
            item.id = query.value(0).toInt();
            item.parentId = 0;
            item.name = query.value(1).toString();
            groups << item;
        }

        db.close();
    }
}
void MainWindow::addService()
{
    AddServiceDialog dialog(&groups, &equpments);
    dialog.setModal(true);
    dialog.exec();
}
