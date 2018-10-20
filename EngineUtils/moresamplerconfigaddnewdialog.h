#ifndef MORESAMPLERCONFIGADDNEWDIALOG_H
#define MORESAMPLERCONFIGADDNEWDIALOG_H

#include <QDialog>
#include "moresamplerconfigsaddnewmodel.h"
#include "moresamplerconfigreader.h"
namespace Ui {
    class MoresamplerConfigAddNewDialog;
}

class MoresamplerConfigAddNewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoresamplerConfigAddNewDialog(MoresamplerConfigReader* reader,QWidget *parent = nullptr);
    ~MoresamplerConfigAddNewDialog();
    QString getCurrentEntryName() const;
private slots:
    void on_tableView_doubleClicked(const QModelIndex &);

private:
    Ui::MoresamplerConfigAddNewDialog *ui;
    MoresamplerConfigsAddNewModel* model = nullptr;
};

#endif // MORESAMPLERCONFIGADDNEWDIALOG_H
