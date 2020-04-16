#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QTextBrowser>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(const QString& applicationName,
                         const QIcon& applicationIcon,
                         const QString& aboutHtml,
                         const QString& authorHtml,
                         const QString& thanksHtml,
                         const QString& translatorsHtml,
                         const QString& licenseHtml,
                         const QString& thirdPartyLibraryHtml,
                         QWidget *parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog *ui;
    void setTab(int tabIndex, QTextBrowser* textBrowser, const QString& htmlString);
};

#endif // ABOUTDIALOG_H
