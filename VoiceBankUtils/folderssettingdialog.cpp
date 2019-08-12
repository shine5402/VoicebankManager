#include "folderssettingdialog.h"
#include "ui_folderssettingdialog.h"

FoldersSettingDialog::FoldersSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FoldersSettingDialog)
{
    ui->setupUi(this);
    ui->allowedPrefixDescriptionLabel->hide();
    ui->allowedPrefixDescriptionButton->hide();
}

FoldersSettingDialog::FoldersSettingDialog(const QStringList &folders, const QString &label, const QString &title, QWidget *parent, const QStringList &defaultFolders, const QList<AllowedPrefix>& allowedPrefix) : FoldersSettingDialog(parent)
{
    setFolders(folders);
    setWindowTitle(title);
    setLabel(label);
    setDefaultFolders(defaultFolders);
    setAllowedPrefix(allowedPrefix);

    if (!allowedPrefix.isEmpty()){
        auto text = tr("可用前缀：");
        ui->allowedPrefixDescriptionLabel->show();
        ui->allowedPrefixDescriptionButton->show();
        for (auto i : allowedPrefix)
        {
            text.append(i.prefix);
            if (!i.briefDescription.isEmpty())
                text.append(tr("（%1）").arg(i.briefDescription));
            text.append(tr("，"));
        }
        text.remove(text.count() - 1,1);
        ui->allowedPrefixDescriptionLabel->setText(text);
    }
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
    ui->descriptionLabel->setText(label);
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
            QString newPath2 = newPath;
            for (auto prefix : allowedPrefix){
                if (newPath.startsWith(prefix.prefix)){
                    newPath.remove(prefix.prefix);
                }
            }
            if (QDir(newPath).exists()){
                ui->foldersListWidget->addItem(newPath2);
                folders.append(newPath2);
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

void FoldersSettingDialog::setAllowedPrefix(const QList<AllowedPrefix>& value)
{
    allowedPrefix = value;
}

void FoldersSettingDialog::setDefaultFolders(const QStringList &value)
{
    defaultFolders = value;
}

void FoldersSettingDialog::on_allowedPrefixDescriptionButton_clicked()
{
    QString text;
    for (auto i : allowedPrefix)
    {
        text.append(tr("<p><b>后缀</b>：%1<br/><b>描述</b>：%2</p>").arg(i.prefix).arg(i.description));
    }
    auto htmlDialog = ShowHTMLDialog(text,tr("允许使用的后缀列表"),this);
    htmlDialog.exec();
}
