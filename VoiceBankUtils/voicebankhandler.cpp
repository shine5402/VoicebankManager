#include "voicebankhandler.h"

VoiceBankHandler::VoiceBankHandler(QObject *parent) : QObject(parent)
{
    readThreadPoolMaxThreadCountSettings();
    connect(this,SIGNAL(categoriesChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
    connect(this,SIGNAL(labelsChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
}

VoiceBankHandler::~VoiceBankHandler()
{
    ///VoiceBankHandler 的析构函数。
    /*!
      将由内部的一个辅助类调用以在程序退出时保存相关状态。
    */

    saveThreadPoolMaxThreadCountSettings();
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
    auto voiceBankPaths = MonitorFoldersScanner::getMonitorFoldersScanner()->getFoldersInMonitorFolders();
    LeafLogger::LogMessage(QString("准备读取音源库。共有%1个文件夹待读取。").arg(voiceBankPaths.count()));
    if (voiceBankPaths.count() == 0)
        emit voiceBanksReadDone();
    else{
        addVoiceBanks(voiceBankPaths);
    }
}


QList<VoiceBank* > VoiceBankHandler::getVoiceBanks() const
{
    ///获取 VoiceBankHandler 保存的 VoiceBank* 列表。
    return voiceBanks;
}

VoiceBank* VoiceBankHandler::addVoiceBank(QString &path){
    ///让 VoiceBankHandler 管理一个路径为 path 的 VoiceBank 。
    /*!
      \param[in] path 要添加的 VoiceBank 的路径。\n

      VoiceBankHandler 会自动配置该 VoiceBank 并读取。\n
      \return 新的 VoiceBank 的指针。注意，返回时该 VoiceBank 可能并没有读取完毕。您应当等待 VoiceBankHandler::aVoiceBankReadDone(VoiceBank* voicebank) 信号或 VoiceBank::readDone(VoiceBank* ) 被触发后再使用此指针。
    */
    auto newVoiceBank = new VoiceBank(path,this);
    connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SLOT(voiceBankReadDoneSlot(VoiceBank* )));
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
    ///清除 VoiceBankHandler 中的 VoiceBank* 列表。
    /*!
      VoiceBankHandler 会自动 delete 所有 VoiceBank* 。
    */
    for (auto item : voiceBanks){
        item->deleteLater();
    }
    voiceBanks.clear();
    voiceBankReadDoneCount = 0;
}

void VoiceBankHandler::setThreadPoolMaxThreadCount(int maxCount)
{
    ///设置读取 VoiceBank 所需信息时所用的最大线程数
    /*!
      VoiceBankHandler 使用多个线程来读取 VoiceBank 。这能节省时间并更好的利用现代处理器的性能。\n
      您可以通过本函数来修改 VoiceBankHandler 内部的线程池的最大线程数来优化性能。但请务必在明白您在做什么的时候使用。
      \param[in] maxCount 新的最大线程数
    */
    threadPool->setMaxThreadCount(maxCount);
}

void VoiceBankHandler::sort(VoiceBankHandler::SortableInformationID sortWhat, Qt::SortOrder order)
{
    ///对 VoiceBankHandler 内的列表进行排序
    /*!
      \param[in] sortWhat 对哪项信息进行排序
      \param[in] order 以何种顺序进行排序
      \see enum class SortableInformationID
    */
    if (sortWhat == SortableInformationID::Name)
        std::sort(voiceBanks.begin(),voiceBanks.end(),[&](VoiceBank* value1,VoiceBank* value2)->bool{
            if (order == Qt::AscendingOrder)
                return value1->getName() < value2->getName();
            else
                return value1->getName() > value2->getName();
        });
    else if (sortWhat == SortableInformationID::Path)
        std::sort(voiceBanks.begin(),voiceBanks.end(),[&](const VoiceBank* value1,const VoiceBank* value2)->bool{
            if (order == Qt::AscendingOrder)
                return value1->getPath() < value2->getPath();
            else
                return value1->getPath() > value2->getPath();
        });
}

QList<int> VoiceBankHandler::findIDByNameOrPath(const QString &text) const
{
    ///在 VoiceBankHandler 管理的 VoiceBank 中按名字或路径查找
    /*!
      \param[in] text 要查找的 VoiceBank 的名称或路径。该函数采用部分匹配方式，即二者中有一个含有 text 即可。
      \return 查找到的 VoiceBank* 的列表。
      \see findIDByCategory(const QString &category) const
      \see findIDByLabel(const QString& label) const
    */
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
    ///在 VoiceBankHandler 管理的 VoiceBank 中按目录查找
    /*!
      \param[in] category 要查找的 VoiceBank 的目录。
      \return 查找到的 VoiceBank* 的列表。
      \see findIDByNameOrPath(const QString &text) const
      \see findIDByLabel(const QString& label) const
    */
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
    ///在 VoiceBankHandler 管理的 VoiceBank 中按标签查找
    /*!
      \param[in] label 要查找的 VoiceBank 的标签。
      \return 查找到的 VoiceBank* 的列表。
      \see findIDByCategory(const QString &category) const
      \see findIDByLabel(const QString& label) const
    */
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

void VoiceBankHandler::voiceBankReadDoneSlot(VoiceBank* voiceBank)
{
    if (voiceBank->isFirstRead())
        if (++voiceBankReadDoneCount == voiceBanks.count()){
            emit voiceBanksReadDone();
        }
}


VoiceBankHandler::VoiceBankReadFuctionRunner::VoiceBankReadFuctionRunner(VoiceBank* voicebank):QRunnable(),voicebank(voicebank)
{
}

void VoiceBankHandler::VoiceBankReadFuctionRunner::run()
{
    ///运行给定 VoiceBank 的读取函数。
    voicebank->readFromPath();
}

VoiceBankHandler* VoiceBankHandler::s_voiceBankHanlder = nullptr;
VoiceBankHandler::Garbo VoiceBankHandler::garbo{};

