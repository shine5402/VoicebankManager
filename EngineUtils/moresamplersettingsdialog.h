#ifndef MORESAMPLERSETTINGSDIALOG_H
#define MORESAMPLERSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class MoresamplerSettingsDialog;
}

class MoresamplerSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerSettingsDialog(QWidget *parent = nullptr);
    ~MoresamplerSettingsDialog();

private:
    Ui::MoresamplerSettingsDialog *ui;
};

#endif // MORESAMPLERSETTINGSDIALOG_H
