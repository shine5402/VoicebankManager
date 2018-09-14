#ifndef TEXTCODECCONVERTDIALOG_H
#define TEXTCODECCONVERTDIALOG_H

#include <QDialog>

namespace Ui {
    class TextCodecConvertDialog;
}

class TextCodecConvertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextCodecConvertDialog(QWidget *parent = nullptr);
    ~TextCodecConvertDialog();

private:
    Ui::TextCodecConvertDialog *ui;
};

#endif // TEXTCODECCONVERTDIALOG_H
