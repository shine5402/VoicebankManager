#ifndef MONITORFOLDERSSETTINGDIALOG_H
#define MONITORFOLDERSSETTINGDIALOG_H

#include <QDialog>
#include "monitorfoldersadddialog.h"
#include <QMessageBox>
#include <public_defines.h>
namespace Ui {
    class MonitorFoldersSettingDialog;
}

class MonitorFoldersSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorFoldersSettingDialog(QWidget *parent = 0);
    ~MonitorFoldersSettingDialog();
    void setMonitorFolders(QStringList monitorFolders);
    QStringList getMonitorFolders() const;
signals:
    void monitorFoldersModified(QStringList monitorFolders);
private slots:
    void on_deleteButton_clicked();

    void on_addButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MonitorFoldersSettingDialog *ui;
    QStringList monitorFolders;
    QStringList oldMonitorFolders;
    static const inline QStringList defaultMonitorFolders = {"./voice"};
};

#endif // MONITORFOLDERSSETTINGDIALOG_H
