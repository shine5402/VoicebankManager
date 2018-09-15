#ifndef TEXTCODECSETTINGDIALOG_H
#define TEXTCODECSETTINGDIALOG_H

#include <QDialog>
#include "voicebank.h"
#include "./TextCodecUtils/availabletextcodecdialog.h"
#include <QTextCodec>
#include <QComboBox>
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
private slots:

    void on_followDefaultTextCodecCheckBox_stateChanged(int state);

    void on_availableCodecButton_Character_clicked();

    void on_availableCodecButton_Readme_clicked();

private:
    Ui::TextCodecSettingDialog *ui;
    VoiceBank* voiceBank = nullptr;

    void initUI();
    void setFormInDefault();
    void setFormInNoDefault();
};

#endif // TEXTCODECSETTINGDIALOG_H
