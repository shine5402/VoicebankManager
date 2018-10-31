#include "voicebankiconcropdialog.h"
#include "ui_voicebankiconcropdialog.h"

VoiceBankIconCropDialog::VoiceBankIconCropDialog(QImage image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoiceBankIconCropDialog),
    image(image)
{
    ui->setupUi(this);
    ui->imageCropper->setImage(QPixmap::fromImage(image));
}

VoiceBankIconCropDialog::~VoiceBankIconCropDialog()
{
    delete ui;
}
