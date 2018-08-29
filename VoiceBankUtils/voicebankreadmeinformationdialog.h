#ifndef VOICEBANKREADMEINFORMATIONDIALOG_H
#define VOICEBANKREADMEINFORMATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class VoiceBankReadmeInformationDialog;
}

class VoiceBankReadmeInformationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoiceBankReadmeInformationDialog(QWidget *parent = nullptr);
    ~VoiceBankReadmeInformationDialog();

private:
    Ui::VoiceBankReadmeInformationDialog *ui;
};

#endif // VOICEBANKREADMEINFORMATIONDIALOG_H
