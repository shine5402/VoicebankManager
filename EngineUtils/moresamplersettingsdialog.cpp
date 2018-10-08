#include "moresamplersettingsdialog.h"
#include "ui_moresamplersettingsdialog.h"

MoresamplerSettingsDialog::MoresamplerSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoresamplerSettingsDialog)
{
    ui->setupUi(this);
}

MoresamplerSettingsDialog::~MoresamplerSettingsDialog()
{
    delete ui;
}
