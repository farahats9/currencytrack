#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    QString getAPIKey();
    QString getPairs();
public slots:
    void setAPIKey(QString s);
    void setPairs(QString s);
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
