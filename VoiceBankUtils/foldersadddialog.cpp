#include "foldersadddialog.h"
#include "ui_foldersadddialog.h"
FoldersAddDialog::FoldersAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FoldersAddDialog)
{
    ui->setupUi(this);
}

FoldersAddDialog::~FoldersAddDialog()
{
    delete ui;
}

QString FoldersAddDialog::getNewPath() const
{
    return ui->pathLineEdit->text();
}

void FoldersAddDialog::on_exploreButton_clicked()
{
    auto path = QFileDialog::getExistingDirectory(this,tr("选择一个文件夹"),QString(),QFileDialog::ShowDirsOnly);
    if (!path.isEmpty())
        ui->pathLineEdit->setText(path);
}
