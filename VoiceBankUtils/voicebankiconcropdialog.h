#ifndef VOICEBANKICONCROPDIALOG_H
#define VOICEBANKICONCROPDIALOG_H

#include <QDialog>
#include "../ImageCropper/src/imagecroppercontainer.h"
namespace Ui {
class VoiceBankIconCropDialog;
}

class VoiceBankIconCropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoiceBankIconCropDialog(QImage image,QWidget *parent = nullptr);
    ~VoiceBankIconCropDialog();

private:
    Ui::VoiceBankIconCropDialog *ui;
    QImage image;
};

#endif // VOICEBANKICONCROPDIALOG_H
