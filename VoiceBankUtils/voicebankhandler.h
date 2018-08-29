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
    void addVoiceBank(VoiceBank * newVoiceBank){
        voiceBanks.append(newVoiceBank);
    }
    VoiceBank* addVoiceBank(QString& path){
        auto newVoiceBank = new VoiceBank(path,this);
        auto newReadThread = QThread::create([=]{newVoiceBank->readFromPath();});
        connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
        newReadThread->start();
        addVoiceBank(newVoiceBank);
        return newVoiceBank;
    }
    void readVoiceBankFromParentDirecory(QString& path);
private:
    QList<VoiceBank *> voiceBanks{};
private slots:
signals:
    void aVoiceBankReadDone(VoiceBank* voicebank);
public slots:
};

#endif // VOICEBANKHANDLER_H
