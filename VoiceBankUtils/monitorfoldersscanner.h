#ifndef MONITORFOLDERSSCANNER_H
#define MONITORFOLDERSSCANNER_H

#include <QObject>
#include <QDir>
#include "voicebank.h"

///获取监视文件夹内的音源文件夹路径列表
/*!
  MonitorFoldersScanner 是用来获取监视文件夹内的音源文件夹路径列表的类。\n
  您可以使用 getFoldersInMonitorFolders() 来获取监视文件夹下的音源库的路径列表。\n
  您可以使用其他成员函数来更改扫描行为，获得扫描详情等。\n
  MonitorFoldersScanner 采用单件模式，您不能直接创建，而是通过 getMonitorFoldersScanner() 来获取其实例。\n
*/
class MonitorFoldersScanner : QObject
{
    Q_OBJECT
public:
    static MonitorFoldersScanner* getMonitorFoldersScanner();
    ~MonitorFoldersScanner();

    QStringList getFoldersInMonitorFolders();

    QStringList getMonitorFolders() const;
    void setMonitorFolders(const QStringList &value);

    QStringList getOutsideVoiceBankFolders() const;
    void setOutsideVoiceBankFolders(const QStringList &value);

    QStringList getIgnoreVoiceBankFolders() const;
    void setIgnoreVoiceBankFolders(const QStringList &value);
    void addIgnoreVoiceBankFolder(const QString &path);

    bool isUseOldFolderScan() const;
    void setUseOldFolderScan(bool value);

    /*
      以下三个函数在调用过scan()之后才有意义。
    */
    QStringList getIgnoredVoiceBankFolders() const;
    QStringList getNotVoiceBankPaths() const;
    QStringList getScannedSubFolders() const;

    ///在 MonitorFoldersScanner 还没有扫描过监视文件夹时调用扫描详情相关函数，将抛出该异常类
    class NotScanned : std::runtime_error {
    public:
        NotScanned();
    };

private:
    MonitorFoldersScanner(QObject *parent = nullptr);
    static MonitorFoldersScanner* s_monitorFoldersScanner;

    QStringList getVoiceBankFoldersInFolder(const QString &dir);
    bool useOldFolderScan = false;
    QStringList outsideVoiceBankFolders;
    QStringList ignoreVoiceBankFolders;
    QStringList ignoredVoiceBankFolders;
    QStringList notVoiceBankPaths;
    QStringList lastScannedPaths;
    bool scanned = false;

    QStringList monitorFolders = {"./voice"};


    void loadMonitorFoldersSettings();
    void saveMonitorFoldersSettings();

    class Garbo {
    public:
        ~Garbo(){
            if (MonitorFoldersScanner::s_monitorFoldersScanner)
                delete MonitorFoldersScanner::s_monitorFoldersScanner;
        }
    };

    static Garbo garbo;
    friend Garbo;
signals:
    void useOldFolderScanChanged();///< “是否使用文件夹扫描策略”发生了改变
    /*!<
      \see isUseOldFolderScan()
    */
};

#endif // MONITORFOLDERSSCANNER_H
