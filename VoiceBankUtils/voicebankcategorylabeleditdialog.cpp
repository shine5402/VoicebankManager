#include "voicebankcategorylabeleditdialog.h"
#include "ui_voicebankcategorylabeleditdialog.h"

VoicebankCategoryLabelEditDialog::VoicebankCategoryLabelEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoicebankCategoryLabelEditDialog)
{
    ui->setupUi(this);
}

VoicebankCategoryLabelEditDialog::~VoicebankCategoryLabelEditDialog()
{
    delete ui;
}
