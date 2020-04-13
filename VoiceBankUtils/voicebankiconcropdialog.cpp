﻿#include "voicebankiconcropdialog.h"
#include "ui_voicebankiconcropdialog.h"

VoicebankIconCropDialog::VoicebankIconCropDialog(Voicebank *voicebank, QString newImagePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoicebankIconCropDialog),
    image(QImage(newImagePath)),voicebank(voicebank)
{
    ui->setupUi(this);
    ui->imageCropper->setImage(QPixmap::fromImage(image));
    setWindowTitle(tr("为音源库“%1”设定新图标").arg(voicebank->getName()));
}

VoicebankIconCropDialog::~VoicebankIconCropDialog()
{
    delete ui;
}

void VoicebankIconCropDialog::accept()
{
    voicebank->setImage(ui->imageCropper->cropImage().toImage(),ui->targetFileNameLineEdit->text().isEmpty() ? "icon.jpg" : ui->targetFileNameLineEdit->text());
    QDialog::accept();
}
