#ifndef VOICEBANK_H
#define VOICEBANK_H
#include <QPixmap>
#include <QTextCodec>
#include <QFile>
#include <exception>
#include <QFileInfo>
#include <QTextDecoder>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <public_defines.h>
#include <QPainter>
#include <qchardet.h>
#include <QJsonArray>
#include <textconverthelper.h>
#include <QThreadPool>
#include <QRandomGenerator>
#include <QMimeDatabase>
#include <QImageReader>
#include <fileiowithcodechelper.h>

///用于表示一个音源库
/*!
    VoiceBank 类代表了一个 UTAU 式音源库。可以通过它获取音源库的相关信息，并可作出修改。
*/
class VoiceBank : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBank(QString path,QObject *parent = nullptr);
    ~VoiceBank();

    void reload();

    QString getName() const;
    void setName(const QString& name);

    QImage getImage() const;
    QString getImagePath() const;
    void setImage(const QImage& _image, const QString &newImageFileName = "icon.jpg");

    QString getReadme() const;

    QString getPath() const;

    QTextCodec* getCharacterTextCodec() const;
    void setCharacterTextCodec(QTextCodec *value);

    QTextCodec* getReadmeTextCodec() const;
    void setReadmeTextCodec(QTextCodec *value);

    QTextCodec* getWavFileNameTextCodec() const;
    void setWavFileNameTextCodec(QTextCodec *value);

    static QTextCodec* getDefaultCharacterTextCodec();
    static void setDefaultCharacterTextCodec(QTextCodec *value);

    static QTextCodec* getDefaultReadmeTextCodec();
    static void setDefaultReadmeTextCodec(QTextCodec *value);

    static QTextCodec* getDefaultWavFileNameTextCodec();
    static void setDefaultWavFileNameTextCodec(QTextCodec *value);

    bool isTextCodecFollowDefault() const;
    void setTextCodecFollowDefault(bool value);

    bool isTextCodecAutoDetect() const;
    void setTextCodecAutoDetect(bool value);

    bool hasTextCodecAutoDetected() const;
    float getCharacterFileAutoDetectConfidence() const;
    float getReadmeFileAutoDetectConfidence() const;

    static bool isDefalutTextCodecAutoDetect();
    static void setDefalutTextCodecAutoDetect(bool value);

    void saveSettings();

    QStringList getWavFileName() const;
    QByteArrayList getWavFileNameRaw() const;
    QStringList getWavFilePath() const;
    void clearWavFileReadStage();


    QString getSampleFileName() const;

    //错误标识类
    ///描述 VoiceBank 从文件夹中读取信息时发现的错误
    /*!
      此类是抽象类，具体错误描述由子类提供。\n
      使用 getErrorHTMLString() 来获得对于遇到的错误的描述。
    */
    class ErrorState{

    public:
        explicit ErrorState();
        virtual QString getErrorHTMLString() = 0;/*!< 遇到的错误的具体描述。将会返回一个 HTML 片段，包含了展现错误时的相关样式（如字体颜色、前缀等）。*/
        virtual ~ErrorState();
    };

    QList<ErrorState*> getErrorStates() const;
    QString getCategory() const;

    void setCategory(const QString &value);

    QStringList getLabels() const;
    void setLabels(const QStringList &value);
    void appendLabel(const QString& label);
    void appendLabels(const QStringList& label);
    void toggleLabelStatus(const QString& label);
    void removeLabel(const QString &label);


    ///VoiceBank在文件无法打开时会抛出该异常
    /*!
    许多情况下 VoiceBank 会自动处理文件无法打开的问题，但某些函数可能依旧会抛出该异常以要求干预。
  */
    class FileCanNotOpen : public std::runtime_error{
    public:
        FileCanNotOpen(const QString QFileError);
        const QString& QFileError() const;
    private:
        QString _QFileError;
    };
    ///VoiceBank在无法加载WAV文件名时会抛出该异常
    /*!
    许多情况下 VoiceBank 会自动处理无法加载WAV文件名的问题，但某些函数可能依旧会抛出该异常以要求干预。
  */
    class WavFileNameNotLoad : public std::runtime_error{
    public:
        WavFileNameNotLoad();
    };

    static bool isVoiceBankPath(const QString &path);


    ///VoiceBank 读取线程的执行者
    /*!
      此类继承于 QRunnable ，用于以多线程读取VoiceBank。\n
      一般来说您不需要使用此类，而是直接使用 addVoiceBank(QString& path) 。
    */
    class VoiceBankReadFuctionRunner : public QRunnable
    {
    public:
        enum ReadType {
            FirstRead,
            Reload
        };
        VoiceBankReadFuctionRunner(VoiceBank* voicebank,ReadType readType = FirstRead);
        void run() override;
    private:
        VoiceBank* voicebank;
        ReadType readType;
    };
    friend VoiceBankReadFuctionRunner;

    static int getThreadPoolMaxThreadCount() {
        ///获得读取 VoiceBank 所需信息时所用的最大线程数
        return threadPool->maxThreadCount();
    }

    static void setThreadPoolMaxThreadCount(int maxCount);

    QString getAuthor() const;

    bool askFileInfo();
    class FileInfoStruct{
        friend VoiceBank;
        FileInfoStruct(bool isValid,uint fileCount,uint dirCount,uint64_t fileTotalSize);
    public:
        const bool isValid;
        const uint fileCount;
        const uint dirCount;
        const uint64_t fileTotalSize;
    };
    const FileInfoStruct getfileInfoStruct(){
        return FileInfoStruct(fileInfoStruct->isFileInfoReaded,fileInfoStruct->fileCount,fileInfoStruct->dirCount,fileInfoStruct->fileTotalSize);
    }
private:
    QImage _image;
    QString imagePath;
    QString imagePathRelative;
    bool imageLoaded = false;
    QString name;
    QString readme;
    QString path;
    QString character_sample;
    QString author;
    QTextCodec* CharacterTextCodec;
    QTextCodec* ReadmeTextCodec;
    QTextCodec* wavFileNameTextCodec;
    bool textCodecFollowDefault = true;
    bool textCodecAutoDetect = false;
    bool textCodecAutoDetected = false;
    float characterFileAutoDetectConfidence = 0.0f;
    float readmeFileAutoDetectConfidence = 0.0f;
    QList<ErrorState*> errorStates;
    void readCharacterFile();
    void readReadme();
    void changeCharacterFile();
    void autoDetectTextFileCodecs();
    static inline QTextCodec* DefaultCharacterTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec* DefaultReadmeTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec* DefaultWavFileNameTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline bool DefalutIsTextCodecAutoDetect = false;
    void readSettings();
    struct WavFileNameStruct{
        bool isWavFileNameReaded = false;
        QStringList wavFileName{};
        QStringList wavFilePath{};
    } * wavFileNameStruct = new WavFileNameStruct;

    struct FileInfoStructPrivate{
        bool isFileInfoReaded = false;
        uint fileCount = 0;
        uint dirCount = 0;
        uint64_t fileTotalSize = 0;
        QMutex mutex;
    } * fileInfoStruct = new FileInfoStructPrivate;

    QString category;
    QStringList labels;
    bool needRecommmendCategoryAndLabels;
    QString recommmendCategory;
    QStringList recommendLabels;
    void readTextCodec_FollowDefault(QJsonObject json);

    void readTextCodec_AutoDetect(QJsonObject json);

    void readTextCodec_ChracterFile(QJsonObject json);

    void readTextCodec_ReadmeFile(QJsonObject json);

    void readTextCodec_WavFileName(QJsonObject json);

    void readCategory(QJsonObject json);

    void readLabels(QJsonObject json);
    class CharacterFileNotExistsErrorState : public ErrorState{
    public:
        explicit CharacterFileNotExistsErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class NameNotSetErrorState : public ErrorState{
    public:
        explicit NameNotSetErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class ImageFileNotSetErrorState : public ErrorState{
    public:
        explicit ImageFileNotSetErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class ImageFileNotExistsErrorState : public ErrorState{
    public:
        explicit ImageFileNotExistsErrorState(const QString imagePath);
        virtual QString getErrorHTMLString() override;
    private:
        QString imagePath;
    };
    class ImageFileSuffixNotFitFileError : public ErrorState{
    public:
        explicit ImageFileSuffixNotFitFileError();
        virtual QString getErrorHTMLString() override;
    };
    class ImageFileNotFitErrorState : public ErrorState{
    public:
        explicit ImageFileNotFitErrorState(int act_width, int act_height);
        virtual QString getErrorHTMLString() override;
    private:
        int act_width = 0, act_height = 0;
    };
    class ImageFileReadErrorState : public ErrorState{
    public:
        explicit ImageFileReadErrorState(const QString& errorString);
        virtual QString getErrorHTMLString() override;
    private:
        QString errorString;
    };
    class ReadmeFileNotExistsErrorState : public ErrorState{
    public:
        explicit ReadmeFileNotExistsErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class ImageReadExceptionErrorState : public ErrorState{
    public:
        explicit ImageReadExceptionErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class ReadmeFileCanNotOpenErrorState : public ErrorState{
    public:
        explicit ReadmeFileCanNotOpenErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class CharacterFileCanNotOpenErrorState : public ErrorState{
    public:
        explicit CharacterFileCanNotOpenErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class CharacterFileTextCodecCanNotDetectErrorState : public ErrorState{
    public:
        explicit CharacterFileTextCodecCanNotDetectErrorState();
        virtual QString getErrorHTMLString() override;
    };
    class ReadmeFileTextCodecCanNotDetectErrorState : public ErrorState{
    public:
        explicit ReadmeFileTextCodecCanNotDetectErrorState();
        virtual QString getErrorHTMLString() override;
    };

    void clear();
    static void readStaticSettings();
    void readWavFileName() const;
    void lazyLoadWavFileName() const;
    QString pickAWAVFileName() const;

    static QThreadPool* threadPool;
    static void readThreadPoolMaxThreadCountSettings();
    static void saveThreadPoolMaxThreadCountSettings();

    class Garbo {
    public:
        Garbo(){
            readThreadPoolMaxThreadCountSettings();
            readStaticSettings();
        }

        ~Garbo(){
            saveThreadPoolMaxThreadCountSettings();
        }
    };

    static Garbo garbo;
    friend Garbo;
    void readFromPathPrivate();
    void doReadFromPath();

    void readImage();

private slots:
    void fileInfoReadCompleteEmitter();
signals:
    void firstReadDone(VoiceBank *);
    void reloadDone(VoiceBank *);
    void readDone(VoiceBank *);
    void statusOutput(const QString&);
    void backupImageFileBecauseExists(VoiceBank *);
    void cannotBackupImageFile(VoiceBank *);
    void categoryChanged();
    void labelsChanged();
    void fileInfoReadComplete(VoiceBank *);
};



#endif // VOICEBANK_H
