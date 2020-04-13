#ifndef VOICEBANKICONCROPDIALOG_H
#define VOICEBANKICONCROPDIALOG_H

#include <QDialog>
#include <imagecroppercontainer.h>
#include "voicebank.h"
#include <public_defines.h>
namespace Ui {
class VoicebankIconCropDialog;
}

class VoicebankIconCropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoicebankIconCropDialog(Voicebank* voicebank,QString newImagePath,QWidget *parent = nullptr);
    ~VoicebankIconCropDialog() override;

private slots:

protected:
    void accept() override;
private:
    Ui::VoicebankIconCropDialog *ui;
    QImage image;
    Voicebank* voicebank = nullptr;
};

#endif // VOICEBANKICONCROPDIALOG_H
