#ifndef TEXTCODECSETTINGDIALOG_H
#define TEXTCODECSETTINGDIALOG_H

#include <QDialog>
#include "voicebank.h"
#include <availabletextcodecdialog.h>
#include <QTextCodec>
#include <QComboBox>
#include <public_defines.h>
namespace Ui {
    class TextCodecSettingDialog;
}

class TextCodecSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextCodecSettingDialog(QWidget *parent = nullptr,VoiceBank* voiceBank = nullptr);
    ~TextCodecSettingDialog();
    void setVoiceBank(VoiceBank* voiceBank);
    QTextCodec* getCharacterTextCodec();
    QTextCodec* getReadmeTextCodec();
    bool getIsFollowDefaultCodec();
    bool getIsAutoDetect();
private slots:

    void on_followDefaultTextCodecCheckBox_stateChanged(int state);

    void on_availableCodecButton_Character_clicked();

    void on_availableCodecButton_Readme_clicked();

    void on_autoDetectCheckBox_stateChanged(int state);

private:
    Ui::TextCodecSettingDialog *ui;
    VoiceBank* voiceBank = nullptr;

    void initUI();
    void setFormInDefault();
    void setFormInNoDefault();
    void setFormInAutoDetect();
    void setFormInNoAutoDetect();
};

#endif // TEXTCODECSETTINGDIALOG_H
