#include "moresamplerconfigsdialog.h"
#include "ui_moresamplerconfigsdialog.h"

MoresamplerConfigsDialog::MoresamplerConfigsDialog(const QString &path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoresamplerConfigsDialog),path(path)
{
    ui->setupUi(this);
    reader = new MoresamplerConfigReader(path,MoresamplerConfigReader::ConfigFileType::VoiceBank,this);
    model = new MoresamplerConfigsModel(reader);
    ui->configTableView->setModel(model);
    ui->configTableView->resizeColumnsToContents();
}

MoresamplerConfigsDialog::~MoresamplerConfigsDialog()
{
    delete ui;
}
