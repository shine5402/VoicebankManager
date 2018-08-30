#include "textcodecsettingdialog.h"
#include "ui_textcodecsettingdialog.h"

TextCodecSettingDialog::TextCodecSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextCodecSettingDialog)
{
    ui->setupUi(this);
}

TextCodecSettingDialog::~TextCodecSettingDialog()
{
    delete ui;
}

void TextCodecSettingDialog::setVoiceBank(VoiceBank *voiceBank)
{
    if (voiceBank)
        voiceBank = voiceBank;
    else
        ui->voiceBankLabel->setText(voiceBank->getName());
}
