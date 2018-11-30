#include "voicebankhandler.h"

VoiceBankHandler::VoiceBankHandler(QObject *parent) : QObject(parent)
{
    VoiceBank::readStaticSettings();
    readThreadPoolMaxThreadCountSettings();
    connect(this,SIGNAL(categoriesChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
    connect(this,SIGNAL(labelsChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
}

VoiceBankHandler::~VoiceBankHandler()
{
    saveThreadPoolMaxThreadCountSettings();
}

QList<VoiceBank *> VoiceBankHandler::getVoiceBanks() const
{
    return voiceBanks;
}

VoiceBank *VoiceBankHandler::addVoiceBank(QString &path){
    auto newVoiceBank = new VoiceBank(path,this);
    connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(backupImageFileBecauseExists(VoiceBank*)),this,SIGNAL(backupImageFileBecauseExists(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(cannotBackupImageFile(VoiceBank*)),this,SIGNAL(cannotBackupImageFile(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(categoryChanged()),this,SIGNAL(categoriesChanged()));
    connect(newVoiceBank,SIGNAL(labelsChanged()),this,SIGNAL(labelsChanged()));
    auto newVoiceBankReadFunctionRunner = new VoiceBankReadFuctionRunner(newVoiceBank);
    threadPool->start(newVoiceBankReadFunctionRunner);
    LeafLogger::LogMessage(QString("%1的读取线程被加入线程池并由线程池管理启动。").arg(path));
    addVoiceBank(newVoiceBank);
    return newVoiceBank;
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

void VoiceBankHandler::sort(VoiceBankHandler::SortableInformationID sortWhat, Qt::SortOrder order)
{
    if (sortWhat == SortableInformationID::Name)
        std::sort(voiceBanks.begin(),voiceBanks.end(),[&](VoiceBank *value1,VoiceBank *value2)->bool{
            if (order == Qt::AscendingOrder)
            return value1->getName() < value2->getName();
        else
            return value1->getName() > value2->getName();
    });
    else if (sortWhat == SortableInformationID::Path)
        std::sort(voiceBanks.begin(),voiceBanks.end(),[&](const VoiceBank *value1,const VoiceBank *value2)->bool{
            if (order == Qt::AscendingOrder)
                return value1->getPath() < value2->getPath();
            else
                return value1->getPath() > value2->getPath();
        });
}

QList<int> VoiceBankHandler::findIDByName(const QString &text) const
{
    QList<int> result{};
    for (auto voiceBank : voiceBanks)
    {
        if (voiceBank->getName().contains(text) || voiceBank->getPath().contains(text))
            result.append(getVoiceBankID(voiceBank));
    }
    return result;
}

void VoiceBankHandler::readThreadPoolMaxThreadCountSettings()
{
    QSettings settings;
    if (settings.contains("VoiceBankHandler/ThreadPoolMaxThreadCount"))
        threadPool->setMaxThreadCount(settings.value("VoiceBankHandler/ThreadPoolMaxThreadCount",50).toInt());
}

void VoiceBankHandler::saveThreadPoolMaxThreadCountSettings()
{
    QSettings settings;
    settings.setValue("VoiceBankHandler/ThreadPoolMaxThreadCount",threadPool->maxThreadCount());
}


VoiceBankHandler::VoiceBankReadFuctionRunner::VoiceBankReadFuctionRunner(VoiceBank *voicebank):QRunnable(),voicebank(voicebank)
{
}

void VoiceBankHandler::VoiceBankReadFuctionRunner::run()
{
    voicebank->readFromPath();
}
