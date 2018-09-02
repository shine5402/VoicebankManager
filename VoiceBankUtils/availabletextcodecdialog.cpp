#include "availabletextcodecdialog.h"
#include "ui_availabletextcodecdialog.h"

AvailableTextCodecDialog::AvailableTextCodecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvailableTextCodecDialog)
{
    ui->setupUi(this);
    auto availableTextCodecs = QTextCodec::availableCodecs();
    for (auto string : availableTextCodecs){
        availableTextCodecsStringList.append(string);
    }
    ui->listWidget->addItems(availableTextCodecsStringList);
    ui->listWidget->addAction(ui->actionCopyTextCodec);
}

AvailableTextCodecDialog::~AvailableTextCodecDialog()
{
    delete ui;
}

void AvailableTextCodecDialog::on_lineEdit_textChanged(const QString &arg1)
{
    if (!arg1.isEmpty()){
        ui->listWidget->clear();
        QStringList newList{};
        for (auto string : availableTextCodecsStringList){
            if (string.contains(arg1,Qt::CaseInsensitive)){
                newList.append(string);
            }
        }
        ui->listWidget->addItems(newList);
    }
    else
        ui->listWidget->addItems(availableTextCodecsStringList);

}

void AvailableTextCodecDialog::on_actionCopyTextCodec_triggered()
{
    auto name = ui->listWidget->currentItem()->text();
    QApplication::clipboard()->setText(name);
}
