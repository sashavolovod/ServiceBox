#include "addservicedialog.h"
#include "ui_addservicedialog.h"

AddServiceDialog::AddServiceDialog(QList<ComboBoxItem> *groups, QList<ComboBoxItem> *equpments, int equpmentId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServiceDialog)
{
    int groupIndex, groupId, i;
    ui->setupUi(this);

    ui->cbGroup->addItem("", -1);
    foreach (ComboBoxItem i, *groups)
    {
        ui->cbGroup->addItem(i.name, i.id);
    }

    connect(ui->cbGroup, SIGNAL(currentIndexChanged(int)), this, SLOT(changeGroup(int)));
    this->equpments = equpments;

    foreach (ComboBoxItem it, *equpments) {
        if(it.id == equpmentId)
        {
            groupId = it.parentId;
            break;
        }
    }

    foreach (ComboBoxItem it, *groups) {
        if(it.id == groupId)
        {
            ui->cbGroup->setCurrentText(it.name);
            break;
        }
    }

    for(i=0; i<ui->cbEq->count(); i++) {
        if(ui->cbEq->itemData(i).toInt()==equpmentId)
            break;
    }

    ui->cbEq->setCurrentIndex(i);


}

AddServiceDialog::~AddServiceDialog()
{
    delete ui;
}

void AddServiceDialog::changeGroup(int index)
{
    int id = ui->cbGroup->currentData().toInt();
    ui->cbEq->clear();
    ui->cbEq->addItem("", -1);
    foreach(ComboBoxItem i, *equpments)
    {
        if(i.parentId==id)
            ui->cbEq->addItem(i.name, i.id);
    }
}

void AddServiceDialog::accept()
{
    int id = ui->cbEq->currentData().toInt();
    QString note = ui->teNote->toPlainText().trimmed();
    if(id<1)
    {
        QMessageBox::information(this, "Ошибка",
                                 "Не выбрано оборудование");
        return;
    }

    if(note.length()==0)
    {
        QMessageBox::information(this, "Ошибка",
                                 "Не указана неисправность");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QString sql("insert into equipment_services(equipment_services_date, status, equipment_id) VALUES (now(), 1 , :equipment_id);");
    QSqlQuery query;
    bool result;
    db.open();
    if(db.isOpen())
    {
        query.prepare(sql);
        query.bindValue(":equipment_id", id);
        result = query.exec();
        if(result == false)
        {
            QMessageBox::critical(this, "Ошибка сохранения", query.lastError().text());
            return;
        }
        query.prepare("insert into equipment_service_details(equipment_services_id, equipment_users, note) VALUES ((select currval('equipment_services_equipment_service_id_seq')), :user_id, :note);");
        query.bindValue(":user_id", 1);
        query.bindValue(":note", note);
        result = query.exec();
        if(result == false)
        {
            QMessageBox::critical(this, "Ошибка сохранения 'equipment_service_details'", query.lastError().text());
            return;
        }
    }

    query.clear();
    db.close();
    QDialog::accept();
}
