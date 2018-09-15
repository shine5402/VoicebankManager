#ifndef VOICEBANKHANDLER_H
#define VOICEBANKHANDLER_H

#include <QObject>
#include "voicebank.h"
#include <QThread>
class VoiceBankHandler : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBankHandler(QObject *parent = nullptr);
    QList<VoiceBank *> getVoiceBanks() const;

    VoiceBank* addVoiceBank(QString& path){
        auto newVoiceBank = new VoiceBank(path,this);
        auto newReadThread = QThread::create([=]{newVoiceBank->readFromPath();});
        LeafLogger::LogMessage(QString(u8"为%1建立了一个新线程。").arg(path));
        connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
        newReadThread->start();
        LeafLogger::LogMessage(QString(u8"%1的读取线程启动。").arg(path));
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
private:
    QList<VoiceBank *> voiceBanks{};
    void addVoiceBank(VoiceBank * newVoiceBank){
        voiceBanks.append(newVoiceBank);
    }
private slots:
signals:
    void aVoiceBankReadDone(VoiceBank* voicebank);
public slots:
};

#endif // VOICEBANKHANDLER_H
