#ifndef MORESAMPLERCONFIGSDIALOG_H
#define MORESAMPLERCONFIGSDIALOG_H

#include <QDialog>
#include "moresamplerconfigreader.h"
#include "moresamplerconfigsmodel.h"
#include "moresamplerconfigsdelegate.h"
#include <QMessageBox>
#include "moresamplerconfigaddnewdialog.h"
#include <QInputDialog>
namespace Ui {
class MoresamplerConfigsDialog;
}

class MoresamplerConfigsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerConfigsDialog(const QString& path, const MoresamplerConfigReader::ConfigFileType configFileType, QWidget *parent = nullptr, QString voiceBankName = QString());
    ~MoresamplerConfigsDialog() override;

private slots:
    void on_deleteButton_clicked();

    void on_addButton_clicked();
public slots:
    void accept() override;
    void onInvalidValue(int row, QVariant data);
private:
    Ui::MoresamplerConfigsDialog *ui;
    QString path;
    MoresamplerConfigReader* reader = nullptr;
    MoresamplerConfigsModel* model = nullptr;
};

#endif // MORESAMPLERCONFIGSDIALOG_H
