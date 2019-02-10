#ifndef VOICEBANKHANDLER_H
#define VOICEBANKHANDLER_H

#include <QObject>
#include "voicebank.h"
#include <QThread>
#include <QThreadPool>
#include <public_defines.h>
#include "monitorfoldersscanner.h"

///用于管理一系列VoiceBank。
/*!
  VoiceBankHandler 是用于管理 VoiceBank 的类。\n
  VoiceBankHandler 采用单件模式，您不能直接创建，而是通过 getVoiceBankHandler() 来获取其实例。\n
  一般来说，您不需要手动添加 VoiceBank ，而是使用 readVoiceBanksFromMonitorFolders() 来从用户指定的监视文件夹中读取音源库，并自动转化为 VoiceBank 的实例。\n
  它允许在它管理的 VoiceBank 中通过名称、分类、标签等条件查找音源库，详见 findIDByNameOrPath(const QString &text) const 、 findIDByCategory(const QString &category) const 、 findIDByLabel(const QString &label) const  。\n
  它也允许对内部的 VoiceBank 列表进行排序，详见 sort(SortableInformationID sortWhat, Qt::SortOrder order) 。
*/
class VoiceBankHandler : public QObject
{
    Q_OBJECT

public:
    static VoiceBankHandler * getVoiceBankHandler();
    ~VoiceBankHandler();

    void readVoiceBanksFromMonitorFolders();

    /*
      作为VoiceBank保存者的相关函数
    */
    QList<VoiceBank *> getVoiceBanks() const;

    void addVoiceBank(VoiceBank * newVoiceBank);

    VoiceBank* addVoiceBank(QString& path);

    QList<VoiceBank*> addVoiceBanks(QStringList& paths){
        ///让 VoiceBankHandler 管理路径在 paths 中的 VoiceBank 。
        /*!
          为了更方便使用而提供，等同于
          \code{.cpp}
        for (auto path : paths)
        {
            addVoiceBank(path);
        }
        \endcode
        \param[in] paths 要添加到 VoiceBankHandler 中的多个 VoiceBank 的文件夹所在路径列表。
        \return 添加到 VoiceBankHandler 的 VoiceBank * 的列表。
        \see addVoiceBank(QString& path)
        */
        QList<VoiceBank*> voiceBanks;
        for (auto path : paths)
        {
            addVoiceBank(path);
        }
        return voiceBanks;
    }

    int count() const {
        ///VoiceBankHandler 已被托管的 VoiceBank 的数量
        return voiceBanks.count();
    }

    VoiceBank* getVoiceBank(int id) const{
        ///通过下标获得一个 VoiceBank *
        /*!
          \param[in] id 需要的 VoiceBank * 的数组下标 ( 0 <= id < count() )。id 不在有效范围内时，返回一个空指针。
          \return id 对应的 VoiceBank * 。
          \see getVoiceBankID(VoiceBank* voiceBank) const
        */
        return voiceBanks.value(id);
    }

    int getVoiceBankID(VoiceBank* voiceBank) const
    {
        ///通过 VoiceBank * 来获得相应下标
        /*!
          \param[in] voiceBank 需要知道下标的 VoiceBank * 。
          \return VoiceBank * 对应的数组下标。
          \see getVoiceBank(int id) const
        */
        return voiceBanks.indexOf(voiceBank);
    }
    QList<int> findIDByNameOrPath(const QString &text) const;
    QList<int> findIDByCategory(const QString &category) const;
    QList<int> findIDByLabel(const QString &label) const;

    void clear();

    /// 可供排序的信息列列表
    /*!
      该枚举定义了 sort(SortableInformationID sortWhat, Qt::SortOrder order) 函数中可以用于排序的信息。
      \see sort(SortableInformationID sortWhat, Qt::SortOrder order = Qt::AscendingOrder)
    */
    //TODO:重构此处
    enum class SortableInformationID
    {
        Name, ///< VoiceBank 的名称。对应 VoiceBank 的名称。
        Path, ///< VoiceBank 的路径。对应 VoiceBank 的路径。
    };
    void sort(SortableInformationID sortWhat, Qt::SortOrder order = Qt::AscendingOrder);

signals:
    //TODO:重写信号文档
    void aVoiceBankReadDone(VoiceBank* voicebank); ///< 一个 VoiceBank 读取完毕。
    /*!<
      \param voicebank 读取完毕的 VoiceBank * 。
      \see VoiceBank::readDone(VoiceBank * voicebank)
    */
    void aVoiceBankFirstReadDone(VoiceBank* voicebank); ///< 一个 VoiceBank 初次读取完毕。
    /*!<
      \param voicebank 读取完毕的 VoiceBank * 。
      \see VoiceBank::readDone(VoiceBank * voicebank)
    */
    void aVoiceBankReloadDone(VoiceBank* voicebank); ///< 一个 VoiceBank 重载完毕。
    /*!<
      \param voicebank 读取完毕的 VoiceBank * 。
      \see VoiceBank::readDone(VoiceBank * voicebank)
    */
    void backupImageFileBecauseExists(VoiceBank * voicebank);///< 修改 VoiceBank 的 image 时由于原本已经存在一个 image 所以实施了备份
    /*!<
      \param voicebank 备份了 image 的 VoiceBank * 。
      \see VoiceBank::backupImageFileBecauseExists(VoiceBank * voicebank)
    */
    void cannotBackupImageFile(VoiceBank * voicebank); ///< 一个 VoiceBank 备份 image 时发生了错误
    /*!<
      \param voicebank 备份 image 时出错的 VoiceBank * 。
      \see VoiceBank::cannotBackupImageFile(VoiceBank * voicebank)
    */
    void categoriesChanged(); ///< 管理的 VoiceBank 的分类发生了改变
    /*!<
      VoiceBankHandler 管理的任何一个 VoiceBank 的分类改变时该信号都会被触发。
      \see VoiceBank::categoryChanged()
    */
    void labelsChanged();///< 管理的 VoiceBank 的标签发生了改变
    /*!<
      VoiceBankHandler 管理的任何一个 VoiceBank 的标签改变时该信号都会被触发。
      \see VoiceBank::labelsChanged()
    */
    void categroiesAndLabelsChanged();///< 管理的 VoiceBank 的目录或标签发生了改变
    /*!<
      VoiceBankHandler 管理的任何一个 VoiceBank 的目录或标签改变时该信号都会被触发。
      \see categoriesChanged()
      \see labelsChanged()
    */
    void useOldFolderScanChanged();///< “是否使用文件夹扫描策略”发生了改变
    /*!<
      \see isUseOldFolderScan()
    */
    void voiceBanksReadDone();///< 所有 VoiceBank 都已经读取完毕
    /*!<
      所有提交给 VoiceBankHandler 读取的 VoiceBank 都已经读取完毕。建议在此信号触发之后再使用 VoiceBankHandler 管理的 VoiceBank * 。
      \see aVoiceBankReadDone(VoiceBank* voicebank)
    */
private:
    explicit VoiceBankHandler(QObject *parent = nullptr);
    VoiceBankHandler(const VoiceBankHandler&) = delete;
    VoiceBankHandler& operator= (const VoiceBankHandler&) = delete;
    static VoiceBankHandler *s_voiceBankHanlder;

    int voiceBankReadDoneCount = 0;

    QList<VoiceBank *> voiceBanks{};

    class Garbo {
    public:
        ~Garbo(){
            if (VoiceBankHandler::s_voiceBankHanlder)
                delete VoiceBankHandler::s_voiceBankHanlder;
        }
    };

    static Garbo garbo;
    friend Garbo;
private slots:
    void voiceBankFirstReadDoneSlot(VoiceBank *);

public slots:
};


#endif // VOICEBANKHANDLER_H
