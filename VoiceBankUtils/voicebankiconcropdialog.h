#ifndef VOICEBANKICONCROPDIALOG_H
#define VOICEBANKICONCROPDIALOG_H

#include <QDialog>
#include "../ImageCropper/src/imagecroppercontainer.h"
#include "voicebank.h"
#include <public_defines.h>
namespace Ui {
class VoiceBankIconCropDialog;
}

class VoiceBankIconCropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoiceBankIconCropDialog(VoiceBank* voicebank,QString newImagePath,QWidget *parent = nullptr);
    ~VoiceBankIconCropDialog() override;

private slots:

protected:
    void accept() override;
private:
    Ui::VoiceBankIconCropDialog *ui;
    QImage image;
    VoiceBank* voicebank = nullptr;
};

#endif // VOICEBANKICONCROPDIALOG_H
