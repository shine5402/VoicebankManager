#include "textcodecconvertdialog.h"
#include "ui_textcodecconvertdialog.h"

TextCodecConvertDialog::TextCodecConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextCodecConvertDialog)
{
    ui->setupUi(this);
}

TextCodecConvertDialog::~TextCodecConvertDialog()
{
    delete ui;
}
