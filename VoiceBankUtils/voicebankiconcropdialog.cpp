#include "voicebankiconcropdialog.h"
#include "ui_voicebankiconcropdialog.h"

VoiceBankIconCropDialog::VoiceBankIconCropDialog(VoiceBank *voicebank, QString newImagePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoiceBankIconCropDialog),
    image(QImage(newImagePath)),voicebank(voicebank)
{
    ui->setupUi(this);
    ui->imageCropper->setImage(QPixmap::fromImage(image));
}

VoiceBankIconCropDialog::~VoiceBankIconCropDialog()
{
    delete ui;
}

void VoiceBankIconCropDialog::accept()
{
    voicebank->changeImage(ui->imageCropper->cropImage());
    QDialog::accept();
}
