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
#include <../LeafPublicQtClasses/leaflogger.h>
#include <public_defines.h>
#include <QPainter>
class VoiceBank : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBank(QString path,QObject *parent = nullptr);
    ~VoiceBank();
    QImage getImage() const;
    void setImage(const QImage &value);

    QString getName() const;

    QString getReadme() const;
    void setReadme(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    void readFromPath();
    //错误标识类
    class ErrorState{
    public:
        explicit ErrorState(VoiceBank* voiceBank){
            if (voiceBank)
                this->voiceBank = voiceBank;
        }
        virtual QString getErrorHTMLString() = 0;
        virtual ~ErrorState(){}
    protected:
        VoiceBank* voiceBank = nullptr;
    };
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
    QString getPixmapPath() const;

    QTextCodec *getCharacterTextCodec() const;
    void setCharacterTextCodec(QTextCodec *value);

    QTextCodec *getReadmeTextCodec() const;
    void setReadmeTextCodec(QTextCodec *value);
    class FileNotExists : public std::runtime_error{
    public:
        FileNotExists():std::runtime_error(u8"File not exists."){}
    };
    class FileCanNotOpen : public std::runtime_error{
    public:
        FileCanNotOpen(const QString QFileError):std::runtime_error(u8"File can not open."),_QFileError(QFileError){}
        const QString& QFileError() const{return _QFileError;}
    private:
        QString _QFileError;
    };
    static void setDefaultCharacterTextCodec(QTextCodec *value);
    static void setDefaultReadmeTextCodec(QTextCodec *value);

    static QTextCodec *getDefaultCharacterTextCodec();

    static QTextCodec *getDefaultReadmeTextCodec();
    static void readStaticSettings();

    bool getIsFollowDefault() const;
    void setIsFollowDefault(bool value);
    void saveSettings();
    bool getIsWavFileNameReaded() const;

    static QTextCodec *getDefaultWavFileNameTextCodec();
    static void setDefaultWavFileNameTextCodec(QTextCodec *value);

    void readWavFileName();

    QTextCodec *getWavFileNameTextCodec() const;
    void setWavFileNameTextCodec(QTextCodec *value);

    QStringList getWavFileName() const;

    // QHash<QString, QString> getWavFileNameReDecoded() const;

    QByteArrayList getWavFileNameRaw() const;
    void clearWavFileReadStage();
    void decodeWavFileName();

    QStringList getWavFilePath() const;
    QList<ErrorState *> getErrorStates() const;
    bool isFirstRead() const{
        return ReadCount == 1 || ReadCount == 0;
    }
    void rename(const QString& name);
    void changeImage(const QPixmap& _image, QString newImageFileName = "icon.jpg");
    void clear();

private:
    QImage image;
    QString imagePath;
    QString imagePathRelative;
    QString name;
    QString readme;
    QString path;
    //QString calculateInformation;
    QTextCodec *CharacterTextCodec;
    QTextCodec *ReadmeTextCodec;
    QTextCodec *wavFileNameTextCodec;
    bool isTextCodecFollowDefault = true;
    QList<ErrorState *> errorStates;
    void readCharacterFile();
    void readReadme();
    void changeCharacterFile();
    QString readTextFileInTextCodec(const QString &path,QTextCodec* textCodec);
    static inline QTextCodec *DefaultCharacterTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec *DefaultReadmeTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec *DefaultWavFileNameTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline bool isReadStaticSettings = false;
    void readSettings();
    bool isWavFileNameReaded = false;
    QStringList wavFileName{};
    QByteArrayList wavFileNameRaw{};
    QStringList wavFilePath{};
    //bool firstRead = true;
    int ReadCount = 0;
    void writeTextFileInTextCodec(const QString &content, const QString &path, QTextCodec *textCodec);
signals:
    void readDone(VoiceBank *);
    void statusOutput(const QString&);
    void backupImageFileBecauseExists(VoiceBank *);
    void cannotBackupImageFile(VoiceBank *);
};



#endif // VOICEBANK_H
