#include "textcodecsettingdialog.h"
#include "ui_textcodecsettingdialog.h"

TextCodecSettingDialog::TextCodecSettingDialog(QWidget *parent, VoiceBank *voiceBank) :
    QDialog(parent),
    ui(new Ui::TextCodecSettingDialog),voiceBank(voiceBank)
{
    ui->setupUi(this);
    initUI();
}

TextCodecSettingDialog::~TextCodecSettingDialog()
{
    delete ui;
}

void TextCodecSettingDialog::setVoiceBank(VoiceBank *voiceBank)
{
    this->voiceBank = voiceBank;
    initUI();
}
void TextCodecSettingDialog::setFormInDefault()
{
    ui->characterTxtComboBox->setCurrentText(voiceBank->getDefaultCharacterTextCodec()->name());
    ui->readmeTxtComboBox->setCurrentText(voiceBank->getDefaultReadmeTextCodec()->name());
    ui->characterTxtComboBox->setEnabled(false);
    ui->characterTxtLabel->setEnabled(false);
    ui->readmeTxtComboBox->setEnabled(false);
    ui->readmeTxtLabel->setEnabled(false);
    ui->availableCodecButton_Character->setEnabled(false);
    ui->availableCodecButton_Readme->setEnabled(false);
    ui->autoDetectCheckBox->setEnabled(false);
}

void TextCodecSettingDialog::setFormInNoDefault()
{
    ui->characterTxtComboBox->setEnabled(true);
    ui->readmeTxtComboBox->setEnabled(true);
    ui->characterTxtLabel->setEnabled(true);
    ui->readmeTxtLabel->setEnabled(true);
    ui->availableCodecButton_Character->setEnabled(true);
    ui->availableCodecButton_Readme->setEnabled(true);
    ui->characterTxtComboBox->setCurrentText(voiceBank->getCharacterTextCodec()->name());
    ui->readmeTxtComboBox->setCurrentText(voiceBank->getReadmeTextCodec()->name());
    ui->autoDetectCheckBox->setEnabled(true);
}
void TextCodecSettingDialog::setFormInAutoDetect()
{
    if (voiceBank)
    {
    ui->characterTxtComboBox->setCurrentText(voiceBank->getDefaultCharacterTextCodec()->name());
    ui->readmeTxtComboBox->setCurrentText(voiceBank->getDefaultReadmeTextCodec()->name());
    ui->characterTxtComboBox->setEnabled(false);
    ui->characterTxtLabel->setEnabled(false);
    ui->readmeTxtComboBox->setEnabled(false);
    ui->readmeTxtLabel->setEnabled(false);
    ui->availableCodecButton_Character->setEnabled(false);
    ui->availableCodecButton_Readme->setEnabled(false);
    }
    else
    {
        ui->characterTxtLabel->setText(tr("（备选）character.txt的字符编码"));
        ui->readmeTxtLabel->setText(tr("（备选）readme.txt的字符编码"));
    }
}

void TextCodecSettingDialog::setFormInNoAutoDetect()
{
    if (voiceBank)
    {
    ui->characterTxtComboBox->setEnabled(true);
    ui->readmeTxtComboBox->setEnabled(true);
    ui->characterTxtLabel->setEnabled(true);
    ui->readmeTxtLabel->setEnabled(true);
    ui->availableCodecButton_Character->setEnabled(true);
    ui->availableCodecButton_Readme->setEnabled(true);
    ui->characterTxtComboBox->setCurrentText(voiceBank->getCharacterTextCodec()->name());
    ui->readmeTxtComboBox->setCurrentText(voiceBank->getReadmeTextCodec()->name());
    }
    else
    {
        ui->characterTxtLabel->setText(tr("character.txt的字符编码"));
        ui->readmeTxtLabel->setText(tr("readme.txt的字符编码"));
    }
}
void TextCodecSettingDialog::initUI(){
    if (voiceBank){
        ui->voiceBankLabel->setText(voiceBank->getName());
        setWindowTitle(tr("设定%1的读取用文本编码").arg(voiceBank->getName()));
        ui->followDefaultTextCodecCheckBox->setChecked(voiceBank->getIsFollowDefault());
        if (!voiceBank->getIsFollowDefault()){
            setFormInNoDefault();
            if (voiceBank->getIsTextCodecAutoDetect()){
                ui->autoDetectCheckBox->setChecked(true);
                setFormInAutoDetect();
            }
            else
                setFormInNoAutoDetect();
        }
        else
        {
            setFormInDefault();
            return;
        }
    }
    else
    {
        ui->voiceBankLabel->setText(tr("（默认编码）"));
        ui->followDefaultTextCodecCheckBox->setVisible(false);
        ui->characterTxtComboBox->setCurrentText(VoiceBank::getDefaultCharacterTextCodec()->name());
        ui->readmeTxtComboBox->setCurrentText(VoiceBank::getDefaultReadmeTextCodec()->name());
        ui->autoDetectCheckBox->setChecked(VoiceBank::getDefalutIsTextCodecAutoDetect());
    }
}

QTextCodec *TextCodecSettingDialog::getCharacterTextCodec()
{
    return QTextCodec::codecForName(ui->characterTxtComboBox->currentText().toUtf8());
}

QTextCodec *TextCodecSettingDialog::getReadmeTextCodec()
{
    return QTextCodec::codecForName(ui->readmeTxtComboBox->currentText().toUtf8());
}

bool TextCodecSettingDialog::getIsFollowDefaultCodec()
{
    return ui->followDefaultTextCodecCheckBox->isChecked();
}

bool TextCodecSettingDialog::getIsAutoDetect()
{
    return ui->autoDetectCheckBox->isChecked();
}



void TextCodecSettingDialog::on_followDefaultTextCodecCheckBox_stateChanged(int state)
{
    if (state == Qt::CheckState::Checked){
        setFormInDefault();
    }
    else if (state == Qt::CheckState::Unchecked){
        setFormInNoDefault();
    }
}


void TextCodecSettingDialog::on_availableCodecButton_Character_clicked()
{
    AvailableTextCodecDialog::onAvailbaleCodecButtonClicked(ui->characterTxtComboBox);
}

void TextCodecSettingDialog::on_availableCodecButton_Readme_clicked()
{
    AvailableTextCodecDialog::onAvailbaleCodecButtonClicked(ui->readmeTxtComboBox);
}

void TextCodecSettingDialog::on_autoDetectCheckBox_stateChanged(int state)
{
    if (state == Qt::CheckState::Checked){
        setFormInAutoDetect();
    }
    else if (state == Qt::CheckState::Unchecked){
        setFormInNoAutoDetect();
    }
}
