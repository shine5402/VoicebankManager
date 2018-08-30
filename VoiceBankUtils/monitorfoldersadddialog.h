#ifndef MONITORFOLDERSADDDIALOG_H
#define MONITORFOLDERSADDDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QCloseEvent>
namespace Ui {
    class MonitorFoldersAddDialog;
}

class MonitorFoldersAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorFoldersAddDialog(QWidget *parent = 0);
    ~MonitorFoldersAddDialog();
    QString getNewPath() const;
private slots:
    void on_exploreButton_clicked();
private:
    Ui::MonitorFoldersAddDialog *ui;
};

#endif // MONITORFOLDERSADDDIALOG_H
