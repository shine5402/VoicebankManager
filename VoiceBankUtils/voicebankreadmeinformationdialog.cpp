#include "voicebankreadmeinformationdialog.h"
#include "ui_voicebankreadmeinformationdialog.h"

VoiceBankReadmeInformationDialog::VoiceBankReadmeInformationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoiceBankReadmeInformationDialog)
{
    ui->setupUi(this);
}

VoiceBankReadmeInformationDialog::~VoiceBankReadmeInformationDialog()
{
    delete ui;
}
