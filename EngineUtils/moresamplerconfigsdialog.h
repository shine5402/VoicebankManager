#ifndef MORESAMPLERCONFIGSDIALOG_H
#define MORESAMPLERCONFIGSDIALOG_H

#include <QDialog>
#include "moresamplerconfigreader.h"
#include "moresamplerconfigsmodel.h"
namespace Ui {
class MoresamplerConfigsDialog;
}

class MoresamplerConfigsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerConfigsDialog(const QString& path,QWidget *parent = nullptr);
    ~MoresamplerConfigsDialog();

private:
    Ui::MoresamplerConfigsDialog *ui;
    QString path;
    MoresamplerConfigReader* reader = nullptr;
    MoresamplerConfigsModel* model = nullptr;
};

#endif // MORESAMPLERCONFIGSDIALOG_H
