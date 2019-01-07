#include "voicebank.h"

VoiceBank::VoiceBank(QString path, QObject *parent) : QObject(parent),path(path),CharacterTextCodec(DefaultCharacterTextCodec),ReadmeTextCodec(DefaultReadmeTextCodec),wavFileNameTextCodec(DefaultWavFileNameTextCodec)
{
    /*!
      VoiceBank 的构造函数。它将设置 VoiceBank 的路径，并将所有文本编码设置置为默认。但它 **不会** 进行读取操作。您应当手动调用 readFromPath() 。
      \param[in] path 声库的路径
      \param[in] parent 父对象，是否设置对 VoiceBank 的行为没有影响。默认为 nullptr 。
    */

}

VoiceBank::~VoiceBank()
{
    /*!
      VoiceBank 的析构函数。它将保存 VoiceBank 的设置到路径下的 leafUTAUQtSettings.json 中。
    */
    saveSettings();
    for (auto state : errorStates)
    {
        if (state)
            delete state;
    }
}

QString VoiceBank::getName() const
{
    ///获得音源库的名称。
    /*!
      音源库的名称是指在 character.txt 的 name 字段中定义的音源名称。
      \return 音源库的名称。
      \see setName(const QString& name)
    */
    return name;
}

QString VoiceBank::getReadme() const
{
    ///获得 VoiceBank 的 readme 信息。
    /*!
      音源库的 readme 信息保存于路径下的 readme.txt 文件中。该信息将在音源详情页面等位置显示。
    */
    return readme;
}

QImage VoiceBank::getImage() const
{
    ///获得该声库的图标。
    /*!
      音源库的图标是指在 character.txt 的 image 字段中定义的音源的图标。在 character.txt 中的值为其路径。 VoiceBank 会将其读取到 QImage 实例中。\n
      建议音源库的图标尺寸为 100*100 ，或至少宽高比为 1:1 。
      \return 包含音源图标的 QImage 。
      \see setImage(const QImage& _image, const QString &newImageFileName)
    */
    return _image;
}


QString VoiceBank::getPath() const
{
    return path;
}

QString VoiceBank::readTextFileInTextCodec(const QString& path, QTextCodec *textCodec)
{
    QFile* file = new QFile(path);
    if (!file->exists()){
        LeafLogger::LogMessage(QString("%1不存在。").arg(file->fileName()));
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
            LeafLogger::LogMessage(QString("读取%1时发生错误。错误描述为：%2").arg(path).arg(file->errorString()));
        }
    }
    return QString();
}

bool VoiceBank::getDefalutIsTextCodecAutoDetect()
{
    return DefalutIsTextCodecAutoDetect;
}

void VoiceBank::setDefalutIsTextCodecAutoDetect(bool value)
{
    DefalutIsTextCodecAutoDetect = value;
    QSettings settings;
    settings.setValue("DefaultTextCodec/AutoDetect",DefalutIsTextCodecAutoDetect);
    LeafLogger::LogMessage(QString("DefaultTextCodec/AutoDetect被设置为%1").arg(DefalutIsTextCodecAutoDetect));
}

bool VoiceBank::getIsTextCodecAutoDetect() const
{
    return isTextCodecAutoDetect;
}

void VoiceBank::setIsTextCodecAutoDetect(bool value)
{
    isTextCodecAutoDetect = value;
}

float VoiceBank::getCharacterFileAutoDetectConfidence() const
{
    return characterFileAutoDetectConfidence;
}

float VoiceBank::getReadmeFileAutoDetectConfidence() const
{
    return readmeFileAutoDetectConfidence;
}

bool VoiceBank::getHasTextCodecAutoDetected() const
{
    return hasTextCodecAutoDetected;
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
        LeafLogger::LogMessage(QString("写入模式打开%1时发生错误。错误描述为：%2").arg(path).arg(file->errorString()));
    }
}

QStringList VoiceBank::getLabels() const
{
    return labels;
}

void VoiceBank::setLabels(const QStringList &value)
{
    labels = value;
    emit labelsChanged();
}

void VoiceBank::appendLabel(const QString &label)
{
    if (!labels.contains(label))
        labels.append(label);
    emit labelsChanged();
}

void VoiceBank::appendLabels(const QStringList &label)
{
    for (auto i : label)
        appendLabel(i);
}

void VoiceBank::toggleLabelStatus(const QString &label)
{
    if (labels.contains(label))
        removeLabel(label);
    else
        appendLabel(label);
}

void VoiceBank::removeLabel(const QString &label)
{
    labels.removeOne(label);
    emit labelsChanged();
}

bool VoiceBank::isVoiceBankPath(const QString &path)
{
    return (QFileInfo(path + "/character.txt").exists() || QFileInfo(path + "/prefix.map").exists() || QFileInfo(path + "/oto.ini").exists());
}
void VoiceBank::setCategory(const QString &value)
{
    category = value;
    emit categoryChanged();
}

QString VoiceBank::getCategory() const
{
    return category;
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
    LeafLogger::LogMessage(QString("DefaultWavFileNameNameTextCodec被设置为%1").arg(QString::fromUtf8(DefaultReadmeTextCodec->name())));
}

void VoiceBank::decodeWavFileName()
{
    if (!wavFileName.isEmpty())
    {
        QTextEncoder encoder(QTextCodec::codecForLocale());
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
        wavFilePath.clear();
        QDir dir(path);
        wavFileName.append(dir.entryList({"*.wav"},QDir::Files|QDir::NoDotAndDotDot));
        for (auto fileName : wavFileName)
        {
            wavFilePath.append(path + fileName);
        }
        auto subdirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        if (!subdirs.isEmpty())
        {
            for (auto subDirPath : subdirs)
            {
                QDir subdir(path + subDirPath);
                wavFileName.append(subdir.entryList({"*.wav"},QDir::Files|QDir::NoDotAndDotDot));
                auto subWavFileName = subdir.entryList({"*.wav"},QDir::Files|QDir::NoDotAndDotDot);
                for (auto fileName : subWavFileName)
                {
                    wavFilePath.append(path + subDirPath + "/" + fileName);
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
        if (settings.contains("DefaultTextCodec/AutoDetect")){
            DefalutIsTextCodecAutoDetect = settings.value("DefaultTextCodec/AutoDetect",false).toBool();
        }
        isReadStaticSettings = true;
    }
}

void VoiceBank::readTextCodec_FollowDefault(QJsonObject json)
{
    if (json.contains("TextCodec/FollowDefault")){
        auto value = json.value("TextCodec/FollowDefault");
        if (value.isBool()){
            setIsFollowDefault(value.toBool());
        }
        else
            LeafLogger::LogMessage(QString("声库%1的TextCodec/FollowDefault不是Bool。").arg(path));
    }
    else
    {
        LeafLogger::LogMessage(QString("声库%1的TextCodec/FollowDefault不存在。").arg(path));
    }
}

void VoiceBank::readTextCodec_AutoDetect(QJsonObject json)
{
    if (json.contains("TextCodec/AutoDetect"))
    {
        auto value = json.value("TextCodec/AutoDetect");
        isTextCodecAutoDetect = value.toBool(true);
    }
    else
    {
        LeafLogger::LogMessage(QString("声库%1的TextCodec/AutoDetect不存在。").arg(path));
    }
}

void VoiceBank::readTextCodec_ChracterFile(QJsonObject json)
{
    if (json.contains("TextCodec/CharacterFile"))
    {

        auto value = json.value("TextCodec/CharacterFile");
        if (value.isString()){
            auto value_string = value.toString();
            setCharacterTextCodec(QTextCodec::codecForName(value_string.toUtf8()));
        }
        else
        {
            LeafLogger::LogMessage(QString("声库%1的TextCodec/CharacterFile不是String。").arg(path));
        }
    }
    else
        LeafLogger::LogMessage(QString("声库%1的TextCodec/CharacterFile不存在。").arg(path));
}

void VoiceBank::readTextCodec_ReadmeFile(QJsonObject json)
{
    if (json.contains("TextCodec/ReadmeFile"))
    {
        auto value = json.value("TextCodec/ReadmeFile");
        if (value.isString()){
            auto value_string = value.toString();
            setReadmeTextCodec(QTextCodec::codecForName(value_string.toUtf8()));
        }
        else
        {
            LeafLogger::LogMessage(QString("声库%1的TextCodec/ReadmeFile不是String。").arg(path));
        }
    }
    else
        LeafLogger::LogMessage(QString("声库%1的TextCodec/ReadmeFile不存在。").arg(path));
}

void VoiceBank::readTextCodec_WavFileName(QJsonObject json)
{
    if (json.contains("TextCodec/WavFileName"))
    {
        auto value = json.value("TextCodec/WavFileName");
        if (value.isString()){
            auto value_string = value.toString();
            setWavFileNameTextCodec(QTextCodec::codecForName(value_string.toUtf8()));
        }
        else
        {
            LeafLogger::LogMessage(QString("声库%1的TextCodec/WavFileName不是String。").arg(path));
        }
    }
    else
        LeafLogger::LogMessage(QString("声库%1的TextCodec/WavFileName不存在。").arg(path));
}

void VoiceBank::readCategory(QJsonObject json)
{
    if (json.contains("Category"))
    {
        auto value = json.value("Category");
        if (value.isString()){
            setCategory(value.toString());
        }
        else
        {
            LeafLogger::LogMessage(QString("声库%1的Category不是String。").arg(path));
        }
    }
    else
        LeafLogger::LogMessage(QString("声库%1的Category不存在。").arg(path));
}

void VoiceBank::readLabels(QJsonObject json)
{
    if (json.contains("Labels"))
    {
        auto value = json.value("Labels");
        if (value.isArray()){
            auto array = value.toArray();
            auto vlist = array.toVariantList();
            for (auto i : vlist)
            {
                labels.append(i.toString());
            }
            emit labelsChanged();
        }
        else
        {
            LeafLogger::LogMessage(QString("声库%1的Labels不是Array。").arg(path));
        }
    }
    else
        LeafLogger::LogMessage(QString("声库%1的Labels不存在。").arg(path));
}

void VoiceBank::readSettings(){
    LeafLogger::LogMessage(QString("开始读取%1的声库单独设置。").arg(path));
    try{
        auto text = readTextFileInTextCodec(path + "leafUTAUQtSettings.json",QTextCodec::codecForName("UTF-8"));
        QJsonParseError json_error;
        auto json_doc = QJsonDocument::fromJson(text.toUtf8(),&json_error);
        if (!json_doc.isNull()){
            QJsonObject json = json_doc.object();
            if (!json.isEmpty()){
                readTextCodec_FollowDefault(json);
                readTextCodec_AutoDetect(json);
                readTextCodec_ChracterFile(json);
                readTextCodec_ReadmeFile(json);
                readTextCodec_WavFileName(json);
                readCategory(json);
                readLabels(json);
                if ((!isTextCodecFollowDefault && isTextCodecAutoDetect) || (isTextCodecFollowDefault && DefalutIsTextCodecAutoDetect))
                    autoDetectTextFileCodecs();
            }
            else
            {
                LeafLogger::LogMessage(QString("声库%1的设置json读取后的Object为空。").arg(path));
            }
        }
        else
        {
            LeafLogger::LogMessage(QString("声库%1的设置json读取出现问题。QJsonParseError的输出为%2。").arg(path).arg(json_error.errorString()));
        }
    }
    catch(FileNotExists&){
        LeafLogger::LogMessage(QString("声库%1的设置json不存在。").arg(path));
    }
}

void VoiceBank::saveSettings(){
    LeafLogger::LogMessage(QString("开始保存%1的声库单独设置。").arg(path));
    QJsonObject json;
    if (isTextCodecFollowDefault)
        json.insert("TextCodec/FollowDefault",true);
    else
    {
        json.insert("TextCodec/FollowDefault",false);
        json.insert("TextCodec/AutoDetect",isTextCodecAutoDetect);
        json.insert("TextCodec/CharacterFile",QString::fromUtf8(CharacterTextCodec->name()));
        json.insert("TextCodec/ReadmeFile",QString::fromUtf8(ReadmeTextCodec->name()));
        json.insert("TextCodec/WavFileName",QString::fromUtf8(wavFileNameTextCodec->name()));
    }
    if (!category.isEmpty())
        json.insert("Category",category);
    if (!labels.isEmpty()){
        QJsonArray array;
        for (auto i : labels)
        {
            array.append(i);
        }
        json.insert("Labels",array);
    }
    QJsonDocument json_doc(json);
    auto json_file = new QFile(path + "leafUTAUQtSettings.json");
    json_file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream json_writer(json_file);
    json_writer.setCodec(QTextCodec::codecForName("UTF-8"));
    json_writer << json_doc.toJson();
    json_file->close();
    json_file->deleteLater();
}

QStringList VoiceBank::getWavFilePath() const
{
    return wavFilePath;
}

QList<VoiceBank::ErrorState *> VoiceBank::getErrorStates() const
{
    return errorStates;
}

void VoiceBank::setName(const QString &name)
{
    ///重命名一个音源库
    /*!
      VoiceBank 会将新名称写入路径下的 character.txt 中，并自动重载。
      \param[in] name 音源库的新名称
      \throw FileCanNotOpen
      \throw FileNotExists
    */
    this->name = name;
    try
    {
        changeCharacterFile();
    }
    catch(FileNotExists& e){
        //changeCharacterFile()会处理文件不存在的情况，但新建文件后下需要重载。
        readFromPath();
        throw e;
    }
    catch(FileCanNotOpen& e){
        throw e;
    }
    readFromPath();
}

void VoiceBank::setImage(const QImage &image, const QString& newImageFileName)
{
    ///改变一个音源库的图标
    /*!
      \param[in] image 该音源库的新图标。 VoiceBank 会尝试将其缩放为 100*100 。
      \param[in] newImageFileName 音源库新图标的文件名。 VoiceBank 将自动推断文件格式并保存。在有同名文件存在时， VoiceBank 会尝试备份原有图标。
      \throw FileCanNotOpen
      \throw FileNotExists
    */
    _image = image;
    if (QFileInfo(path + newImageFileName).exists())
    {
        if (QFileInfo(imagePath + ".bak").exists())
            QFile(imagePath + ".bak").remove();
        if (QFile(imagePath).rename(imagePath + ".bak"))
        {
            emit backupImageFileBecauseExists(this);
        }
        else
        {
            emit cannotBackupImageFile(this);
            return;
        }
    }
    _image = _image.scaled(100,100);
    QImage imageWhiteBackgroud(_image.size(),_image.format());
    imageWhiteBackgroud.fill(QColor(Qt::white).rgb());
    QPainter painter(&imageWhiteBackgroud);
    painter.drawImage(0, 0, _image);
    imageWhiteBackgroud.save(path + newImageFileName);
    imagePathRelative = newImageFileName;
    changeCharacterFile();
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
    LeafLogger::LogMessage(QString("DefaultReadmeTextCodec被设置为%1").arg(QString::fromUtf8(DefaultReadmeTextCodec->name())));
}

void VoiceBank::setDefaultCharacterTextCodec(QTextCodec *value)
{
    DefaultCharacterTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/CharacterFile",DefaultCharacterTextCodec->name());
    LeafLogger::LogMessage(QString("DefaultCharacterTextCodec被设置为%1").arg(QString::fromUtf8(DefaultCharacterTextCodec->name())));
}

void VoiceBank::readCharacterFile()
{
    try
    {
        QString characterString{};
        if (!isTextCodecFollowDefault || (isTextCodecFollowDefault && DefalutIsTextCodecAutoDetect))
            characterString = readTextFileInTextCodec(path + "character.txt",CharacterTextCodec);
        else
            characterString = readTextFileInTextCodec(path + "character.txt",DefaultCharacterTextCodec);
        LeafLogger::LogMessage(QString("%1的character.txt被成功读取至characterString。").arg(path));
        auto characterList = characterString.split("\n",QString::SplitBehavior::SkipEmptyParts);
        for (auto i : characterList){
            i = i.trimmed();
            auto list = i.split("=",QString::SplitBehavior::SkipEmptyParts);
            if (list.count() >= 2)
            {
                if (list.at(0).compare("name",Qt::CaseInsensitive) == 0){
                    name = list.at(1);
                    LeafLogger::LogMessage(QString("%1的name为%2").arg(path).arg(name));
                }
                if (list.at(0).compare("image",Qt::CaseInsensitive) == 0)
                {
                    imagePath = path + list.at(1);
                    imagePathRelative = list.at(1);
                    QFileInfo imageFileInfo(imagePath);
                    if (imageFileInfo.exists()) {
                        try {
                            _image.load(imagePath);
                            LeafLogger::LogMessage(QString("%1的image成功读取。大小为：%2*%3").arg(path).arg(_image.width()).arg(_image.height()));

                            if (_image.height() == 0 ||(!qFuzzyCompare(_image.width() / _image.height() , 1.0))){
                                errorStates.append(new ImageFileNotFitErrorState(this));
                            }
                        } catch (std::exception &e){
                            LeafLogger::LogMessage(QString("程序运行过程中在VoiceBank::readCharacterFile中读取image时发生了一个异常。异常说明为%1").arg(e.what()));
                            errorStates.append(new ImageReadExceptionErrorState(this));
                            _image = QImage();
                        }
                        catch (...) {
                            LeafLogger::LogMessage("程序运行过程中在VoiceBank::readCharacterFile中读取image时发生了一个由通用捕捉器捕捉的异常。");
                            errorStates.append(new ImageReadExceptionErrorState(this));
                            _image = QImage();
                        }

                    }
                    else
                    {
                        errorStates.append(new ImageFileNotExistsErrorState(this));
                        LeafLogger::LogMessage(QString("%1的音源图片文件不存在。").arg(path));
                    }
                }
                if (list.at(0).compare("sample",Qt::CaseInsensitive) == 0){
                    auto decoder = QTextCodec::codecForLocale()->makeDecoder();
                    auto encoder = CharacterTextCodec->makeEncoder();
                    sample = decoder->toUnicode(encoder->fromUnicode(list.at(1)));
                    LeafLogger::LogMessage(QString("%1的sample为%2").arg(path).arg(sample));
                }
            }
        }
        if (name.isEmpty()){
            errorStates.append(new NameNotSetErrorState(this));
            LeafLogger::LogMessage(QString("%1的音源的name字段不存在。").arg(path));
        }
        if (imagePath.isEmpty()){
            errorStates.append(new ImageFileNotSetErrorState(this));
            LeafLogger::LogMessage(QString("%1的音源的image字段不存在。").arg(path));}
    }
    catch(FileNotExists&){
        errorStates.append(new CharacterFileNotExistsErrorState(this));
        LeafLogger::LogMessage(QString("%1的音源的character.txt不存在。").arg(path));
    }
    catch(FileCanNotOpen&)
    {
        errorStates.append(new CharacterFileCanNotOpenErrorState(this));
        LeafLogger::LogMessage(QString("%1的音源的character.txt无法打开。").arg(path));
    }

}
void VoiceBank::readReadme()
{
    try{
        if (!isTextCodecFollowDefault || (isTextCodecFollowDefault && DefalutIsTextCodecAutoDetect))
            readme = readTextFileInTextCodec(path + "readme.txt",ReadmeTextCodec);
        else
            readme = readTextFileInTextCodec(path + "readme.txt",DefaultReadmeTextCodec);
        LeafLogger::LogMessage(QString("%1的readme.txt被成功读取至readmeString。").arg(path));
    }
    catch(FileNotExists&){
        errorStates.append(new ReadmeFileNotExistsErrorState(this));
        LeafLogger::LogMessage(QString("%1的音源的readme.txt不存在。").arg(path));
    }
    catch(FileCanNotOpen&)
    {
        errorStates.append(new ReadmeFileCanNotOpenErrorState(this));
        LeafLogger::LogMessage(QString("%1的音源的readme.txt无法打开。").arg(path));
    }
}

void VoiceBank::changeCharacterFile()
{
    try
    {
        QString characterString{};
        if (!isTextCodecFollowDefault)
            characterString = readTextFileInTextCodec(path + "character.txt",CharacterTextCodec);
        else
            characterString = readTextFileInTextCodec(path + "character.txt",DefaultCharacterTextCodec);
        LeafLogger::LogMessage(QString("%1的character.txt被成功读取至characterString。").arg(path));
        QString newCharacterString{};
        QTextStream readStream(&characterString);
        QTextStream writeStream(&newCharacterString);
        while (!readStream.atEnd())
        {
            auto line = readStream.readLine();
            if (line.trimmed().startsWith("name=",Qt::CaseInsensitive))
            {
                line = QString("name=%1").arg(name);
            }
            if (line.trimmed().startsWith("image=",Qt::CaseInsensitive))
            {
                line = QString("image=%1").arg(imagePathRelative);
            }
            writeStream << line << endl;
        }
        newCharacterString = newCharacterString.trimmed();
        if (!isTextCodecFollowDefault)
            writeTextFileInTextCodec(newCharacterString,path + "character.txt",CharacterTextCodec);
        else
            writeTextFileInTextCodec(newCharacterString,path + "character.txt",DefaultCharacterTextCodec);

    }
    catch(FileNotExists& e){
        LeafLogger::LogMessage(QString("%1的音源的character.txt不存在。").arg(path));
        QString newCharacterString{};
        QTextStream writeStream(&newCharacterString);
        writeStream << QString("name=%1").arg(name) << endl
                    << QString("image=%1").arg(imagePath) << endl;
        newCharacterString = newCharacterString.trimmed();
        if (!isTextCodecFollowDefault)
            writeTextFileInTextCodec(newCharacterString,path + "character.txt",CharacterTextCodec);
        else
            writeTextFileInTextCodec(newCharacterString,path + "character.txt",DefaultCharacterTextCodec);
        throw e;
    }
    catch(FileCanNotOpen& e)
    {
        LeafLogger::LogMessage(QString("%1的音源的character.txt无法打开。").arg(path));
        throw e;
    }
}

void VoiceBank::autoDetectTextFileCodecs()
{
    CharacterTextCodec = QChardet::encodingForFile(path + "character.txt",&characterFileAutoDetectConfidence);
    ReadmeTextCodec = QChardet::encodingForFile(path + "readme.txt",&readmeFileAutoDetectConfidence);
    int notAvaliableDetectCount = 0;
    if (!CharacterTextCodec){
        CharacterTextCodec = DefaultCharacterTextCodec;
        errorStates.append(new CharacterFileTextCodecCanNotDetectErrorState(this));
        ++notAvaliableDetectCount;
    }
    if (!ReadmeTextCodec)
    {
        ReadmeTextCodec = DefaultReadmeTextCodec;
        errorStates.append(new ReadmeFileTextCodecCanNotDetectErrorState(this));
        ++notAvaliableDetectCount;
    }
    if (notAvaliableDetectCount < 2)
        hasTextCodecAutoDetected = true;
}

bool VoiceBank::getIsFollowDefault() const
{
    return isTextCodecFollowDefault;
}

void VoiceBank::setIsFollowDefault(bool value)
{
    isTextCodecFollowDefault = value;
}

void VoiceBank::clear()
{
    name.clear();
    _image = QImage();
    imagePath.clear();
    imagePathRelative.clear();
    readme.clear();
    sample.clear();
    if (!errorStates.isEmpty())
    {
        for (auto state : errorStates)
            delete state;
    }
    errorStates.clear();
    clearWavFileReadStage();
    hasTextCodecAutoDetected = false;
    category.clear();
    labels.clear();
}

QString VoiceBank::getSample() const
{
    return sample;
}

void VoiceBank::readFromPath()
{
    path = QDir::fromNativeSeparators(path);
    if (!path.endsWith("/")){
        path.append("/");
    }
    clear();
    readSettings();
    readCharacterFile();
    readReadme();
    //firstRead = false;
    ++ReadCount;
    emit readDone(this);
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
        return tr("<p style=\"color:red\">错误：没有为此音源库找到character.txt。在音源使用过程中将无法查看音源名称、图像等信息。</p>");
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
        return tr("<p style=\"color:red\">错误：character.txt中的name字段没有被设定。在音源使用过程中音源区域将显示文件夹名称。</p>");
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
        return tr("<p style=\"color:red\">错误：character.txt中的image字段没有被设定。在音源使用过程中音源区域将不显示图片。</p>");
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
        return tr("<p style=\"color:red\">错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。</p>").arg(voiceBank->getPixmapPath());
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
            return tr("<p style=\"color:red\">错误：character.txt中设定的图片文件没有正常读取。是不是图片格式与后缀名不符？亦或是文件损坏？</p>");
        else
            return tr("<p style=\"color:red\">错误：character.txt中设定的图片文件（%1*%2）不符合UTAU的图标要求（比例1:1）。在音源使用过程中将音源区域图片可能显示不正确，或者无法显示。</p>").arg(voiceBank->getImage().width()).arg(voiceBank->getImage().height());
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
        return tr("<p style=\"color:red\">错误：找不到readme.txt。音源的README将无法显示。</p>");
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
        return tr("<p style=\"color:red\">错误：在读取音源图片时发生了一个异常。或许重载此音源能解决这个问题。</p>");
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
        return tr("<p style=\"color:red\">错误：无法打开readme.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。</p>");
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
        return tr("<p style=\"color:red\">错误：无法打开character.txt。或许被其他程序占用了？或者是文件系统问题？日志可以提供更多信息。</p>");
    }
    else
        return QString();
}

VoiceBank::CharacterFileTextCodecCanNotDetectErrorState::CharacterFileTextCodecCanNotDetectErrorState(VoiceBank *voiceBank) : ErrorState (voiceBank)
{

}

QString VoiceBank::CharacterFileTextCodecCanNotDetectErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr("<p style=\"color:orange\">警告：无法探测character.txt的编码。程序将使用默认编码。</p>");
    }
    else
        return QString();
}

VoiceBank::ReadmeFileTextCodecCanNotDetectErrorState::ReadmeFileTextCodecCanNotDetectErrorState(VoiceBank *voiceBank) : ErrorState (voiceBank)
{

}

QString VoiceBank::ReadmeFileTextCodecCanNotDetectErrorState::getErrorHTMLString()
{
    if (voiceBank){
        return tr("<p style=\"color:orange\">警告：无法探测readme.txt的编码。程序将使用默认编码。</p>");
    }
    else
        return QString();
}
