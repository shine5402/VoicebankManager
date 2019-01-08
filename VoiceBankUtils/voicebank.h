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
#include "./TextCodecUtils/qchardet.h"
#include <QJsonArray>
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

    QString getName() const;
    void setName(const QString& name);

    QImage getImage() const;
    QString getImagePath() const;
    void setImage(const QImage& _image, const QString &newImageFileName = "icon.jpg");

    QString getReadme() const;

    QString getPath() const;

    void readFromPath();

    QTextCodec *getCharacterTextCodec() const;
    void setCharacterTextCodec(QTextCodec *value);

    QTextCodec *getReadmeTextCodec() const;
    void setReadmeTextCodec(QTextCodec *value);

    QTextCodec *getWavFileNameTextCodec() const;
    void setWavFileNameTextCodec(QTextCodec *value);

    static QTextCodec *getDefaultCharacterTextCodec();
    static void setDefaultCharacterTextCodec(QTextCodec *value);

    static QTextCodec *getDefaultReadmeTextCodec();
    static void setDefaultReadmeTextCodec(QTextCodec *value);

    static QTextCodec *getDefaultWavFileNameTextCodec();
    static void setDefaultWavFileNameTextCodec(QTextCodec *value);

    bool isTextCodecFollowDefault() const;
    void setTextCodecFollowDefault(bool value);

    bool isTextCodecAutoDetect() const;
    void setTextCodecAutoDetect(bool value);

    static bool isDefalutTextCodecAutoDetect();
    static void setDefalutTextCodecAutoDetect(bool value);

    void saveSettings();

    void readWavFileName();

    QStringList getWavFileName() const;

    QByteArrayList getWavFileNameRaw() const;
    void clearWavFileReadStage();
    void decodeWavFileName();

    QStringList getWavFilePath() const;

    bool isFirstRead() const{
        return ReadCount == 1 || ReadCount == 0;
    }

    QString getSample() const;





    float getCharacterFileAutoDetectConfidence() const;

    float getReadmeFileAutoDetectConfidence() const;

    bool getHasTextCodecAutoDetected() const;

    //错误标识类
    class ErrorState{
    public:
        explicit ErrorState(VoiceBank* voiceBank);
        virtual QString getErrorHTMLString() = 0;
        virtual ~ErrorState();
    protected:
        VoiceBank* voiceBank = nullptr;
    };

    QList<ErrorState *> getErrorStates() const;
    QString getCategory() const;

    void setCategory(const QString &value);

    QStringList getLabels() const;
    void setLabels(const QStringList &value);
    void appendLabel(const QString& label);
    void appendLabels(const QStringList& label);
    void toggleLabelStatus(const QString& label);

    class FileNotExists : public std::runtime_error{
    public:
        FileNotExists();
    };
    class FileCanNotOpen : public std::runtime_error{
    public:
        FileCanNotOpen(const QString QFileError);
        const QString& QFileError() const;
    private:
        QString _QFileError;
    };
    void removeLabel(const QString &label);

    static bool isVoiceBankPath(const QString &path);
private:
    QImage _image;
    QString imagePath;
    QString imagePathRelative;
    QString name;
    QString readme;
    QString path;
    QString sample;
    QTextCodec *CharacterTextCodec;
    QTextCodec *ReadmeTextCodec;
    QTextCodec *wavFileNameTextCodec;
    bool textCodecFollowDefault = true;
    bool textCodecAutoDetect = true;
    bool hasTextCodecAutoDetected = false;
    float characterFileAutoDetectConfidence = 0.0f;
    float readmeFileAutoDetectConfidence = 0.0f;
    QList<ErrorState *> errorStates;
    void readCharacterFile();
    void readReadme();
    void changeCharacterFile();
    void autoDetectTextFileCodecs();
    QString readTextFileInTextCodec(const QString &path,QTextCodec* textCodec);
    static inline QTextCodec *DefaultCharacterTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec *DefaultReadmeTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec *DefaultWavFileNameTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline bool isReadStaticSettings = false;
    static inline bool DefalutIsTextCodecAutoDetect = false;
    void readSettings();
    bool isWavFileNameReaded = false;
    QStringList wavFileName{};
    QByteArrayList wavFileNameRaw{};
    QStringList wavFilePath{};
    //bool firstRead = true;
    int ReadCount = 0;
    void writeTextFileInTextCodec(const QString &content, const QString &path, QTextCodec *textCodec);
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
signals:
    void readDone(VoiceBank *);
    void statusOutput(const QString&);
    void backupImageFileBecauseExists(VoiceBank *);
    void cannotBackupImageFile(VoiceBank *);
    void categoryChanged();
    void labelsChanged();
};



#endif // VOICEBANK_H
