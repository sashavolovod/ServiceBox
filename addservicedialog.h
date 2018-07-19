#ifndef ADDSERVICEDIALOG_H
#define ADDSERVICEDIALOG_H
#include "comboboxitem.h"
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class AddServiceDialog;
}

class AddServiceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddServiceDialog(QList<ComboBoxItem> *groups, QList<ComboBoxItem> *equpments, QWidget *parent = 0);
    ~AddServiceDialog();

private:
    Ui::AddServiceDialog *ui;
    QList<ComboBoxItem> *equpments;
protected slots:
    void changeGroup(int index);
    void accept();

};

#endif // ADDSERVICEDIALOG_H
