#include "voicebank.h"

VoiceBank::VoiceBank(QString path, QObject *parent) : QObject(parent),path(path)
{

}

QPixmap VoiceBank::getImage() const
{
    return image;
}

void VoiceBank::setImage(const QPixmap &value)
{
    image = value;
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

QTextCodec *VoiceBank::getTextCodec() const
{
    return textCodec;
}

void VoiceBank::setTextCodec(QTextCodec *value)
{
    textCodec = value;
}

QString VoiceBank::readTextFileInTextCodec(QString& path)
{
    QFile* file = new QFile(path);
    if (!file->exists())
        throw std::runtime_error(u8"File not exists");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    auto RawData = file->readAll();
    delete file;
    QTextDecoder *decoder = textCodec->makeDecoder();
    auto String = decoder->toUnicode(RawData);
    delete decoder;

    return String;
}

void VoiceBank::readCharacterFile()
{
    try
    {
    auto characterString = readTextFileInTextCodec(QDir::fromNativeSeparators(path + u8"character.txt"));
    auto characterList = characterString.split("\n",QString::SplitBehavior::SkipEmptyParts);
    for (auto i : characterList){
        i = i.trimmed();
        auto list = i.split("=",QString::SplitBehavior::SkipEmptyParts);
        if (list.at(0) == u8"name")
            name = list.at(1);
        if (list.at(0) == u8"image")
        {
            auto imagePath = path + list.at(1);
            QFileInfo imageFileInfo(imagePath);
            if (imageFileInfo.exists()) {
                image.load(imagePath);
                if (image.width() != 100 || image.height() != 100){
                    errors.insert(ProbablyErrors::ImageFileNotFit,true);
                }
            }
            else
            {
                errors.insert(ProbablyErrors::ImageFileNotExists,true);
            }

        }
    }
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
        readme = readTextFileInTextCodec(QDir::fromNativeSeparators(path + u8"readme.txt"));
    }
    catch(std::runtime_error& e){
        if (std::strcmp(e.what(),u8"File not exists") == 0){
            errors.insert(ProbablyErrors::ReadmeFileNotExists,true);
        }
    }
}
void VoiceBank::readFromPath()
{
    readCharacterFile();
    readReadme();
    emit readDone(this);
}

QString VoiceBank::getCalculateInformation()
{
    return calculateInformation;
}
