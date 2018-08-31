#ifndef AVAILABLETEXTCODECDIALOG_H
#define AVAILABLETEXTCODECDIALOG_H

#include <QDialog>

namespace Ui {
    class AvailableTextCodecDialog;
}

class AvailableTextCodecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AvailableTextCodecDialog(QWidget *parent = 0);
    ~AvailableTextCodecDialog();

private:
    Ui::AvailableTextCodecDialog *ui;
};

#endif // AVAILABLETEXTCODECDIALOG_H
