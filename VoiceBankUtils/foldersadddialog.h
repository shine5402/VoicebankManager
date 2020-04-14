#ifndef MONITORFOLDERSADDDIALOG_H
#define MONITORFOLDERSADDDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QCloseEvent>
#include <public_defines.h>
namespace Ui {
    class FoldersAddDialog;
}

class FoldersAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FoldersAddDialog(QWidget *parent = nullptr);
    ~FoldersAddDialog();
    QString getNewPath() const;
    void setCurrentPath(const QString&newPath);
private slots:
    void on_exploreButton_clicked();
private:
    Ui::FoldersAddDialog *ui;
};

#endif // MONITORFOLDERSADDDIALOG_H
