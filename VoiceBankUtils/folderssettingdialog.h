#ifndef MONITORFOLDERSSETTINGDIALOG_H
#define MONITORFOLDERSSETTINGDIALOG_H

#include <QDialog>
#include "foldersadddialog.h"
#include <QMessageBox>
#include <public_defines.h>
namespace Ui {
    class FoldersSettingDialog;
}

class FoldersSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FoldersSettingDialog(QWidget *parent = nullptr);
    explicit FoldersSettingDialog(const QStringList &folders,const QString &label,const QString &title
                                  ,QWidget *parent = nullptr,const QStringList &defaultFolders = QStringList(),const QStringList &allowedPrefix = QStringList());
    //TODO:为可用前缀添加说明
    ~FoldersSettingDialog();
    void setFolders(const QStringList &folders);
    QStringList getFolders() const;
    void setLabel(const QString &label);
    void setDefaultFolders(const QStringList &value);

    void setAllowedPrefix(const QStringList& value);

signals:
    void monitorFoldersModified(QStringList folders);
private slots:
    void on_deleteButton_clicked();

    void on_addButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::FoldersSettingDialog *ui;
    QStringList folders;
    QStringList oldFolders;
    QStringList defaultFolders;
    QStringList allowedPrefix;
};

#endif // MONITORFOLDERSSETTINGDIALOG_H
