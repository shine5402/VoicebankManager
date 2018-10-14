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
