#include "moresamplerconfigsdialog.h"
#include "ui_moresamplerconfigsdialog.h"

MoresamplerConfigsDialog::MoresamplerConfigsDialog(const QString &path, const MoresamplerConfigReader::ConfigFileType configFileType,QWidget *parent,QString voiceBankName) :
    QDialog(parent),
    ui(new Ui::MoresamplerConfigsDialog),path(path)
{
    ui->setupUi(this);
    reader = new MoresamplerConfigReader(path,configFileType,this);
    model = new MoresamplerConfigsModel(reader);
    ui->configTableView->setModel(model);
    ui->configTableView->resizeColumnsToContents();
    ui->configTableView->setItemDelegate(new MoresamplerConfigsDelegate(reader,this));
    if (configFileType == MoresamplerConfigReader::ConfigFileType::VoiceBank)
    {
        if (!voiceBankName.isEmpty())
            setWindowTitle(tr(u8"编辑“%1”的Moresampler配置").arg(voiceBankName));
        else
            setWindowTitle(tr(u8"编辑名称位置的音源的Moresampler配置"));
    }
    else
        setWindowTitle(tr(u8"编辑全局Moresampler配置"));

}

MoresamplerConfigsDialog::~MoresamplerConfigsDialog()
{
    delete ui;
}

void MoresamplerConfigsDialog::on_deleteButton_clicked()
{
    if (reader->getCount() > 0)
        model->removeConfig(ui->configTableView->currentIndex().row());
    else
        QMessageBox::warning(this,tr(u8"没有可删除的项"),tr(u8"当前配置文件的配置项目数为0，所以无法删除项目。"));
}

void MoresamplerConfigsDialog::on_addButton_clicked()
{
    auto dialog = new MoresamplerConfigAddNewDialog(this);
    dialog->exec();
}
