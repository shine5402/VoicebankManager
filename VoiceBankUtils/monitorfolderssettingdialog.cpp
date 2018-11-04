#include "monitorfolderssettingdialog.h"
#include "ui_monitorfolderssettingdialog.h"

MonitorFoldersSettingDialog::MonitorFoldersSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorFoldersSettingDialog)
{
    ui->setupUi(this);

}

MonitorFoldersSettingDialog::~MonitorFoldersSettingDialog()
{
    delete ui;
}

void MonitorFoldersSettingDialog::setMonitorFolders(QStringList monitorFolders)
{
    ui->monitorFoldersListWidget->clear();
    ui->monitorFoldersListWidget->addItems(monitorFolders);
    this->monitorFolders = monitorFolders;
    oldMonitorFolders = monitorFolders;
}

QStringList MonitorFoldersSettingDialog::getMonitorFolders() const
{
    return monitorFolders;
}

void MonitorFoldersSettingDialog::on_deleteButton_clicked()
{
    auto item_list = ui->monitorFoldersListWidget->selectedItems();
    for (auto item : item_list){
        ui->monitorFoldersListWidget->removeItemWidget(item);
        monitorFolders.removeOne(item->text());
        delete item;
    }
}

void MonitorFoldersSettingDialog::on_addButton_clicked()
{
    auto dialog = new MonitorFoldersAddDialog(this);
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted)
    {
        auto newPath = dialog->getNewPath();
        if (!newPath.isEmpty()){
            if (QDir(newPath).exists()){
                ui->monitorFoldersListWidget->addItem(newPath);
                monitorFolders.append(newPath);
            }
            else
                QMessageBox::warning(this,tr("路径不存在"),tr("您输入的路径不存在。监视文件夹列表将不做更改。"));
        }
        else
            QMessageBox::warning(this,tr("路径为空"),tr("您并没有输入路径。监视文件夹列表将不做更改。"));
    }
    dialog->deleteLater();
}

void MonitorFoldersSettingDialog::on_buttonBox_accepted()
{
    accept();
}

void MonitorFoldersSettingDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    auto buttonType = ui->buttonBox->standardButton(button);
    switch (buttonType) {
    case QDialogButtonBox::Reset:
        ui->monitorFoldersListWidget->clear();
        ui->monitorFoldersListWidget->addItems(oldMonitorFolders);
        break;
    case QDialogButtonBox::RestoreDefaults:
        ui->monitorFoldersListWidget->clear();
        ui->monitorFoldersListWidget->addItems(defaultMonitorFolders);
        break;
    default:
        break;
    }
}
