#include "monitorfoldersscanner.h"

MonitorFoldersScanner* MonitorFoldersScanner::getMonitorFoldersScanner()
{
    if (!s_monitorFoldersScanner)
        s_monitorFoldersScanner = new MonitorFoldersScanner();
    return s_monitorFoldersScanner;
}

MonitorFoldersScanner::~MonitorFoldersScanner()
{
    saveMonitorFoldersSettings();
}

MonitorFoldersScanner::MonitorFoldersScanner(QObject* parent):QObject (parent)
{
    loadMonitorFoldersSettings();
}

MonitorFoldersScanner* MonitorFoldersScanner::s_monitorFoldersScanner = nullptr;
MonitorFoldersScanner::Garbo MonitorFoldersScanner::garbo{};

void MonitorFoldersScanner::setMonitorFolders(const QStringList &value)
{
    ///设定监视文件夹列表。将在 MonitorFoldersScanner 被析构时保存至 QSettings 。
    monitorFolders = value;
}

QStringList MonitorFoldersScanner::getMonitorFolders() const
{
    ///获取监视文件夹列表
    /*!
      监视文件夹列表定义 MonitorFoldersScanner 去哪里寻找 VoiceBank 所在的文件夹。监视文件夹应是 VoiceBank 的父文件夹。
      根据扫描文件夹策略设定的不同，VoiceBank 文件夹的确定方式也会有不同。参见 isUseOldFolderScan() 。
    */

    return monitorFolders;
}
QStringList MonitorFoldersScanner::getOutsideVoiceBankFolders() const
{
    ///获取外部音源文件夹列表
    /*!
      外部音源文件夹列表中的文件夹将在扫描时直接加入音源库列表中，不管其是否在监视文件夹内，不管其运行 VoiceBank::isVoiceBankPath(const QString &path) 的结果是否为真。但是其仍然受忽略文件夹列表的限制。
    */
    return outsideVoiceBankFolders;
}

void MonitorFoldersScanner::setOutsideVoiceBankFolders(const QStringList &value)
{
    ///设置外部音源文件夹列表。
    outsideVoiceBankFolders = value;
}

QStringList MonitorFoldersScanner::getNotVoiceBankPaths() const
{
    ///获取扫描过程中被程序认为不是音源文件夹的文件夹列表，仅在进行过扫描后有效。
    /*!
    \throw NotScanned 调用该函数之前没有进行过扫描操作。
  */
    return notVoiceBankPaths;
}

QStringList MonitorFoldersScanner::getIgnoreVoiceBankFolders() const
{
    ///获取忽略文件夹列表
    /*!
      忽略文件夹列表中的文件夹将在扫描时被直接忽略，但仍然会去搜寻其子文件夹。
      \todo 实现使用*来防止子文件夹调用
    */
    //TODO:实现使用*来防止子文件夹调用
    return ignoreVoiceBankFolders;
}

QStringList MonitorFoldersScanner::getIgnoredVoiceBankFolders() const
{
    ///获取扫描过程中已经被忽略的文件夹列表，仅在进行过扫描后有效。
    /*!
      \throw NotScanned 调用该函数之前没有进行过扫描操作。
    */
    if (!scanned)
        throw NotScanned();
    return ignoredVoiceBankFolders;
}

void MonitorFoldersScanner::setIgnoreVoiceBankFolders(const QStringList &value)
{
    ///设置忽略文件夹列表
    ignoreVoiceBankFolders = value;
}


void MonitorFoldersScanner::addIgnoreVoiceBankFolder(const QString& path)
{
    ///在忽略文件夹列表中添加一个文件夹
    /*!
      该函数为添加一个文件夹到忽略文件夹列表提供一个方便的途径。
    \param[in] path 要添加的文件夹路径。
    */
    ignoreVoiceBankFolders.append(path);
}

QStringList MonitorFoldersScanner::getScannedSubFolders() const
{
    ///获取扫描过程中通过递归查找子文件夹找到的音源文件夹，仅在进行过扫描后有效。
    /*!
      \throw NotScanned 调用该函数之前没有进行过扫描操作。
    */
    if (!scanned)
        throw NotScanned();

    QStringList firstSubFolders;
    QStringList scannedSubFolders;
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
    for (auto i : lastScannedPaths)
    {
        if (!(firstSubFolders.contains(i) || outsideFolders.contains(i)))
            scannedSubFolders.append(i);
    }
    return scannedSubFolders;
}

bool MonitorFoldersScanner::isUseOldFolderScan() const
{
    ///返回 MonitorFoldersScanner 是否使用旧式文件夹扫描策略
    /*!
      Leaf Open UTAU Qt 这部分代码的早期版本中，将监视文件夹的子文件夹直接作为 VoiceBank 的路径。这种策略与 UTAU 相同，但是在某些场景下不够实用。所以在较新版本的代码中， MonitorFoldersScanner 将会递归查找监视文件夹的子文件夹来确定音源库所在的文件夹。 \n
      MonitorFoldersScanner 使用 VoiceBank::isVoiceBankPath(const QString &path) 来确定一个文件夹是否是一个音源库文件夹。\n
      \return 如果使用旧式扫描策略，该函数返回 true ，否则返回 false 。
    */
    return useOldFolderScan;
}

void MonitorFoldersScanner::setUseOldFolderScan(bool value)
{
    ///设置 MonitorFoldersScanner 是否使用旧式文件夹扫描策略
    useOldFolderScan = value;
    emit useOldFolderScanChanged();
}

void MonitorFoldersScanner::loadMonitorFoldersSettings()
{
    QSettings settings;
    monitorFolders = settings.value("MonitorFolders",{"./voice"}).toStringList();
    setUseOldFolderScan(settings.value("useOldFolderScan",false).toBool());
    outsideVoiceBankFolders = settings.value("OutsideVoiceBankFolders").toStringList();
    ignoreVoiceBankFolders = settings.value("ignoreVoiceBankFolders").toStringList();

}

void MonitorFoldersScanner::saveMonitorFoldersSettings()
{
    QSettings settings;
    settings.setValue("MonitorFolders",monitorFolders);
    settings.setValue("useOldFolderScan",useOldFolderScan);
    settings.setValue("OutsideVoiceBankFolders",outsideVoiceBankFolders);
    settings.setValue("ignoreVoiceBankFolders",ignoreVoiceBankFolders);
}

QStringList MonitorFoldersScanner::getFoldersInMonitorFolders()
{
    ///获得监视文件夹内的音源文件夹
    /*!
      您可以使用其他函数来修改 MonitorFoldersScanner 的扫描行为。参见其它成员函数。
      \return 监视文件夹内的音源文件夹列表
    */
    QStringList folderList{};
    for (auto monitorFolder : monitorFolders){
        folderList.append(getVoiceBankFoldersInFolder(monitorFolder));
    }
    folderList.append(outsideVoiceBankFolders);
    lastScannedPaths = folderList;
    scanned = true;
    return folderList;
}

QStringList MonitorFoldersScanner::getVoiceBankFoldersInFolder(const QString &dir)
{
    QStringList folderList{};
    QDir pDir(dir);
    auto entrys = pDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (auto entry : entrys){
        auto path = pDir.absolutePath() + "/" + entry;
        auto isIgnore = false;
        auto isIgnoreSub = false;
        for (auto i : ignoreVoiceBankFolders)
        {
            if (i.startsWith("*"))
            {
                i.remove("*");
                isIgnoreSub = true;
            }
            if (QDir(i).path() == QDir(path).path())
            {
                ignoredVoiceBankFolders.append(i);
                isIgnore = true;
                break;
            }
        }
        if (isIgnoreSub && isIgnore)
            continue;
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

MonitorFoldersScanner::NotScanned::NotScanned() : std::runtime_error("MonitorFoldersScanner wasn't required to scan before.")
{

}

