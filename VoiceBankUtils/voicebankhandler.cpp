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
    ///VoiceBankHandler 的析构函数。
    /*!
      将由内部的一个辅助类调用以在程序退出时保存相关状态。
    */

    saveThreadPoolMaxThreadCountSettings();
    saveMonitorFoldersSettings();
}

VoiceBankHandler *VoiceBankHandler::getVoiceBankHandler()
{
    ///VoiceBankHandler 的工厂函数。调用此函数以获取 VoiceBankHandler 的实例。
    /*!
      VoiceBankHandler 使用单件模式来保证程序中只有一份音源库列表，所以您应当使用本函数获取实例，而不是通过构造函数（您也无法这么做）。
    */
    if (!s_voiceBankHanlder)
        s_voiceBankHanlder = new VoiceBankHandler();
    return s_voiceBankHanlder;
}

void VoiceBankHandler::readVoiceBanksFromMonitorFolders()
{
    ///从监视文件夹中读取音源库。
    /*!
      在确定待读取文件夹列表时，程序会考虑是否递归查找、忽略文件夹列表、外部文件夹列表等。参见这些设置相关的函数以获取详情。
    */
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
    ///返回 VoiceBankHandler 是否使用旧式文件夹扫描策略
    /*!
      Leaf Open UTAU Qt 这部分代码的早期版本中，将监视文件夹的子文件夹直接作为 VoiceBank 的路径。这种策略与 UTAU 相同，但是在某些场景下不够实用。所以在较新版本的代码中， VoiceBankHandler 将会递归查找监视文件夹的子文件夹来确定音源库所在的文件夹。 \n
      VoiceBankHandler 使用 VoiceBank::isVoiceBankPath(const QString &path) 来确定一个文件夹是否是一个音源库文件夹。\n
      如果使用旧式扫描策略，该函数返回 true ，否则返回 false 。
    */
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
    ///获取忽略文件夹列表
    /*!
      忽略文件夹列表中的文件夹将在扫描时被直接忽略，但仍然会去搜寻其子文件夹。
    */
    //TODO:实现使用*来防止子文件夹调用
    return ignoreVoiceBankFolders;
}

void VoiceBankHandler::setIgnoreVoiceBankFolders(const QStringList &value)
{
    ///设置忽略文件夹列表
    ignoreVoiceBankFolders = value;
}

QStringList VoiceBankHandler::getOutsideVoiceBankFolders()
{
    ///获取外部音源文件夹列表
    /*!
      外部音源文件夹列表中的文件夹将在扫描时直接加入音源库列表中，不管其是否在监视文件夹内，不管其运行 VoiceBank::isVoiceBankPath(const QString &path) 的结果是否为真。但是其仍然受忽略文件夹列表的限制。
    */
    return outsideVoiceBankFolders;
}

void VoiceBankHandler::setOutsideVoiceBankFolders(const QStringList &value)
{
    ///设置外部音源文件夹列表。
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

void VoiceBankHandler::addIgnoreVoiceBankFolder(const QString& path)
{
    ///在忽略文件夹列表中添加一个文件夹
    /*!
      该函数为添加一个文件夹到忽略文件夹列表提供一个方便的途径。
    \param[in] path 要添加的文件夹路径。
    */
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
    ///设定监视文件夹列表。将在 VoiceBankHandler 被析构时保存至 QSettings 。
    monitorFolders = value;
}

QStringList VoiceBankHandler::getMonitorFolders()
{
    ///获取监视文件夹列表
    /*!
      监视文件夹列表定义 VoiceBankHandler 去哪里寻找 VoiceBank 所在的文件夹。监视文件夹应是 VoiceBank 的父文件夹。
      根据扫描文件夹策略设定的不同，VoiceBank 文件夹的确定方式也会有不同。参见 isUseOldFolderScan() 。
    */

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

