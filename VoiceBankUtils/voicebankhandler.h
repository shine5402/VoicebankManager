#ifndef VOICEBANKHANDLER_H
#define VOICEBANKHANDLER_H

#include <QObject>
#include "voicebank.h"
#include <QThread>
#include <QThreadPool>
class VoiceBankHandler : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBankHandler(QObject *parent = nullptr);
    ~VoiceBankHandler();
    QList<VoiceBank *> getVoiceBanks() const;

    VoiceBank* addVoiceBank(QString& path){
        auto newVoiceBank = new VoiceBank(path,this);
        //auto newReadThread = QThread::create([=]{newVoiceBank->readFromPath();});
        //LeafLogger::LogMessage(QString(u8"为%1建立了一个新线程。").arg(path));
        connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
        auto newVoiceBankReadFunctionRunner = new VoiceBankReadFuctionRunner(newVoiceBank);
        //newReadThread->start();
        threadPool->start(newVoiceBankReadFunctionRunner);
        LeafLogger::LogMessage(QString(u8"%1的读取线程被加入线程池并由线程池管理启动。").arg(path));
        addVoiceBank(newVoiceBank);
        return newVoiceBank;
    }
    int count(){
        return voiceBanks.count();
    }
    VoiceBank* getVoiceBank(int id){
        return voiceBanks.value(id);
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
private:
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
public slots:
};

#endif // VOICEBANKHANDLER_H
