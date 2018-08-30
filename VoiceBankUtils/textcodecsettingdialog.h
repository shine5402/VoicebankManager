#ifndef TEXTCODECSETTINGDIALOG_H
#define TEXTCODECSETTINGDIALOG_H

#include <QDialog>
#include "voicebank.h"
namespace Ui {
    class TextCodecSettingDialog;
}

class TextCodecSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextCodecSettingDialog(QWidget *parent = 0);
    ~TextCodecSettingDialog();
    void setVoiceBank(VoiceBank* voiceBank);
private:
    Ui::TextCodecSettingDialog *ui;
    VoiceBank* voiceBank = nullptr;
};

#endif // TEXTCODECSETTINGDIALOG_H
