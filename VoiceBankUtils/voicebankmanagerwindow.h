#ifndef VOICEBANKMANAGERWINDOW_H
#define VOICEBANKMANAGERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include "voicebankhandler.h"
#include <QDebug>
#include "../GUIUtils/nofocusdelegate.h"
#include <QTableWidgetItem>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>
#include "monitorfolderssettingdialog.h"
#include "textcodecsettingdialog.h"
#include <QSettings>
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
    void readVoiceBanks();
    const static QString version;
public slots:
#ifndef NDEBUG
    void debug_voiceBank_readDone_Slot(VoiceBank *voiceBank);
#endif
    void voiceBankReadDoneSlot(VoiceBank *voiceBank);

private:
    Ui::VoiceBankManagerWindow *ui;
    QStringList monitorFolders = {u8"./voice"};
    VoiceBankHandler* voiceBankHandler = new VoiceBankHandler(this);
    QStringList getFoldersInMonitorFolders() const;
    void addVoiceBankRowInTableWidget(VoiceBank *voiceBank);
    void setVoiceBankInfomation(VoiceBank *voiceBank);
    int voiceBankPathsCount{};
    int voiceBankReadDoneCount{};
    struct TableColumn
    {
        static constexpr int Name = 0;
        static constexpr int Path = 1;
    };
    QHash<QTableWidgetItem*,VoiceBank*> voiceBankByTableItemFinder;
    QMenu* voiceBanksTableWidgetMenu = new QMenu(this);
    void createVoiceBanksTableMenu();

    void loadVoiceBanksList();
    
    void loadMonitorFoldersSettings();
    void saveMonitorFoldersSettings();
    void setUIAfterVoiceBanksReadDone();

private slots:
#ifndef NDEBUG
    void debugFunction();
#endif
    void on_voiceBanksTableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *);
    void on_voiceBanksTableWidget_customContextMenuRequested(const QPoint &);
    void openVoiceBankPathInExplorer();
    void openVoiceBankCharacterFileByOS();
    void openVoiceBankReadmeFileByOS();
    void copyVoiceBankPathtoClipboard();
    void copyVoiceBankCharacterFilePathtoClipboard();
    void copyVoiceBankReadmeFilePathtoClipboard();
    void on_actionMonitor_Folders_triggered();
    void on_actionRefresh_triggered();
    void on_actionDefault_TextCodec_triggered();
    void setCodecForVoiceBankActionSlot();
    void reloadVoiceBankActionSlot();
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
};

#endif // VOICEBANKMANAGERWINDOW_H
