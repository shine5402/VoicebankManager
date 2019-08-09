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
        explicit ErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() = 0;/*!< 遇到的错误的具体描述。将会返回一个 HTML 片段，包含了展现错误时的相关样式（如字体颜色、前缀等）。*/
        virtual ~ErrorState();
    protected:
        VoiceBank* voiceBank = nullptr;///<构造时提供的 VoiceBank 指针。 ErrorState 可能使用它来获取信息。
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

    ///VoiceBank在处理一个不存在的文件时可能会抛出该异常
    /*!
      许多情况下 VoiceBank 会自动处理文件不存在的问题，但某些函数可能依旧会抛出该异常以要求干预。
    */
    //TODO:变成内部异常
    class FileNotExists : public std::runtime_error{
    public:
        FileNotExists();
    };

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

private:
    QImage _image;
    QString imagePath;
    QString imagePathRelative;
    QString name;
    QString readme;
    QString path;
    QString character_sample;
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
    QString readTextFileInTextCodec(const QString &path,QTextCodec* textCodec);
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
        explicit CharacterFileNotExistsErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class NameNotSetErrorState : public ErrorState{
    public:
        explicit NameNotSetErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ImageFileNotSetErrorState : public ErrorState{
    public:
        explicit ImageFileNotSetErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ImageFileNotExistsErrorState : public ErrorState{
    public:
        explicit ImageFileNotExistsErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ImageFileNotFitErrorState : public ErrorState{
    public:
        explicit ImageFileNotFitErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ReadmeFileNotExistsErrorState : public ErrorState{
    public:
        explicit ReadmeFileNotExistsErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ImageReadExceptionErrorState : public ErrorState{
    public:
        explicit ImageReadExceptionErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ReadmeFileCanNotOpenErrorState : public ErrorState{
    public:
        explicit ReadmeFileCanNotOpenErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class CharacterFileCanNotOpenErrorState : public ErrorState{
    public:
        explicit CharacterFileCanNotOpenErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class CharacterFileTextCodecCanNotDetectErrorState : public ErrorState{
    public:
        explicit CharacterFileTextCodecCanNotDetectErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() override;
    };
    class ReadmeFileTextCodecCanNotDetectErrorState : public ErrorState{
    public:
        explicit ReadmeFileTextCodecCanNotDetectErrorState(VoiceBank* voiceBank);
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

signals:
    void firstReadDone(VoiceBank *);
    void reloadDone(VoiceBank *);
    void readDone(VoiceBank *);
    void statusOutput(const QString&);
    void backupImageFileBecauseExists(VoiceBank *);
    void cannotBackupImageFile(VoiceBank *);
    void categoryChanged();
    void labelsChanged();
};



#endif // VOICEBANK_H
