#ifndef VOICEBANKHANDLER_H
#define VOICEBANKHANDLER_H

#include <QObject>
#include "voicebank.h"
#include <QThread>
#include <QThreadPool>
#include <public_defines.h>
class VoiceBankHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool useOldFolderScan READ isOldFolderScan WRITE setUseOldFolderScan NOTIFY useOldFolderScanChanged)
public:
    explicit VoiceBankHandler(QObject *parent = nullptr);
    ~VoiceBankHandler();

    void readVoiceBanksFromMonitorFolders();

    QList<VoiceBank *> getVoiceBanks() const;

    VoiceBank* addVoiceBank(QString& path);
    QList<VoiceBank*> addVoiceBanks(QStringList& paths){
        QList<VoiceBank*> voiceBanks;
        for (auto path : paths)
        {
            addVoiceBank(path);
        }
        return voiceBanks;
    }
    int count(){
        return voiceBanks.count();
    }
    VoiceBank* getVoiceBank(int id) const{
        return voiceBanks.value(id);
    }
    int getVoiceBankID(VoiceBank* voiceBank) const
    {
        return voiceBanks.indexOf(voiceBank);
    }
    void clear();
    class VoiceBankReadFuctionRunner : public QRunnable{
    public:
        VoiceBankReadFuctionRunner(VoiceBank* voicebank);
        void run() override;
    private:
        VoiceBank* voicebank;
    };
    void setThreadPoolMaxThreadCount(int maxCount);
    int getThreadPoolMaxThreadCount() const{
        return threadPool->maxThreadCount();
    }
    enum class SortableInformationID{Name,Path};
    void sort(SortableInformationID sortWhat, Qt::SortOrder order = Qt::AscendingOrder);
    QList<int> findIDByName(const QString &text) const;
    int getVoiceBankCount() const{
        return voiceBanks.count();
    }
    QList<int> findIDByCategory(const QString &category) const;
    QList<int> findIDByLabel(const QString &label) const;
    bool isUseOldFolderScan() const;

    void setUseOldFolderScan(bool value);

private:


    int voiceBankReadDoneCount{};

    QStringList getVoiceBankFoldersInFolder(const QString &dir);
    bool useOldFolderScan = false;
    QStringList outsideVoiceBankFolders;
    QStringList ignoreVoiceBankFolders;
    QStringList ignoredVoiceBankFolders;
    QStringList notVoiceBankPaths;
    void findScannedSubFolders();
    QStringList scannedSubFolders;

    QStringList monitorFolders = {"./voice"};

    QStringList getFoldersInMonitorFolders();
    void loadMonitorFoldersSettings();
    void saveMonitorFoldersSettings();

    QList<VoiceBank *> voiceBanks{};
    void addVoiceBank(VoiceBank * newVoiceBank){
        voiceBanks.append(newVoiceBank);
    }
    QThreadPool* threadPool = new QThreadPool(this);
    void readThreadPoolMaxThreadCountSettings();
    void saveThreadPoolMaxThreadCountSettings();

private slots:
signals:
    void aVoiceBankReadDone(VoiceBank* voicebank);
    void backupImageFileBecauseExists(VoiceBank *);
    void cannotBackupImageFile(VoiceBank *);
    void categoriesChanged();
    void labelsChanged();
    void categroiesAndLabelsChanged();
    void useOldFolderScanChanged();
    void voiceBanksReadDone();
public slots:
};

#endif // VOICEBANKHANDLER_H
