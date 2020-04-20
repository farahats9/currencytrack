#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getAPIKey()
{
    return ui->lineEdit->text();
}

QString SettingsDialog::getPairs()
{
    return ui->lineEdit_2->text();
}

void SettingsDialog::setAPIKey(QString s)
{
    ui->lineEdit->setText(s);
}

void SettingsDialog::setPairs(QString s)
{
    ui->lineEdit_2->setText(s);
}
