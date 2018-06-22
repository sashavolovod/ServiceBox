#include "logindialog.h"
#include "ui_logindialog.h"
#include "common.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(Connect()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    setUi();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setUi()
{
    QSettings settings;
    ui->leServer->setText(settings.value("host", "localhost").toString());
    ui->lePort->setText(settings.value("port", 5432).toString());
    ui->leDb->setText(settings.value("database", "texac_db").toString());
    ui->leLogin->setText(settings.value("login", "").toString());
    QString sPass = settings.value("password", "").toString();
    sPass = decodeText(sPass, PASS_PHRASE);
    ui->lePassword->setText(sPass);
}

void LoginDialog::Connect()
{  
    sHost = ui->leServer->text();
    iPort = ui->lePort->text().toInt();
    sDatabase = ui->leDb->text();
    sLogin = ui->leLogin->text();
    sPassword = ui->lePassword->text();
    accept();
}
