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
#include "EngineUtils/moresamplerconfigsdialog.h"
#include <QDir>
#include <QFileInfo>
#include <QRandomGenerator>
#include "voicebankiconcropdialog.h"
#include <QImageReader>
#include <QMediaPlayer>
#include <QProgressBar>
#include <QTranslator>
#include "./TextCodecUtils/qchardet.h"
#include "categoriesandlabelslistwidget.h"

namespace Ui {
class VoiceBankManagerWindow;
}

class VoiceBankManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VoiceBankManagerWindow(QWidget *parent = nullptr);
    ~VoiceBankManagerWindow() override;

    QStringList getMonitorFolders() const;
    void setMonitorFolders(const QStringList &value);
    void readVoiceBanks();
    void loadVoiceBanksList();
public slots:
#ifndef NDEBUG
    void debug_voiceBank_readDone_Slot(VoiceBank *);
#endif
    void voiceBankReadDoneSlot(VoiceBank *voiceBank);

    void onSamplePlayerPositionChange(qint64 position);
    void onSamplePlayerStateChanged(QMediaPlayer::State state);
    void createVoiceBanksCategoriesSubMenu();

protected:
    void changeEvent(QEvent *e) override;
private:
    Ui::VoiceBankManagerWindow *ui;

    QStringList monitorFolders = {"./voice"};
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
    QMenu* voiceBankCategoriesSubMenu = new QMenu(tr("分类"),this);
    QActionGroup* voiceBankCategoriesActionGroup = new QActionGroup(this);
    QMenu* voiceBankLabelsSubMenu = new QMenu(tr("标签"),this);
    QActionGroup* voiceBankLabelsActionGroup = new QActionGroup(this);

    void createVoiceBanksTableMenu();
    void loadMonitorFoldersSettings();
    void saveMonitorFoldersSettings();
    void setUIAfterVoiceBanksReadDone();

    QPair<bool, QTextCodec *> processFileTextCodecConvert(const QString &path, QTextCodec *sourceCodec, QTextCodec *targetCodec);
    VoiceBank *getSelectedVoiceBank();
    VoiceBank *getSelectedVoiceBank(const QModelIndex &current);
    QProgressBar* samplePlayerProgress = new QProgressBar();
    QMediaPlayer* samplePlayer = new QMediaPlayer(this);
    void autoDetectTranslate();
    QList<QTranslator*> translators;
    void removeAllTranslators();
    bool processFileNameConvert(QByteArrayList _fileNameRaw, QStringList _filePaths, QString title, QTextCodec *rawCodec, QTextCodec *targetCodec);
    CategoriesAndLabelsListWidget* categoriesAndLabelsListWidget = new CategoriesAndLabelsListWidget(voiceBankHandler,this);

    QString currentCategoryFilter;
    QString currentLabelFilter;
    void showVoiceBanksRows(const QList<int> &voiceBankIDs);
    void dealFilters();
    QList<int> getIntersection(QList<QList<int> > lists);
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
    void on_searchLineEdit_textChanged(const QString &);
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void convertCharacterCodecActionSlot();
    void convertReadmeCodecActionSlot();
    void on_actionSet_Thread_Pool_Max_Count_triggered();
    void convertWavFileNameCodecActionSlot();
    void on_voiceBanksTableView_customContextMenuRequested(const QPoint &);
    void onVoiceBankViewCurrentChanged(const QModelIndex &, const QModelIndex &);
    void moresamplerConfigEditActionSlot();
    void on_actionEdit_Global_MoresamplerConfig_triggered();
    void modifyNameActionSlot();
    void modifyIconActionSlot();
    void on_actionchoose_a_voicebank_randomly_triggered();
    void onBackupImageFileBecauseExists(VoiceBank * voicebank);
    void onCannotBackupImageFile(VoiceBank* voicebank);
    void on_playSamplebutton_clicked();
    void dealLanguageMenuAutoAndDontStates();
    void dealLanguageMenuLoadFile();
    void on_actionFor_text_file_triggered();
    void on_actionFor_File_Name_triggered();
    void addNewCategoryActionSlot();
    void setCategoryActionsSlot(QAction *action);
    void createVoiceBanksLabelsSubMenu();
    void addNewLabelActionSlot();
    void setLabelActionSlot(QAction *action);
    void on_voicebankImage_customContextMenuRequested(const QPoint &);
    void onCurrentCategoryChanged(const QString& current);
    void onCurrentLabelChanged(const QString& current);
};

#endif // VOICEBANKMANAGERWINDOW_H
