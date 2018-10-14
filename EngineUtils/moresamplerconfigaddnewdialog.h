#ifndef MORESAMPLERCONFIGADDNEWDIALOG_H
#define MORESAMPLERCONFIGADDNEWDIALOG_H

#include <QDialog>
#include "moresamplerconfigsaddnewmodel.h"
namespace Ui {
    class MoresamplerConfigAddNewDialog;
}

class MoresamplerConfigAddNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerConfigAddNewDialog(QWidget *parent = nullptr);
    ~MoresamplerConfigAddNewDialog();
    QString getCurrentEntryName() const;
private:
    Ui::MoresamplerConfigAddNewDialog *ui;
    MoresamplerConfigsAddNewModel* model = nullptr;
};

#endif // MORESAMPLERCONFIGADDNEWDIALOG_H
