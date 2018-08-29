#ifndef VOICEBANKMANAGERWINDOW_H
#define VOICEBANKMANAGERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include "voicebankhandler.h"
#include <QDebug>
namespace Ui {
    class VoiceBankManagerWindow;
}

class VoiceBankManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VoiceBankManagerWindow(QWidget *parent = nullptr);
    ~VoiceBankManagerWindow();

    QStringList getMonitorFolders() const;
    void setMonitorFolders(const QStringList &value);

public slots:
#ifndef NDEBUG
    void debug_voiceBank_readDone_Slot(VoiceBank *voiceBank);
#endif
private:
    Ui::VoiceBankManagerWindow *ui;
    QStringList monitorFolders = {u8"./voice"};
    VoiceBankHandler* voiceBankhandler = new VoiceBankHandler(this);
private slots:
#ifndef NDEBUG
    void debugFunction();
#endif
};

#endif // VOICEBANKMANAGERWINDOW_H
