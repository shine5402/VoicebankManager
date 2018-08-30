#include "voicebank.h"

VoiceBank::VoiceBank(QString path, QObject *parent) : QObject(parent),path(path),CharacterTextCodec(DefaultCharacterTextCodec),ReadmeTextCodec(DefaultReadmeTextCodec)
{

}

QPixmap VoiceBank::getPixmap() const
{
    return pixmap;
}

void VoiceBank::setImage(const QPixmap &value)
{
    pixmap = value;
}

QString VoiceBank::getName() const
{
    return name;
}

void VoiceBank::setName(const QString &value)
{
    name = value;
}

QString VoiceBank::getReadme() const
{
    return readme;
}

void VoiceBank::setReadme(const QString &value)
{
    readme = value;
}

QString VoiceBank::getPath() const
{
    return path;
}

void VoiceBank::setPath(const QString &value)
{
    path = value;
}



QString VoiceBank::readTextFileInTextCodec(const QString& path, QTextCodec *textCodec)
{
    QFile* file = new QFile(path);
    if (!file->exists())
        throw std::runtime_error(u8"File not exists");
    else
    {
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    auto RawData = file->readAll();
    delete file;
    QTextDecoder *decoder = textCodec->makeDecoder();
    auto String = decoder->toUnicode(RawData);
    delete decoder;

    return String;
    }
    return QString();
}

void VoiceBank::readCharacterFile()
{
    try
    {
    auto characterString = readTextFileInTextCodec(path + u8"character.txt",CharacterTextCodec);
    auto characterList = characterString.split("\n",QString::SplitBehavior::SkipEmptyParts);
    for (auto i : characterList){
        i = i.trimmed();
        auto list = i.split("=",QString::SplitBehavior::SkipEmptyParts);

        if (list.at(0).compare(u8"name",Qt::CaseInsensitive) == 0)
            name = list.at(1);
        if (list.at(0).compare(u8"image",Qt::CaseInsensitive) == 0)
        {
            pixmapPath = path + list.at(1);
            QFileInfo imageFileInfo(pixmapPath);
            if (imageFileInfo.exists()) {
                pixmap.load(pixmapPath);
                if (pixmap.width() != 100 || pixmap.height() != 100){
                    errors.insert(ProbablyErrors::ImageFileNotFit,true);
                }
            }
            else
            {
                errors.insert(ProbablyErrors::ImageFileNotExists,true);
            }

        }
    }
    if (name.isEmpty())
        errors.insert(ProbablyErrors::NameNotSet,true);
    if (pixmapPath.isEmpty())
        errors.insert(ProbablyErrors::ImageFileNotSet,true);
    }
    catch(std::runtime_error& e){
        if (std::strcmp(e.what(),u8"File not exists") == 0){
            errors.insert(ProbablyErrors::CharacterFileNotExists,true);
        }
    }

}
void VoiceBank::readReadme()
{
    try{
        readme = readTextFileInTextCodec(path + u8"readme.txt",ReadmeTextCodec);
    }
    catch(std::runtime_error& e){
        if (std::strcmp(e.what(),u8"File not exists") == 0){
            errors.insert(ProbablyErrors::ReadmeFileNotExists,true);
        }
    }
}
void VoiceBank::readFromPath()
{
    path = QDir::fromNativeSeparators(path);
    if (!path.endsWith(u8"/")){
        path.append(u8"/");
    }
    readCharacterFile();
    readReadme();
    emit readDone(this);
}

QString VoiceBank::getCalculateInformation()
{
    return calculateInformation;
}

QHash<VoiceBank::ProbablyErrors, bool> VoiceBank::getErrors() const
{
    return errors;
}

QString VoiceBank::getPixmapPath() const
{
    return pixmapPath;
}

QTextCodec *VoiceBank::getCharacterTextCodec() const
{
    return CharacterTextCodec;
}

void VoiceBank::setCharacterTextCodec(QTextCodec *value)
{
    CharacterTextCodec = value;
}

QTextCodec *VoiceBank::getReadmeTextCodec() const
{
    return ReadmeTextCodec;
}

void VoiceBank::setReadmeTextCodec(QTextCodec *value)
{
    ReadmeTextCodec = value;
}
