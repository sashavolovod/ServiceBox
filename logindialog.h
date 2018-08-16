#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSettings>

#include "aesqt.h"

#define PASS_PHRASE "top_secret"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    QString sHost;
    int iPort;
    QString sDatabase;
    QString sLogin;
    QString sPassword;


private:
    Ui::LoginDialog *ui;
    void setUi();

private slots:
    void Connect();
};

#endif // LOGINDIALOG_H
