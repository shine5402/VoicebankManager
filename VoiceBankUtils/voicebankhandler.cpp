#include "voicebankhandler.h"

VoiceBankHandler::VoiceBankHandler(QObject *parent) : QObject(parent)
{
    //readThreadPoolMaxThreadCountSettings();
    connect(this,SIGNAL(categoriesChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
    connect(this,SIGNAL(labelsChanged()),this,SIGNAL(categroiesAndLabelsChanged()));
}

VoiceBankHandler::~VoiceBankHandler()
{
    ///VoiceBankHandler 的析构函数。
    /*!
      将由内部的一个辅助类调用以在程序退出时保存相关状态。
    */

    //saveThreadPoolMaxThreadCountSettings();
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

void VoiceBankHandler::addVoiceBank(VoiceBank *newVoiceBank){
    ///将一个 VoiceBank 交给 VoiceBankHandler 管理。
    /*!
          更建议使用 addVoiceBank(QString& path) 。
          \param[in] newVoiceBank 要交给 VoiceBankHandler 的 VoiceBank * 。
        */
    voiceBanks.append(newVoiceBank);
    connect(newVoiceBank,SIGNAL(readDone(VoiceBank*)),this,SIGNAL(aVoiceBankReadDone(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(firstReadDone(VoiceBank*)),this,SLOT(voiceBankFirstReadDoneSlot(VoiceBank* )));
    connect(newVoiceBank,SIGNAL(firstReadDone(VoiceBank*)),this,SIGNAL(aVoiceBankFirstReadDone(VoiceBank* )));
    connect(newVoiceBank,SIGNAL(reloadDone(VoiceBank*)),this,SIGNAL(aVoiceBankReloadDone(VoiceBank* )));
    connect(newVoiceBank,SIGNAL(backupImageFileBecauseExists(VoiceBank*)),this,SIGNAL(backupImageFileBecauseExists(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(cannotBackupImageFile(VoiceBank*)),this,SIGNAL(cannotBackupImageFile(VoiceBank*)));
    connect(newVoiceBank,SIGNAL(categoryChanged()),this,SIGNAL(categoriesChanged()));
    connect(newVoiceBank,SIGNAL(labelsChanged()),this,SIGNAL(labelsChanged()));
}

VoiceBank* VoiceBankHandler::addVoiceBank(QString &path){
    ///让 VoiceBankHandler 管理一个路径为 path 的 VoiceBank 。
    /*!
      \param[in] path 要添加的 VoiceBank 的路径。\n

      VoiceBankHandler 会自动配置该 VoiceBank 并读取。\n
      \return 新的 VoiceBank 的指针。注意，返回时该 VoiceBank 可能并没有读取完毕。您应当等待 VoiceBankHandler::aVoiceBankReadDone(VoiceBank* voicebank) 信号或 VoiceBank::readDone(VoiceBank* ) 被触发后再使用此指针。
    */
    auto newVoiceBank = new VoiceBank(path,this);
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


void VoiceBankHandler::sort(VoiceBankHandler::SortableInformationID sortWhat, Qt::SortOrder order)
{
    ///对 VoiceBankHandler 内的列表进行排序
    /*!
      当声库的名称字段为空时，VoiceBankHandler将使用其文件夹名称。
      \param[in] sortWhat 对哪项信息进行排序
      \param[in] order 以何种顺序进行排序
      \see enum class SortableInformationID
    */
    if (sortWhat == SortableInformationID::Name)
        std::sort(voiceBanks.begin(),voiceBanks.end(),[&](VoiceBank* value1,VoiceBank* value2)->bool{
            auto name1 = value1->getName();
            auto name2 = value2->getName();
            auto folder1 = QFileInfo(value1->getPath()).dir().dirName();
            auto folder2 = QFileInfo(value2->getPath()).dir().dirName();
            auto sortString1 = name1.isEmpty()?folder1:name1;
            auto sortString2 = name2.isEmpty()?folder2:name2;
            if (order == Qt::AscendingOrder)
                return sortString1 < sortString2;
            else
                return sortString1 > sortString2;
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
    auto byName = findIDByName(text);
    auto byPath = findIDByPath(text);

    return SetOperations::getUnion<int>({byName, byPath});
}

QList<int> VoiceBankHandler::findIDByName(const QString &text) const{
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
        if (voiceBank->getName().contains(text))
            result.append(getVoiceBankID(voiceBank));
    }
    return result;
}

QList<int> VoiceBankHandler::findIDByPath(const QString &text) const{
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
        if (voiceBank->getPath().contains(text))
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



void VoiceBankHandler::voiceBankFirstReadDoneSlot(VoiceBank*)
{
        if (++voiceBankReadDoneCount == voiceBanks.count()){
            emit voiceBanksReadDone();
        }
}

VoiceBankHandler* VoiceBankHandler::s_voiceBankHanlder = nullptr;
VoiceBankHandler::Garbo VoiceBankHandler::garbo{};

