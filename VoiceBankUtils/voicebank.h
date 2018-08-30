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
class VoiceBank : public QObject
{
    Q_OBJECT
public:
    explicit VoiceBank(QString path,QObject *parent = nullptr);
    QPixmap getPixmap() const;
    void setImage(const QPixmap &value);

    QString getName() const;
    void setName(const QString &value);

    QString getReadme() const;
    void setReadme(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    void readFromPath();
    QString getCalculateInformation();
    enum ProbablyErrors {
        CharacterFileNotExists,NameNotSet,ImageFileNotSet,ImageFileNotExists,ImageFileNotFit,ReadmeFileNotExists
    };
    QHash<ProbablyErrors, bool> getErrors() const;

    QString getPixmapPath() const;

    QTextCodec *getCharacterTextCodec() const;
    void setCharacterTextCodec(QTextCodec *value);

    QTextCodec *getReadmeTextCodec() const;
    void setReadmeTextCodec(QTextCodec *value);

private:
    QPixmap pixmap;
    QString pixmapPath;
    QString name;
    QString readme;
    QString path;
    QString calculateInformation;
    QTextCodec *CharacterTextCodec = QTextCodec::codecForName("Shift-JIS");
    QTextCodec *ReadmeTextCodec = QTextCodec::codecForName("Shift-JIS");
    QHash<ProbablyErrors,bool>errors{};
    void readCharacterFile();
    void readReadme();
    QString readTextFileInTextCodec(const QString &path,QTextCodec* textCodec);
    static inline QTextCodec *DefaultCharacterTextCodec = QTextCodec::codecForName("Shift-JIS");
    static inline QTextCodec *DefaultReadmeTextCodec = QTextCodec::codecForName("Shift-JIS");
signals:
    void readDone(VoiceBank *);
};



#endif // VOICEBANK_H
