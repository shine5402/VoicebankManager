#ifndef MORESAMPLERSETTINGSDIALOG_H
#define MORESAMPLERSETTINGSDIALOG_H

#include <QDialog>
#include "moresamplerconfigreader.h"
#include "moresamplersettingsmodel.h"
namespace Ui {
class MoresamplerSettingsDialog;
}

class MoresamplerSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerSettingsDialog(const QString& path,QWidget *parent = nullptr);
    ~MoresamplerSettingsDialog();

private:
    Ui::MoresamplerSettingsDialog *ui;
    QString path;
    MoresamplerConfigReader* reader = nullptr;
    MoresamplerSettingsModel* model = nullptr;
};

#endif // MORESAMPLERSETTINGSDIALOG_H
