#ifndef VOICEBANKCATEGORYLABELEDITDIALOG_H
#define VOICEBANKCATEGORYLABELEDITDIALOG_H

#include <QDialog>

namespace Ui {
class VoicebankCategoryLabelEditDialog;
}

class VoicebankCategoryLabelEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoicebankCategoryLabelEditDialog(QWidget *parent = nullptr);
    ~VoicebankCategoryLabelEditDialog();

private:
    Ui::VoicebankCategoryLabelEditDialog *ui;
};

#endif // VOICEBANKCATEGORYLABELEDITDIALOG_H
