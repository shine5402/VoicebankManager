#ifndef MORESAMPLERCONFIGSDIALOG_H
#define MORESAMPLERCONFIGSDIALOG_H

#include <QDialog>
#include "moresamplerconfigreader.h"
#include "moresamplerconfigsmodel.h"
#include "moresamplerconfigsdelegate.h"
#include <QMessageBox>
namespace Ui {
class MoresamplerConfigsDialog;
}

class MoresamplerConfigsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerConfigsDialog(const QString& path, const MoresamplerConfigReader::ConfigFileType configFileType, QWidget *parent = nullptr, QString voiceBankName = QString());
    ~MoresamplerConfigsDialog();

private slots:
    void on_deleteButton_clicked();

private:
    Ui::MoresamplerConfigsDialog *ui;
    QString path;
    MoresamplerConfigReader* reader = nullptr;
    MoresamplerConfigsModel* model = nullptr;
};

#endif // MORESAMPLERCONFIGSDIALOG_H
