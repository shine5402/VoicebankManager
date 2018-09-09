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
}

void TextCodecSettingDialog::initUI(){
    if (voiceBank){
        ui->voiceBankLabel->setText(voiceBank->getName());
        setWindowTitle(tr(u8"设定%1的读取用文本编码").arg(voiceBank->getName()));
        ui->followDefaultTextCodecCheckBox->setChecked(voiceBank->getIsFollowDefault());
        if (!voiceBank->getIsFollowDefault()){
            setFormInNoDefault();
        }
        else
        {
            setFormInDefault();
        }
    }
    else
    {
        ui->voiceBankLabel->setText(tr(u8"（默认编码）"));
        ui->followDefaultTextCodecCheckBox->setVisible(false);
        ui->followDefaultTextCodecLabel->setVisible(false);
        ui->characterTxtComboBox->setCurrentText(VoiceBank::getDefaultCharacterTextCodec()->name());
        ui->readmeTxtComboBox->setCurrentText(VoiceBank::getDefaultReadmeTextCodec()->name());
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



void TextCodecSettingDialog::on_followDefaultTextCodecCheckBox_stateChanged(int state)
{
    if (state == Qt::CheckState::Checked){
        setFormInDefault();
    }
    else if (state == Qt::CheckState::Unchecked){
        setFormInNoDefault();
    }
}

void TextCodecSettingDialog::onAvailbaleCodecButtonClicked(QComboBox* comboBox)
{
    auto dialog = new AvailableTextCodecDialog();
    auto dialogCode = dialog->exec();
    if (dialogCode == QDialog::Accepted)
    {
        auto newCodecString = dialog->getSelectedCodecName();
        if (QTextCodec::codecForName(newCodecString.toUtf8()) != nullptr)
            comboBox->setCurrentText(newCodecString);}
    dialog->deleteLater();
}

void TextCodecSettingDialog::on_availableCodecButton_Character_clicked()
{
    onAvailbaleCodecButtonClicked(ui->characterTxtComboBox);
}

void TextCodecSettingDialog::on_availableCodecButton_Readme_clicked()
{
    onAvailbaleCodecButtonClicked(ui->readmeTxtComboBox);
}
