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
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted)
    {
        auto name = dialog->getCurrentEntryName();
        if (name == tr(u8"（空行）"))
            name = QString();
        else if (name == tr(u8"（注释）"))
            name = u8"#";
        else if (name == tr(u8"（元标记）"))
        {
            bool ok = false;
            auto num = QInputDialog::getInt(this,tr(u8"指定元标记的序数"),tr(u8"在下面的输入框中输入一个数字。该数字将作为调用元标记时应当使用的系数。比如，您想要使用M1，就在下框中输入1."),1,1,100,1,&ok);
            if (ok)
            {
                name = QString(u8"meta-flag-%1").arg(num);
            }
            else
                return;
        }
        model->addConfig(name);
    }
}

void MoresamplerConfigsDialog::accept()
{
    reader->saveConfigs();
    QDialog::accept();
}
