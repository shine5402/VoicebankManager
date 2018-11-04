#include "voicebankiconcropdialog.h"
#include "ui_voicebankiconcropdialog.h"

VoiceBankIconCropDialog::VoiceBankIconCropDialog(VoiceBank *voicebank, QString newImagePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoiceBankIconCropDialog),
    image(QImage(newImagePath)),voicebank(voicebank)
{
    ui->setupUi(this);
    ui->imageCropper->setImage(QPixmap::fromImage(image));
    setWindowTitle(tr("为音源库“%1”设定新图标").arg(voicebank->getName()));
}

VoiceBankIconCropDialog::~VoiceBankIconCropDialog()
{
    delete ui;
}

void VoiceBankIconCropDialog::accept()
{
    voicebank->changeImage(ui->imageCropper->cropImage(),ui->targetFileNameLineEdit->text());
    QDialog::accept();
}
