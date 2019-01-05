#include "voicebankhandler.h"

VoiceBankHandler::VoiceBankHandler(QObject *parent) : QObject(parent)
{
    VoiceBank::readStaticSettings();
    readThreadPoolMaxThreadCountSettings();
    connect(this,SIGNAL(categoriesChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
    connect(this,SIGNAL(labelsChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
    loadMonitorFoldersSettings();
}

VoiceBankHandler::~VoiceBankHandler()
{
    saveThreadPoolMaxThreadCountSettings();
    saveMonitorFoldersSettings();
}

VoiceBankHandler *VoiceBankHandler::getVoiceBankHandler()
{
    /*!
      \l VoiceBankHandler 的工厂函数。
      \l VoiceBankHandler 使用单件模式来保证程序中只有一份音源库列表，所以您应当使用本函数获取实例，而不是通过构造函数（您也无法这么做）。
    */
    if (!s_voiceBankHanlder)
        s_voiceBankHanlder = new VoiceBankHandler();
    return s_voiceBankHanlder;
}

void VoiceBankHandler::readVoiceBanksFromMonitorFolders()
{
    auto voiceBankPaths = getFoldersInMonitorFolders();
    LeafLogger::LogMessage(QString("准备读取音源库。共有%1个文件夹待读取。").arg(voiceBankPaths.count()));
    if (voiceBankPaths.count() == 0)
        emit voiceBanksReadDone();
    else{
        addVoiceBanks(voiceBankPaths);
    }
}

void VoiceBankHandler::loadMonitorFoldersSettings()
{
    QSettings settings;
    monitorFolders = settings.value("MonitorFolders",{"./voice"}).toStringList();
    setUseOldFolderScan(settings.value("useOldFolderScan",false).toBool());
    //ui->actionuse_old_watched_folder_scan_strategy->setChecked(useOldFolderScan);
    outsideVoiceBankFolders = settings.value("OutsideVoiceBankFolders").toStringList();
    ignoreVoiceBankFolders = settings.value("ignoreVoiceBankFolders").toStringList();

}

void VoiceBankHandler::saveMonitorFoldersSettings()
{
    QSettings settings;
    settings.setValue("MonitorFolders",monitorFolders);
    settings.setValue("useOldFolderScan",useOldFolderScan);
    settings.setValue("OutsideVoiceBankFolders",outsideVoiceBankFolders);
    settings.setValue("ignoreVoiceBankFolders",ignoreVoiceBankFolders);
}

QList<VoiceBank *> VoiceBankHandler::getVoiceBanks() const
{
    return voiceBanks;
}

VoiceBank *VoiceBankHandler::addVoiceBank(QString &path){
    auto newVoiceBank = new VoiceBank(path,this);
    connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SLOT(voiceBankReadDoneSlot(VoiceBank *)));
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
    voiceBankReadDoneCount = 0;
    ignoredVoiceBankFolders.clear();
    notVoiceBankPaths.clear();
    scannedSubFolders.clear();
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
    if (text.trimmed().isEmpty())
    {
        for (auto i = 0; i < voiceBanks.count(); ++i)
        {
            result.append(i);
        }
        return result;
    }
    for (auto voiceBank : voiceBanks)
    {
        if (voiceBank->getName().contains(text) || voiceBank->getPath().contains(text))
            result.append(getVoiceBankID(voiceBank));
    }
    return result;
}

QList<int> VoiceBankHandler::findIDByCategory(const QString &category) const
{
    QList<int> result{};
    if (category.trimmed().isEmpty())
    {
        for (auto i = 0; i < voiceBanks.count(); ++i)
        {
            result.append(i);
        }
        return result;
    }
    if (category == tr("未分类"))
    {
        for (auto voiceBank : voiceBanks)
        {
            if (voiceBank->getCategory().isEmpty())
                result.append(getVoiceBankID(voiceBank));
        }
        return result;
    }
    for (auto voiceBank : voiceBanks)
    {
        if (voiceBank->getCategory() == category)
            result.append(getVoiceBankID(voiceBank));
    }
    return result;
}

QList<int> VoiceBankHandler::findIDByLabel(const QString& label) const
{
    QList<int> result{};
    if (label.trimmed().isEmpty())
    {
        for (auto i = 0; i < voiceBanks.count(); ++i)
        {
            result.append(i);
        }
        return result;
    }
    if (label == tr("无标签"))
    {
        for (auto voiceBank : voiceBanks)
        {
            if (voiceBank->getLabels().isEmpty())
                result.append(getVoiceBankID(voiceBank));
        }
    }
    for (auto voiceBank : voiceBanks)
    {
        if (voiceBank->getLabels().contains(label))
            result.append(getVoiceBankID(voiceBank));
    }
    return result;
}

bool VoiceBankHandler::isUseOldFolderScan()
{
    return useOldFolderScan;
}

void VoiceBankHandler::setUseOldFolderScan(bool value)
{
    useOldFolderScan = value;
    emit useOldFolderScanChanged();
}

QStringList VoiceBankHandler::getVoiceBankFoldersInFolder(const QString &dir)
{
    QStringList folderList{};
    QDir pDir(dir);
    auto entrys = pDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto entry : entrys){
        auto path = pDir.absolutePath() + "/" + entry;
        auto isIgnore = false;
        for (auto i : ignoreVoiceBankFolders)
        {
            if (QDir(i).path() == QDir(path).path())
            {
                ignoredVoiceBankFolders.append(i);
                isIgnore = true;
                break;
            }
        }
        if (isIgnore){
            folderList.append(getVoiceBankFoldersInFolder(path));
            continue;
        }
        if (!useOldFolderScan){
            if (VoiceBank::isVoiceBankPath(path))
                folderList.append(path);
            else
            {
                notVoiceBankPaths.append(path);
                LeafLogger::LogMessage(QString("%1不是音源文件夹。").arg(path));
                folderList.append(getVoiceBankFoldersInFolder(path));
            }
        }
        else
        {
            folderList.append(path);
        }
    }
    return folderList;
}

QStringList VoiceBankHandler::getIgnoreVoiceBankFolders()
{
    return ignoreVoiceBankFolders;
}

void VoiceBankHandler::setIgnoreVoiceBankFolders(const QStringList &value)
{
    ignoreVoiceBankFolders = value;
}

QStringList VoiceBankHandler::getOutsideVoiceBankFolders()
{
    return outsideVoiceBankFolders;
}

void VoiceBankHandler::setOutsideVoiceBankFolders(const QStringList &value)
{
    outsideVoiceBankFolders = value;
}

QStringList VoiceBankHandler::getNotVoiceBankPaths() const
{
    return notVoiceBankPaths;
}

QStringList VoiceBankHandler::getIgnoredVoiceBankFolders() const
{
    return ignoredVoiceBankFolders;
}

void VoiceBankHandler::addIgnoreVoiceBankFolder(QString path)
{
    ignoreVoiceBankFolders.append(path);
}

void VoiceBankHandler::findScannedSubFolders()
{
    QStringList firstSubFolders;
    for (auto i : monitorFolders)
    {
        QDir iDir(i);
        for (auto j : iDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            firstSubFolders.append(iDir.absoluteFilePath(j));
        }
    }
    auto outsideFolders = this->outsideVoiceBankFolders;
    for (auto i : outsideFolders)
    {
        if (i.endsWith("/") || i.endsWith("\\"))
            i.remove(i.count() - 1,1);
    }
    for (auto i : voiceBanks)
    {
        if (!(firstSubFolders.contains(i->getPath()) || outsideFolders.contains(i->getPath())))
            scannedSubFolders.append(i->getPath());
    }
}

void VoiceBankHandler::setMonitorFolders(const QStringList &value)
{
    monitorFolders = value;
}

QStringList VoiceBankHandler::getMonitorFolders()
{
    return monitorFolders;
}

QStringList VoiceBankHandler::getScannedSubFolders() const
{
    return scannedSubFolders;
}

QStringList VoiceBankHandler::getFoldersInMonitorFolders()
{
    QStringList folderList{};
    for (auto monitorFolder : monitorFolders){
        folderList.append(getVoiceBankFoldersInFolder(monitorFolder));
    }
    folderList.append(outsideVoiceBankFolders);
    return folderList;
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

void VoiceBankHandler::voiceBankReadDoneSlot(VoiceBank *voiceBank)
{
    if (voiceBank->isFirstRead())
        if (++voiceBankReadDoneCount == voiceBanks.count()){
            findScannedSubFolders();
            emit voiceBanksReadDone();
        }
}


VoiceBankHandler::VoiceBankReadFuctionRunner::VoiceBankReadFuctionRunner(VoiceBank *voicebank):QRunnable(),voicebank(voicebank)
{
}

void VoiceBankHandler::VoiceBankReadFuctionRunner::run()
{
    voicebank->readFromPath();
}

VoiceBankHandler* VoiceBankHandler::s_voiceBankHanlder = nullptr;
VoiceBankHandler::DestroyHelper VoiceBankHandler::destoryHelper{};

