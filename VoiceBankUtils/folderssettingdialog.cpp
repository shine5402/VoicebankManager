#include "folderssettingdialog.h"
#include "ui_folderssettingdialog.h"

FoldersSettingDialog::FoldersSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FoldersSettingDialog)
{
    ui->setupUi(this);

}

FoldersSettingDialog::FoldersSettingDialog(const QStringList &folders, const QString &label, const QString &title, QWidget *parent,const QStringList &defaultFolders) : FoldersSettingDialog(parent)
{
    setFolders(folders);
    setWindowTitle(title);
    setLabel(label);
    setDefaultFolders(defaultFolders);
}

FoldersSettingDialog::~FoldersSettingDialog()
{
    delete ui;
}

void FoldersSettingDialog::setFolders(const QStringList &folders)
{
    ui->foldersListWidget->clear();
    ui->foldersListWidget->addItems(folders);
    this->folders = folders;
    oldFolders = folders;
}

QStringList FoldersSettingDialog::getFolders() const
{
    return folders;
}

void FoldersSettingDialog::setLabel(const QString &label)
{
    ui->label->setText(label);
}

void FoldersSettingDialog::on_deleteButton_clicked()
{
    auto item_list = ui->foldersListWidget->selectedItems();
    for (auto item : item_list){
        ui->foldersListWidget->removeItemWidget(item);
        folders.removeOne(item->text());
        delete item;
    }
}

void FoldersSettingDialog::on_addButton_clicked()
{
    auto dialog = new FoldersAddDialog(this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted)
    {
        auto newPath = dialog->getNewPath();
        if (!newPath.isEmpty()){
            if (QDir(newPath).exists()){
                ui->foldersListWidget->addItem(newPath);
                folders.append(newPath);
            }
            else
                QMessageBox::warning(this,tr("路径不存在"),tr("您输入的路径不存在。文件夹列表将不做更改。"));
        }
        else
            QMessageBox::warning(this,tr("路径为空"),tr("您并没有输入路径。文件夹列表将不做更改。"));
    }
    dialog->deleteLater();
}

void FoldersSettingDialog::on_buttonBox_accepted()
{
    accept();
}

void FoldersSettingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    auto buttonType = ui->buttonBox->standardButton(button);
    switch (buttonType) {
    case QDialogButtonBox::Reset:
        ui->foldersListWidget->clear();
        ui->foldersListWidget->addItems(oldFolders);
        break;
    case QDialogButtonBox::RestoreDefaults:
        ui->foldersListWidget->clear();
        ui->foldersListWidget->addItems(defaultFolders);
        break;
    default:
        break;
    }
}

void FoldersSettingDialog::setDefaultFolders(const QStringList &value)
{
    defaultFolders = value;
}
