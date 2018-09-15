#include "voicebankhandler.h"

VoiceBankHandler::VoiceBankHandler(QObject *parent) : QObject(parent)
{
    VoiceBank::readStaticSettings();
    threadPool->setMaxThreadCount(50);//TODO:提供设置
}

QList<VoiceBank *> VoiceBankHandler::getVoiceBanks() const
{
    return voiceBanks;
}

void VoiceBankHandler::clear()
{
    for (auto item : voiceBanks){
        item->deleteLater();
    }
    voiceBanks.clear();
}

VoiceBankHandler::VoiceBankReadFuctionRunner::VoiceBankReadFuctionRunner(VoiceBank *voicebank):QRunnable(),voicebank(voicebank)
{
}

void VoiceBankHandler::VoiceBankReadFuctionRunner::run()
{
    voicebank->readFromPath();
}
