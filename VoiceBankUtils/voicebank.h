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
    QPixmap getImage() const;
    void setImage(const QPixmap &value);

    QString getName() const;
    void setName(const QString &value);

    QString getReadme() const;
    void setReadme(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    QTextCodec *getTextCodec() const;
    void setTextCodec(QTextCodec *value);

    void readFromPath();
    QString getCalculateInformation();

private:
    QPixmap image;
    QString name;
    QString readme;
    QString path;//must have "/" in the end.
    QString calculateInformation;
    QTextCodec *textCodec = QTextCodec::codecForName("Shift-JIS");
    enum ProbablyErrors {
        CharacterFileNotExists,ImageFileNotExists,ImageFileNotFit,ReadmeFileNotExists
    };
    QHash<ProbablyErrors,bool>errors{};
    void readCharacterFile();
    void readReadme();
    QString readTextFileInTextCodec(QString& path);

signals:
    void readDone(VoiceBank *);
};



#endif // VOICEBANK_H
