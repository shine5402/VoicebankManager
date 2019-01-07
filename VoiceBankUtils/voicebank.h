﻿#ifndef VOICEBANK_H
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

class VoiceBank : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBank(QString path,QObject *parent = nullptr);
    ~VoiceBank();

    QString getName() const;
    void setName(const QString& name);

    QImage getImage() const;
    void setImage(const QImage& _image, const QString &newImageFileName = "icon.jpg");

    QString getReadme() const;

    QString getPath() const;

    void readFromPath();

    QString getPixmapPath() const;

    QTextCodec *getCharacterTextCodec() const;
    void setCharacterTextCodec(QTextCodec *value);

    QTextCodec *getReadmeTextCodec() const;
    void setReadmeTextCodec(QTextCodec *value);

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

    QByteArrayList getWavFileNameRaw() const;
    void clearWavFileReadStage();
    void decodeWavFileName();

    QStringList getWavFilePath() const;

    bool isFirstRead() const{
        return ReadCount == 1 || ReadCount == 0;
    }


    void clear();

    QString getSample() const;

    static bool getDefalutIsTextCodecAutoDetect();
    static void setDefalutIsTextCodecAutoDetect(bool value);

    bool getIsTextCodecAutoDetect() const;
    void setIsTextCodecAutoDetect(bool value);

    float getCharacterFileAutoDetectConfidence() const;

    float getReadmeFileAutoDetectConfidence() const;

    bool getHasTextCodecAutoDetected() const;

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
        FileNotExists():std::runtime_error("File not exists."){}
    };
    class FileCanNotOpen : public std::runtime_error{
    public:
        FileCanNotOpen(const QString QFileError):std::runtime_error("File can not open."),_QFileError(QFileError){}
        const QString& QFileError() const{return _QFileError;}
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
    //QString calculateInformation;
    QTextCodec *CharacterTextCodec;
    QTextCodec *ReadmeTextCodec;
    QTextCodec *wavFileNameTextCodec;
    bool isTextCodecFollowDefault = true;
    bool isTextCodecAutoDetect = true;
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
signals:
    void readDone(VoiceBank *);
    void statusOutput(const QString&);
    void backupImageFileBecauseExists(VoiceBank *);
    void cannotBackupImageFile(VoiceBank *);
    void categoryChanged();
    void labelsChanged();
};



#endif // VOICEBANK_H
