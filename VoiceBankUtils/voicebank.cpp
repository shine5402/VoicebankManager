#include "voicebank.h"

VoiceBank::VoiceBank(QString path, QObject *parent) : QObject(parent),path(path),CharacterTextCodec(DefaultCharacterTextCodec),ReadmeTextCodec(DefaultReadmeTextCodec),wavFileNameTextCodec(DefaultWavFileNameTextCodec)
{

}

VoiceBank::~VoiceBank()
{
    saveSettings();
    for (auto state : errorStates)
    {
        if (state)
            delete state;
    }
}
QImage VoiceBank::getImage() const
{
    return image;
}

void VoiceBank::setImage(const QImage &value)
{
    image = value;
}

QString VoiceBank::getName() const
{
    return name;
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
        LeafLogger::LogMessage(QString(u8"%1不存在。").arg(file->fileName()));
        file->deleteLater();
        throw FileNotExists();}
    else
    {
        if (file->open(QIODevice::ReadOnly | QIODevice::Text)){
            auto RawData = file->readAll();
            file->close();
            file->deleteLater();
            QTextDecoder *decoder = textCodec->makeDecoder();
            auto String = decoder->toUnicode(RawData);
            delete decoder;
            return String;
        }
        else
        {
            LeafLogger::LogMessage(QString(u8"读取%1时发生错误。错误描述为：%2").arg(path).arg(file->errorString()));
        }
    }
    return QString();
}

void VoiceBank::writeTextFileInTextCodec(const QString& content, const QString& path,QTextCodec* textCodec){
    QFile* file = new QFile(path);
    if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextEncoder *encoder= textCodec->makeEncoder();
        file->write(encoder->fromUnicode(content));
        delete encoder;
        file->close();
        file->deleteLater();
    }
    else
    {
        LeafLogger::LogMessage(QString(u8"写入模式打开%1时发生错误。错误描述为：%2").arg(path).arg(file->errorString()));
    }
}
QTextCodec *VoiceBank::getDefaultWavFileNameTextCodec()
{
    return DefaultWavFileNameTextCodec;
}

void VoiceBank::setDefaultWavFileNameTextCodec(QTextCodec *value)
{
    DefaultWavFileNameTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/WavFileName",DefaultReadmeTextCodec->name());
    LeafLogger::LogMessage(QString(u8"DefaultWavFileNameNameTextCodec被设置为%1").arg(QString::fromUtf8(DefaultReadmeTextCodec->name())));
}

void VoiceBank::decodeWavFileName()
{
    if (!wavFileName.isEmpty())
    {
        QTextEncoder encoder(QTextCodec::codecForLocale());
        QTextDecoder decoder(wavFileNameTextCodec);
        for (auto name : wavFileName)
        {
            auto raw = encoder.fromUnicode(name);
            wavFileNameRaw.append(raw);
        }
    }
}

void VoiceBank::readWavFileName()
{
    if (!isWavFileNameReaded){
        wavFileName.clear();
        //wavFilePathNameAndDecoded.clear();
        wavFilePath.clear();
        QDir dir(path);
        wavFileName.append(dir.entryList({u8"*.wav"},QDir::Files|QDir::NoDotAndDotDot));
        auto subdirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        if (!subdirs.isEmpty())
        {
            for (auto subDirPath : subdirs)
            {
                QDir subdir(path + subDirPath);
                wavFileName.append(subdir.entryList({u8"*.wav"},QDir::Files|QDir::NoDotAndDotDot));
                for (auto fileName : wavFileName)
                {
                    wavFilePath.append(path + subDirPath + u8"/" + fileName);
                }
            }
        }
        decodeWavFileName();
    }
}

QTextCodec *VoiceBank::getWavFileNameTextCodec() const
{
    return wavFileNameTextCodec;
}

void VoiceBank::setWavFileNameTextCodec(QTextCodec *value)
{
    if (value){
        wavFileNameTextCodec = value;
    }
    else
        wavFileNameTextCodec = DefaultCharacterTextCodec;
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
        if (settings.contains("DefaultTextCodec/WavFileName")){
            auto readmeCodecName = settings.value("DefaultTextCodec/WavFileName");
            DefaultReadmeTextCodec = QTextCodec::codecForName(readmeCodecName.toByteArray());
        }
        isReadStaticSettings = true;
    }
}

void VoiceBank::readSettings(){
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
                        setIsFollowDefault(value.toBool());
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
                if (json.contains(u8"TextCodec/WavFileName"))
                {

                    auto value = json.value(u8"TextCodec/WavFileName");
                    if (value.isString()){
                        auto value_string = value.toString();
                        setWavFileNameTextCodec(QTextCodec::codecForName(value_string.toUtf8()));
                    }
                    else
                    {
                        LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/WavFileName不是String。").arg(path));
                    }
                }
                else
                    LeafLogger::LogMessage(QString(u8"声库%1的TextCodec/WavFileName不存在。").arg(path));
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

QStringList VoiceBank::getWavFilePath() const
{
    return wavFilePath;
}

QList<VoiceBank::ErrorState *> VoiceBank::getErrorStates() const
{
    return errorStates;
}

void VoiceBank::rename(const QString &name)
{
    this->name = name;
    try
    {
        changeCharacterFile();
    }
    catch(FileNotExists& e){
        readFromPath();
        throw e;
    }
    catch(FileCanNotOpen& e){
        throw e;
    }
    readFromPath();
}


QByteArrayList VoiceBank::getWavFileNameRaw() const
{
    return wavFileNameRaw;
}

void VoiceBank::clearWavFileReadStage()
{
    wavFileName.clear();
    wavFileNameRaw.clear();
    wavFilePath.clear();
    isWavFileNameReaded = false;
}


QStringList VoiceBank::getWavFileName() const
{
    return wavFileName;
}

bool VoiceBank::getIsWavFileNameReaded() const
{
    return isWavFileNameReaded;
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
        json.insert(u8"TextCodec/WavFileName",QString::fromUtf8(wavFileNameTextCodec->name()));
    }
    QJsonDocument json_doc(json);
    auto json_file = new QFile(path + u8"leafUTAUQtSettings.json");
    json_file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream json_writer(json_file);
    json_writer << json_doc.toJson();
    json_file->close();
    json_file->deleteLater();
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
    LeafLogger::LogMessage(QString(u8"DefaultReadmeTextCodec被设置为%1").arg(QString::fromUtf8(DefaultReadmeTextCodec->name())));
}

void VoiceBank::setDefaultCharacterTextCodec(QTextCodec *value)
{
    DefaultCharacterTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/CharacterFile",DefaultCharacterTextCodec->name());
    LeafLogger::LogMessage(QString(u8"DefaultCharacterTextCodec被设置为%1").arg(QString::fromUtf8(DefaultCharacterTextCodec->name())));
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
        LeafLogger::LogMessage(QString(u8"%1的character.txt被成功读取至characterString。").arg(path));
        auto characterList = characterString.split("\n",QString::SplitBehavior::SkipEmptyParts);
        for (auto i : characterList){
            i = i.trimmed();
            auto list = i.split("=",QString::SplitBehavior::SkipEmptyParts);
            if (list.count() >= 2)
            {
                if (list.at(0).compare(u8"name",Qt::CaseInsensitive) == 0){
                    name = list.at(1);
                    LeafLogger::LogMessage(QString(u8"%1的name为%2").arg(path).arg(name));
                }
                if (list.at(0).compare(u8"image",Qt::CaseInsensitive) == 0)
                {
                    imagePath = path + list.at(1);
                    QFileInfo imageFileInfo(imagePath);
                    if (imageFileInfo.exists()) {
                        try {
                            image.load(imagePath);
                            LeafLogger::LogMessage(QString(u8"%1的image成功读取。大小为：%2*%3").arg(path).arg(image.width()).arg(image.height()));

                            if (image.height() == 0 ||(!qFuzzyCompare(image.width() / image.height() , 1.0))){
                                errorStates.append(new ImageFileNotFitErrorState(this));
                            }
                        } catch (std::exception &e){
                            LeafLogger::LogMessage(QString(u8"程序运行过程中在VoiceBank::readCharacterFile中读取image时发生了一个异常。异常说明为%1").arg(e.what()));
                            errorStates.append(new ImageReadExceptionErrorState(this));
                            image = QImage();
                        }
                        catch (...) {
                            LeafLogger::LogMessage(u8"程序运行过程中在VoiceBank::readCharacterFile中读取image时发生了一个由通用捕捉器捕捉的异常。");
                            errorStates.append(new ImageReadExceptionErrorState(this));
                            image = QImage();
                        }

                    }
                    else
                    {
                        errorStates.append(new ImageFileNotExistsErrorState(this));
                        LeafLogger::LogMessage(QString(u8"%1的音源图片文件不存在。").arg(path));
                    }

                }
            }
        }
        if (name.isEmpty()){
            errorStates.append(new NameNotSetErrorState(this));
            LeafLogger::LogMessage(QString(u8"%1的音源的name字段不存在。").arg(path));
        }
        if (imagePath.isEmpty()){
            errorStates.append(new ImageFileNotSetErrorState(this));
            LeafLogger::LogMessage(QString(u8"%1的音源的image字段不存在。").arg(path));}
    }
    catch(FileNotExists&){
        errorStates.append(new CharacterFileNotExistsErrorState(this));
        LeafLogger::LogMessage(QString(u8"%1的音源的character.txt不存在。").arg(path));
    }
    catch(FileCanNotOpen&)
    {
        errorStates.append(new CharacterFileCanNotOpenErrorState(this));
        LeafLogger::LogMessage(QString(u8"%1的音源的character.txt无法打开。").arg(path));
    }

}
void VoiceBank::readReadme()
{
    try{
        if (!isTextCodecFollowDefault)
            readme = readTextFileInTextCodec(path + u8"readme.txt",ReadmeTextCodec);
        else
            readme = readTextFileInTextCodec(path + u8"readme.txt",DefaultReadmeTextCodec);
        LeafLogger::LogMessage(QString(u8"%1的readme.txt被成功读取至readmeString。").arg(path));
    }
    catch(FileNotExists&){
        errorStates.append(new ReadmeFileNotExistsErrorState(this));
        LeafLogger::LogMessage(QString(u8"%1的音源的readme.txt不存在。").arg(path));
    }
    catch(FileCanNotOpen&)
    {
        errorStates.append(new ReadmeFileCanNotOpenErrorState(this));
        LeafLogger::LogMessage(QString(u8"%1的音源的readme.txt无法打开。").arg(path));
    }
}

void VoiceBank::changeCharacterFile()
{
    try
    {
        QString characterString{};
        if (!isTextCodecFollowDefault)
            characterString = readTextFileInTextCodec(path + u8"character.txt",CharacterTextCodec);
        else
            characterString = readTextFileInTextCodec(path + u8"character.txt",DefaultCharacterTextCodec);
        LeafLogger::LogMessage(QString(u8"%1的character.txt被成功读取至characterString。").arg(path));
        QString newCharacterString{};
        QTextStream readStream(&characterString);
        QTextStream writeStream(&newCharacterString);
        while (!readStream.atEnd())
        {
            auto line = readStream.readLine();
            if (line.trimmed().startsWith(u8"name=",Qt::CaseInsensitive))
            {
                line = QString("name=%1").arg(name);
            }
            writeStream << line << endl;
        }
        newCharacterString = newCharacterString.trimmed();
        if (!isTextCodecFollowDefault)
            writeTextFileInTextCodec(newCharacterString,path + u8"character.txt",CharacterTextCodec);
        else
            writeTextFileInTextCodec(newCharacterString,path + u8"character.txt",DefaultCharacterTextCodec);

    }
    catch(FileNotExists& e){
        LeafLogger::LogMessage(QString(u8"%1的音源的character.txt不存在。").arg(path));
        QString newCharacterString{};
        QTextStream writeStream(&newCharacterString);
        writeStream << QString("name=%1").arg(name) << endl
                    << QString("image=%1").arg(imagePath) << endl;
        newCharacterString = newCharacterString.trimmed();
        if (!isTextCodecFollowDefault)
            writeTextFileInTextCodec(newCharacterString,path + u8"character.txt",CharacterTextCodec);
        else
            writeTextFileInTextCodec(newCharacterString,path + u8"character.txt",DefaultCharacterTextCodec);
        throw e;
    }
    catch(FileCanNotOpen& e)
    {
        LeafLogger::LogMessage(QString(u8"%1的音源的character.txt无法打开。").arg(path));
        throw e;
    }
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
    path = QDir::fromNativeSeparators(path);
    if (!path.endsWith(u8"/")){
        path.append(u8"/");
    }
    if (!errorStates.isEmpty())
    {
        for (auto state : errorStates)
            delete state;
    }
    errorStates.clear();
    clearWavFileReadStage();
    readSettings();
    readCharacterFile();
    readReadme();
    //firstRead = false;
    ++ReadCount;
    emit readDone(this);
}

QString VoiceBank::getCalculateInformation()
{
    return calculateInformation;
}


QString VoiceBank::getPixmapPath() const
{
    return imagePath;
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

VoiceBank::CharacterFileNotExistsErrorState::CharacterFileNotExistsErrorState(VoiceBank *voiceBank) :ErrorState(voiceBank)
{

}

QString VoiceBank::CharacterFileNotExistsErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：没有为此音源库找到character.txt。在音源使用过程中将无法查看音源名称、图像等信息。</p>)");
    }
    else
        return QString();
}

VoiceBank::NameNotSetErrorState::NameNotSetErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::NameNotSetErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：character.txt中的name字段没有被设定。在音源使用过程中音源区域将显示文件夹名称。</p>)");
    }
    else
        return QString();
}

VoiceBank::ImageFileNotSetErrorState::ImageFileNotSetErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::ImageFileNotSetErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：character.txt中的image字段没有被设定。在音源使用过程中音源区域将不显示图片。</p>)");
    }
    else
        return QString();
}

VoiceBank::ImageFileNotExistsErrorState::ImageFileNotExistsErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::ImageFileNotExistsErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。</p>)").arg(voiceBank->getPixmapPath());
    }
    else
        return QString();
}

VoiceBank::ImageFileNotFitErrorState::ImageFileNotFitErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::ImageFileNotFitErrorState::getErrorHTMLString()
{
    if (voiceBank){
        if (voiceBank->getImage().isNull())
            return tr(u8R"(<p style="color:red">错误：character.txt中设定的图片文件没有正常读取。是不是图片格式与后缀名不符？亦或是文件损坏？</p>)");
        else
            return tr(u8R"(<p style="color:red">错误：character.txt中设定的图片文件（%1*%2）不符合UTAU的图标要求（比例1:1）。在音源使用过程中将音源区域图片可能显示不正确，或者无法显示。</p>)").arg(voiceBank->getImage().width()).arg(voiceBank->getImage().height());
    }
    else
        return QString();
}

VoiceBank::ReadmeFileNotExistsErrorState::ReadmeFileNotExistsErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::ReadmeFileNotExistsErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：找不到readme.txt。音源的README将无法显示。</p>)");
    }
    else
        return QString();
}

VoiceBank::ImageReadExceptionErrorState::ImageReadExceptionErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::ImageReadExceptionErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：在读取音源图片时发生了一个异常。或许重载此音源能解决这个问题。</p>)");
    }
    else
        return QString();
}

VoiceBank::ReadmeFileCanNotOpenErrorState::ReadmeFileCanNotOpenErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::ReadmeFileCanNotOpenErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：无法打开readme.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。</p>)");
    }
    else
        return QString();
}

VoiceBank::CharacterFileCanNotOpenErrorState::CharacterFileCanNotOpenErrorState(VoiceBank *voiceBank) : ErrorState(voiceBank)
{

}

QString VoiceBank::CharacterFileCanNotOpenErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr(u8R"(<p style="color:red">错误：无法打开character.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。</p>)");
    }
    else
        return QString();
}
