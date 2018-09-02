#ifndef AVAILABLETEXTCODECDIALOG_H
#define AVAILABLETEXTCODECDIALOG_H

#include <QDialog>
#include <QTextCodec>
#include <QStringList>
#include <QClipboard>

namespace Ui {
    class AvailableTextCodecDialog;
}

class AvailableTextCodecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AvailableTextCodecDialog(QWidget *parent = 0);
    ~AvailableTextCodecDialog();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_actionCopyTextCodec_triggered();

private:
    Ui::AvailableTextCodecDialog *ui;
    QStringList availableTextCodecsStringList{};
};

#endif // AVAILABLETEXTCODECDIALOG_H
