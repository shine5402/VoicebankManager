#ifndef VOICEBANKMANAGERWINDOW_H
#define VOICEBANKMANAGERWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include "voicebankhandler.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QClipboard>
#include "monitorfolderssettingdialog.h"
#include "textcodecsettingdialog.h"
#include <QSettings>
#include <public_defines.h>
#include "TextCodecUtils/textcodecconvertdialog.h"
#include <QPair>
#include <QInputDialog>
#include "voicebanktablemodel.h"
#include "EngineUtils/moresamplerconfigreader.h"
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
    void loadVoiceBanksList();
public slots:
#ifndef NDEBUG
    void debug_voiceBank_readDone_Slot(VoiceBank *);
#endif
    void voiceBankReadDoneSlot(VoiceBank *voiceBank);

private:
    Ui::VoiceBankManagerWindow *ui;
    QStringList monitorFolders = {u8"./voice"};
    VoiceBankHandler* voiceBankHandler = new VoiceBankHandler(this);
    VoiceBankTableModel* voiceBankTableModel = nullptr;
    QStringList getFoldersInMonitorFolders() const;
    void setVoiceBankInfomation(VoiceBank *voiceBank);
    int voiceBankPathsCount{};
    int voiceBankReadDoneCount{};
    struct TableColumn
    {
        static constexpr int Name = 0;
        static constexpr int Path = 1;
    };
    QMenu* voiceBanksTableWidgetMenu = new QMenu(this);
    void createVoiceBanksTableMenu();
    void loadMonitorFoldersSettings();
    void saveMonitorFoldersSettings();
    void setUIAfterVoiceBanksReadDone();

    QPair<bool, QTextCodec *> processFileTextCodecConvert(const QString &path, QTextCodec *sourceCodec, QTextCodec *targetCodec);
    VoiceBank *getSelectedVoiceBank();

    VoiceBank *getSelectedVoiceBank(const QModelIndex &current);
private slots:
#ifndef NDEBUG
    void debugFunction();
#endif
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
    void convertCharacterCodecActionSlot();
    void convertReadmeCodecActionSlot();
    void on_actionSet_Thread_Pool_Max_Count_triggered();
    void convertWavFileNameCodecActionSlot();
    void on_voiceBanksTableView_customContextMenuRequested(const QPoint &);
    void onVoiceBankViewCurrentChanged(const QModelIndex &, const QModelIndex &);
};

#endif // VOICEBANKMANAGERWINDOW_H
