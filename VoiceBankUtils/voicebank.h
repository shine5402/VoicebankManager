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
class VoiceBank : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBank(QString path,QObject *parent = nullptr);
    ~VoiceBank();
    QImage getImage() const;
    void setImage(const QImage &value);

    QString getName() const;
    void setName(const QString &value);

    QString getReadme() const;
    void setReadme(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    void readFromPath();
    QString getCalculateInformation();
    enum ProbablyErrors {
        CharacterFileNotExists,NameNotSet,ImageFileNotSet,ImageFileNotExists,ImageFileNotFit,ReadmeFileNotExists,PixmapReadException,ReadmeFileCanNotOpen,CharacterFileCanNotOpen
    };
    QHash<ProbablyErrors, bool> getErrors() const;

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
        FileCanNotOpen():std::runtime_error(u8"File can not open."){}
    };
    static void setDefaultCharacterTextCodec(QTextCodec *value);

    static void setDefaultReadmeTextCodec(QTextCodec *value);

    static QTextCodec *getDefaultCharacterTextCodec();

    static QTextCodec *getDefaultReadmeTextCodec();
    static void readStaticSettings();
    void readFromPathWithoutEmit();

    bool getIsFollowDefault() const;
    void setIsFollowDefault(bool value);
    void saveSettings();
private:
    QImage image;
    QString pixmapPath;
    QString name;
    QString readme;
    QString path;
    QString calculateInformation;
    QTextCodec *CharacterTextCodec;
    QTextCodec *ReadmeTextCodec;
    bool isTextCodecFollowDefault = true;
    QHash<ProbablyErrors,bool>errors{};
    void readCharacterFile();
    void readReadme();
    QString readTextFileInTextCodec(const QString &path,QTextCodec* textCodec);
    static inline QTextCodec *DefaultCharacterTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline QTextCodec *DefaultReadmeTextCodec = QTextCodec::codecForName(defaultTextCodecName);
    static inline bool isReadStaticSettings = false;
    void readSettings();

signals:
    void readDone(VoiceBank *);
    void statusOutput(const QString&);
};



#endif // VOICEBANK_H
