#include "moresamplersettingsdialog.h"
#include "ui_moresamplersettingsdialog.h"

MoresamplerSettingsDialog::MoresamplerSettingsDialog(const QString &path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoresamplerSettingsDialog),path(path)
{
    ui->setupUi(this);
    reader = new MoresamplerConfigReader(path,MoresamplerConfigReader::ConfigFileType::VoiceBank,this);
    model = new MoresamplerSettingsModel(reader);
    ui->configTableView->setModel(model);
    ui->configTableView->resizeColumnsToContents();
}

MoresamplerSettingsDialog::~MoresamplerSettingsDialog()
{
    delete ui;
}
