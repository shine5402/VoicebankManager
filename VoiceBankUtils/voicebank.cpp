#include "voicebank.h"

VoiceBank::VoiceBank(QString path, QObject *parent) : QObject(parent),path(path),CharacterTextCodec(DefaultCharacterTextCodec),ReadmeTextCodec(DefaultReadmeTextCodec)
{

}

VoiceBank::~VoiceBank()
{
    saveSettings();
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
    if (!file->exists()){
        delete file;
        throw FileNotExists();}
    else
    {
        file->open(QIODevice::ReadOnly | QIODevice::Text);
        auto RawData = file->readAll();
        file->close();
        delete file;
        QTextDecoder *decoder = textCodec->makeDecoder();
        auto String = decoder->toUnicode(RawData);
        delete decoder;
        return String;
    }
}

void VoiceBank::readStaticSettings()
{
    if (!isReadStaticSettings){
        QSettings settings{};

        if (settings.contains("DefaultTextCodec/CharacterFile")){
            auto characterCodecName = settings.value("DefaultTextCodec/CharacterFile");
            DefaultCharacterTextCodec = QTextCodec::codecForName(characterCodecName.toByteArray());
        }

        if (settings.contains("DefaultTextCodec/ReadmeFile")){
            auto readmeCodecName = settings.value("DefaultTextCodec/ReadmeFile");
            DefaultReadmeTextCodec = QTextCodec::codecForName(readmeCodecName.toByteArray());
        }
        isReadStaticSettings = true;
    }
}

void VoiceBank::readSettings(){
    //FIXME:读取失效，怀疑是后面新的设置函数调用进行了覆盖。
    LeafLogger::LogMessage(QString(u8"开始读取%1的声库单独设置。").arg(path));
    try{
    auto text = readTextFileInTextCodec(path + u8"leafUTAUQtSettings.json",QTextCodec::codecForName("UTF-8"));
    QJsonParseError json_error;
    auto json_doc = QJsonDocument::fromJson(text.toUtf8(),&json_error);
    if (!json_doc.isNull()){
        auto json = json_doc.object();
        if (!json.isEmpty()){
            if (json.contains(u8"TextCodec/FollowDefault")){
                auto value = json.value(u8"TextCodec/FollowDefault");
                if (value.isBool()){

                }else
                    LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/FollowDefault不是Bool。").arg(path));
            }
            else
                LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/FollowDefault不存在。").arg(path));
            if (json.contains(u8"TextCodec/CharacterFile"))
            {

                auto value = json.value(u8"TextCodec/CharacterFile");
                if (value.isString()){
                    auto value_string = value.toString();
                    setCharacterTextCodec(QTextCodec::codecForName(value_string.toUtf8()));
                }
                else
                {
                    LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/CharacterFile不是String。").arg(path));
                }
            }
            else
                LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/CharacterFile不存在。").arg(path));
            if (json.contains(u8"TextCodec/ReadmeFile"))
            {
                auto value = json.value(u8"TextCodec/ReadmeFile");
                if (value.isString()){
                    auto value_string = value.toString();
                    setReadmeTextCodec(QTextCodec::codecForName(value_string.toUtf8()));
                }
                else
                {
                    LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/ReadmeFile不是String。").arg(path));
                }
            }
            else
                LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/ReadmeFile不存在。").arg(path));
        }
        else
        {
            LeafLogger::LogMessage(QString(u8"声库%1的设置json读取后的Object为空。").arg(path));
        }
    }
    else
    {
        LeafLogger::LogMessage(QString(u8"声库%1的设置json读取出现问题。QJsonParseError的输出为%2。").arg(path).arg(json_error.errorString()));
    }
    }
    catch(FileNotExists&){
        LeafLogger::LogMessage(QString(u8"声库%1的设置json不存在。").arg(path));
    }
}

void VoiceBank::saveSettings(){
    LeafLogger::LogMessage(QString(u8"开始保存%1的声库单独设置。").arg(path));
    QJsonObject json;
    if (isTextCodecFollowDefault)
        json.insert(u8"TextCodec/FollowDefault",true);
    else
    {
        json.insert(u8"TextCodec/FollowDefault",false);
        json.insert(u8"TextCodec/CharacterFile",QString::fromUtf8(CharacterTextCodec->name()));
        json.insert(u8"TextCodec/ReadmeFile",QString::fromUtf8(ReadmeTextCodec->name()));
    }
    QJsonDocument json_doc(json);
    auto json_file = new QFile(path + u8"leafUTAUQtSettings.json");
    json_file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream json_writer(json_file);
    json_writer << json_doc.toJson();
    json_file->close();
    delete json_file;
}

QTextCodec *VoiceBank::getDefaultReadmeTextCodec()
{
    return DefaultReadmeTextCodec;
}

QTextCodec *VoiceBank::getDefaultCharacterTextCodec()
{
    return DefaultCharacterTextCodec;
}

void VoiceBank::setDefaultReadmeTextCodec(QTextCodec *value)
{
    DefaultReadmeTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/ReadmeFile",DefaultReadmeTextCodec->name());
}

void VoiceBank::setDefaultCharacterTextCodec(QTextCodec *value)
{
    DefaultCharacterTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/CharacterFile",DefaultCharacterTextCodec->name());
}

void VoiceBank::readCharacterFile()
{
    try
    {
        QString characterString{};
        if (!isTextCodecFollowDefault)
            characterString = readTextFileInTextCodec(path + u8"character.txt",CharacterTextCodec);
        else
            characterString = readTextFileInTextCodec(path + u8"character.txt",DefaultCharacterTextCodec);
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
                    try {
                        pixmap.load(pixmapPath);
                    } catch (...) {
                        auto dialog = new QMessageBox(QMessageBox::Warning,tr(u8"发生了一个异常"),tr(u8"程序运行过程中在VoiceBank::readCharacterFile中读取pixmap时发生了一个异常。\n由于当前是通用捕捉器捕捉的异常，我们无法提供更多信息。\n您可以继续使用程序，但程序可能不稳定。"),QMessageBox::Ok);
                        dialog->exec();
                        dialog->deleteLater();
                    }
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
    catch(FileNotExists&){
        errors.insert(ProbablyErrors::CharacterFileNotExists,true);
    }

}
void VoiceBank::readReadme()
{
    try{
        if (!isTextCodecFollowDefault)
            readme = readTextFileInTextCodec(path + u8"readme.txt",ReadmeTextCodec);
        else
            readme = readTextFileInTextCodec(path + u8"readme.txt",DefaultReadmeTextCodec);
    }
    catch(FileNotExists&){
        errors.insert(ProbablyErrors::ReadmeFileNotExists,true);
    }
}
void VoiceBank::readFromPathWithoutEmit()
{
    path = QDir::fromNativeSeparators(path);
    if (!path.endsWith(u8"/")){
        path.append(u8"/");
    }
    errors.clear();
    readSettings();
    readCharacterFile();
    readReadme();
}

bool VoiceBank::getIsFollowDefault() const
{
    return isTextCodecFollowDefault;
}

void VoiceBank::setIsFollowDefault(bool value)
{
    isTextCodecFollowDefault = value;
}

void VoiceBank::readFromPath()
{
    readFromPathWithoutEmit();
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
    if (value){
        CharacterTextCodec = value;
    }
    else
        CharacterTextCodec = DefaultCharacterTextCodec;
}

QTextCodec *VoiceBank::getReadmeTextCodec() const
{
    return ReadmeTextCodec;
}

void VoiceBank::setReadmeTextCodec(QTextCodec *value)
{
    if (value){
        ReadmeTextCodec = value;
    }
    else
        ReadmeTextCodec = DefaultReadmeTextCodec;
}
