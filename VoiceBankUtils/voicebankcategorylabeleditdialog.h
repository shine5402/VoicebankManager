#ifndef VOICEBANKCATEGORYLABELEDITDIALOG_H
#define VOICEBANKCATEGORYLABELEDITDIALOG_H

#include <QDialog>
#include "voicebankcategoryeditormodel.h"

namespace Ui {
class VoicebankCategoryLabelEditDialog;
}

class VoicebankCategoryLabelEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VoicebankCategoryLabelEditDialog(VoicebankCategoryEditorModel* model, QWidget *parent = nullptr);
    ~VoicebankCategoryLabelEditDialog();

private:
    Ui::VoicebankCategoryLabelEditDialog *ui;
    VoicebankCategoryEditorModel* model;
};

#endif // VOICEBANKCATEGORYLABELEDITDIALOG_H
