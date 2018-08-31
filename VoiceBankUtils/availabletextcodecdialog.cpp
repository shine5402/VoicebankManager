#include "availabletextcodecdialog.h"
#include "ui_availabletextcodecdialog.h"

AvailableTextCodecDialog::AvailableTextCodecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvailableTextCodecDialog)
{
    ui->setupUi(this);
}

AvailableTextCodecDialog::~AvailableTextCodecDialog()
{
    delete ui;
}
