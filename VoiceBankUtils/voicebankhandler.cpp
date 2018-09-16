#include "voicebankhandler.h"

VoiceBankHandler::VoiceBankHandler(QObject *parent) : QObject(parent)
{
    VoiceBank::readStaticSettings();
    readThreadPoolMaxThreadCountSettings();
}

VoiceBankHandler::~VoiceBankHandler()
{
    saveThreadPoolMaxThreadCountSettings();
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

void VoiceBankHandler::setThreadPoolMaxThreadCount(int maxCount)
{
    threadPool->setMaxThreadCount(maxCount);
}

void VoiceBankHandler::readThreadPoolMaxThreadCountSettings()
{
    QSettings settings;
    if (settings.contains(u8"VoiceBankHandler/ThreadPoolMaxThreadCount"))
        threadPool->setMaxThreadCount(settings.value(u8"VoiceBankHandler/ThreadPoolMaxThreadCount",50).toInt());
}

void VoiceBankHandler::saveThreadPoolMaxThreadCountSettings()
{
    QSettings settings;
    settings.setValue(u8"VoiceBankHandler/ThreadPoolMaxThreadCount",threadPool->maxThreadCount());
}

VoiceBankHandler::VoiceBankReadFuctionRunner::VoiceBankReadFuctionRunner(VoiceBank *voicebank):QRunnable(),voicebank(voicebank)
{
}

void VoiceBankHandler::VoiceBankReadFuctionRunner::run()
{
    voicebank->readFromPath();
}
