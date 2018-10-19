#include "moresamplerconfigaddnewdialog.h"
#include "ui_moresamplerconfigaddnewdialog.h"

MoresamplerConfigAddNewDialog::MoresamplerConfigAddNewDialog(MoresamplerConfigReader *reader, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoresamplerConfigAddNewDialog)
{
    ui->setupUi(this);
    model = new MoresamplerConfigsAddNewModel(reader,this);
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

MoresamplerConfigAddNewDialog::~MoresamplerConfigAddNewDialog()
{
    delete ui;
}

QString MoresamplerConfigAddNewDialog::getCurrentEntryName() const
{
    return model->data(model->index(ui->tableView->currentIndex().row(),0)).toString();
}
