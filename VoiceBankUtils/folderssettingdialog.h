#ifndef MONITORFOLDERSSETTINGDIALOG_H
#define MONITORFOLDERSSETTINGDIALOG_H

#include <QDialog>
#include "foldersadddialog.h"
#include <QMessageBox>
#include <public_defines.h>
#include "./CommonUtils/showhtmldialog.h"

//TODO:移动到CommonUtil

namespace Ui {
    class FoldersSettingDialog;
}

class FoldersSettingDialog : public QDialog
{
    Q_OBJECT

public:
    struct AllowedAffix{
        QString affix;
        enum Type{prefix, suffix} type = prefix;
        Q_ENUM(Type);
        QString briefDescription;
        QString description;
    };

    explicit FoldersSettingDialog(QWidget *parent = nullptr);
    explicit FoldersSettingDialog(const QStringList &folders,const QString &label,const QString &title
                                  ,QWidget *parent = nullptr,const QStringList &defaultFolders = QStringList(),const QList<AllowedAffix> &allowedPrefix = QList<AllowedAffix>());
    ~FoldersSettingDialog();
    void setFolders(const QStringList &folders);
    QStringList getFolders() const;
    void setLabel(const QString &label);
    void setDefaultFolders(const QStringList &value);

    void setAllowedPrefix(const QList<AllowedAffix>& value);

signals:
    void monitorFoldersModified(QStringList folders);
private slots:
    void on_deleteButton_clicked();

    void on_addButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_allowedPrefixDescriptionButton_clicked();

    void on_modifyButton_clicked();

private:
    Ui::FoldersSettingDialog *ui;
    QStringList folders;
    QStringList oldFolders;
    QStringList defaultFolders;
    QList<AllowedAffix> allowedPrefix;
};

#endif // MONITORFOLDERSSETTINGDIALOG_H
