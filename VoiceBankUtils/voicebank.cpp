#include "voicebank.h"

VoiceBank::VoiceBank(QString path, QObject *parent) : QObject(parent),path(path),CharacterTextCodec(DefaultCharacterTextCodec),ReadmeTextCodec(DefaultReadmeTextCodec),wavFileNameTextCodec(DefaultWavFileNameTextCodec)
{
    /*!
      VoiceBank 的构造函数。它将设置 VoiceBank 的路径，并将所有文本编码设置置为默认。但它 **不会** 进行读取操作。您应当手动调用 readFromPath() 。
      \param[in] path 声库的路径
      \param[in] parent 父对象，是否设置对 VoiceBank 的行为没有影响。默认为 nullptr 。
    */
    readStaticSettings();
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
    ///获得该音源库的图标。
    /*!
      音源库的图标是指在 character.txt 的 image 字段中定义的音源的图标。在 character.txt 中的值为其路径。 VoiceBank 会将其读取到 QImage 实例中。\n
      建议音源库的图标尺寸为 100*100 ，或至少宽高比为 1:1 。
      \return 包含音源图标的 QImage 。
      \see setImage(const QImage& _image, const QString &newImageFileName)
    */
    return _image;
}

QString VoiceBank::getImagePath() const
{
    ///获得该音源库的图标的路径。
    /*!
      如果您要使用该图标，建议直接使用 getImage() const 。
      \return 音源库图标的路径。
      \see getImage() const
    */
    return imagePath;
}

QString VoiceBank::getPath() const
{
    ///获得该音源库的路径
    /*!
      音源库的路径是指音源库文件存放的文件夹位置。您应当直接在构造函数中设置，因为在没有路径的情况下，所有 VoiceBank 类的功能都将失效。
      \return 音源库的路径
    */
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

bool VoiceBank::isDefalutTextCodecAutoDetect()
{
    ///返回默认情况下 VoiceBank 读取音源库的文本文件时的文本编码是否由程序自动推断
    /*!
      \return 默认情况下 VoiceBank 读取音源库的文本文件时的文本编码是否由程序自动推断
      \see setDefalutTextCodecAutoDetect(bool value)
      \see isTextCodecAutoDetect() const
    */
    return DefalutIsTextCodecAutoDetect;
}

void VoiceBank::setDefalutTextCodecAutoDetect(bool value)
{
    ///设置默认情况下 VoiceBank 读取音源库的文本文件时的文本编码是否由程序自动推断
    /*!
      该项设置保存于 QSettings 中。
      \param value VoiceBank 读取音源库的文本文件时的文本编码是否由程序自动推断
      \see isDefalutTextCodecAutoDetect()
    */
    DefalutIsTextCodecAutoDetect = value;
    QSettings settings;
    settings.setValue("DefaultTextCodec/AutoDetect",DefalutIsTextCodecAutoDetect);
    LeafLogger::LogMessage(QString("DefaultTextCodec/AutoDetect被设置为%1").arg(DefalutIsTextCodecAutoDetect));
}

bool VoiceBank::isTextCodecAutoDetect() const
{
    ///返回该音源库的文本编码是否要由程序自动推断
    /*!
      该项设置仅影响文本编码，并且影响所有文本，不影响文件名编码。
      \see setTextCodecAutoDetect(bool value)
    */
    return textCodecAutoDetect;
}

void VoiceBank::setTextCodecAutoDetect(bool value)
{
    ///设置该音源库的文本编码是否要由程序自动推断
    /*!
      该项设置保存于音源库路径下的 leafUTAUQtSettings.json 中。
      \see isTextCodecAutoDetect() const
    */
    textCodecAutoDetect = value;
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
    ///返回默认情况下 VoiceBank 读取该音源库的 wav 文件的文件名时使用的文本编码。
    /*!
      \return 默认情况下 VoiceBank 读取该音源库的 wav 文件的文件名时使用的文本编码
      \see setDefaultWavFileNameCodec(QTextCodec *value)
    */
    return DefaultWavFileNameTextCodec;
}

void VoiceBank::setDefaultWavFileNameTextCodec(QTextCodec *value)
{
    ///更改默认情况下 VoiceBank 读取该音源库的 wav 文件的文件名时使用的文本编码。
    /*!
      该项设置保存于 QSettings 中，默认为 Shift-JIS 。
      \param value 要使用的文本编码。为 nullptr 时的行为是未定义的。
      \see getDefaultCharacterTextCodec()
      \see setDefaultReadmeTextCodec(QTextCodec *value)
    */
    DefaultWavFileNameTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/WavFileName",DefaultReadmeTextCodec->name());
    LeafLogger::LogMessage(QString("DefaultWavFileNameNameTextCodec被设置为%1").arg(QString::fromUtf8(DefaultReadmeTextCodec->name())));
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
        //decodeWavFileName();
    }
}

QTextCodec *VoiceBank::getWavFileNameTextCodec() const
{
    ///返回 VoiceBank 读取该音源库的 wav 文件的文件名时使用的文本编码。
    /*!
      \return VoiceBank 读取该音源库的 wav 文件的文件名时使用的 QTextCodec *
      \see setWavFileNameTextCodec(QTextCodec *value)
    */
    return wavFileNameTextCodec;
}

void VoiceBank::setWavFileNameTextCodec(QTextCodec *value)
{
    ///更改 VoiceBank 读取该音源库的 wav 文件的文件名时使用的文本编码。
    /*!
      该项设置保存于音源库路径下的 leafUTAUQtSettings.json 中。
      \param value 要使用的文本编码。为 nullptr 时将设置为默认编码。
      \see getWavFileNameTextCodec() const
    */
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
            setTextCodecFollowDefault(value.toBool());
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
        textCodecAutoDetect = value.toBool(true);
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
                if ((!textCodecFollowDefault && textCodecAutoDetect) || (textCodecFollowDefault && DefalutIsTextCodecAutoDetect))
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
    ///让 VoiceBank 将声库的特定设置保存到 leafUTAUQtSettings.json 中
    /*!
      VoiceBank 使用声库文件夹下的 leafUTAUQtSettings.json 保存一系列与 UTAU 本体不兼容的额外设定。
      该函数默认会由 VoiceBank 的析构函数调用，您也可以在需要时调用本函数（如改变设置后的重载前）。
    */
    LeafLogger::LogMessage(QString("开始保存%1的声库单独设置。").arg(path));
    QJsonObject json;
    //保存文本编码设置：
    if (textCodecFollowDefault)
        json.insert("TextCodec/FollowDefault",true);
    else
    {
        json.insert("TextCodec/FollowDefault",false);
        json.insert("TextCodec/AutoDetect",textCodecAutoDetect);
        json.insert("TextCodec/CharacterFile",QString::fromUtf8(CharacterTextCodec->name()));
        json.insert("TextCodec/ReadmeFile",QString::fromUtf8(ReadmeTextCodec->name()));
        json.insert("TextCodec/WavFileName",QString::fromUtf8(wavFileNameTextCodec->name()));
    }
    //保存分类：
    if (!category.isEmpty())
        json.insert("Category",category);
    //保存标签：
    if (!labels.isEmpty()){
        QJsonArray array;
        for (auto i : labels)
        {
            array.append(i);
        }
        json.insert("Labels",array);
    }
    //写入json：
    QJsonDocument json_doc(json);
    auto json_file = new QFile(path + "leafUTAUQtSettings.json");
    json_file->open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream json_writer(json_file);
    json_writer.setCodec(QTextCodec::codecForName("UTF-8"));
    json_writer << json_doc.toJson();
    json_file->close();
    json_file->deleteLater();
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



void VoiceBank::clearWavFileReadStage()
{
    wavFileName.clear();
    wavFilePath.clear();
    isWavFileNameReaded = false;
}

void VoiceBank::lazyLoadWavFileName()
{
    if (!isWavFileNameReaded)
        readWavFileName();
}

QStringList VoiceBank::getWavFileName() const
{
    ///获取音源库的 .wav 文件名列表。
    /*!
      这些文件名为操作系统返回的 UTF-8 字符串。\n
    一般说来，非日文区域将会返回一系列乱码，因为 UTAU 本体需要文件名以 Shift-JIS 编码。Leaf Open UTAU 兼容此项限制。\n
    如果您需要以特定编码读取这些字符串以获得正确解码结果，请使用 getWavFileNameRaw() const ，或者手动将其使用 QTextEncoder 编码至本地编码（或其他需要的编码）。\n
    该函数会包含子文件夹中的文件名，但不会包含其子文件夹名称。如果您需要包含子文件夹的文件路径，请使用 getWavFilePath() const 。
    \warning 该函数使用惰性求值（Lazy Evaluation）策略，即 VoiceBank 一开始并不会读取文件名，而是在第一次调用 .wav 文件名获取相关函数时读取。所以在第一次调用相关函数时，请确保 VoiceBank 本身并没有被 const 限定，否则结果将是未定义的。
    \return 操作系统返回的 UTF-8 文件名列表
    \see getWavFileNameRaw() const
    \see getWavFilePath() const
    */
    const_cast<VoiceBank *>(this)->lazyLoadWavFileName();
    return wavFileName;
}

QByteArrayList VoiceBank::getWavFileNameRaw() const
{
    ///获取以本地编码重编码过的文件名列表
    /*!
      这些文件名为以本地编码重解码的 ByteArray。\n
      为方便使用而设。相当于使用 QTextEncoder 以本地编码编码 getWavFileName() const 的返回结果。\n
    \warning 该函数使用惰性求值（Lazy Evaluation）策略，即 VoiceBank 一开始并不会读取文件名，而是在第一次调用 .wav 文件名获取相关函数时读取。所以在第一次相关本函数时，请确保 VoiceBank 本身并没有被 const 限定，否则结果将是未定义的。
    \see getWavFileName() const
    \see getWavFilePath() const
*/
    const_cast<VoiceBank *>(this)->lazyLoadWavFileName();
    QByteArrayList wavFileNameRaw;
    if (!wavFileName.isEmpty())
    {
        QTextEncoder encoder(QTextCodec::codecForLocale());
        for (auto name : wavFileName)
        {
            auto raw = encoder.fromUnicode(name);
            wavFileNameRaw.append(raw);
        }
    }
    return wavFileNameRaw;
}

QStringList VoiceBank::getWavFilePath() const
{
    ///获取音源库下的 .wav 文件路径
    /*!
      您可以使用这些路径去访问这些 .wav 文件。这些文件的名称与 getWavFileName() const 一致。\n
    \warning 该函数使用惰性求值（Lazy Evaluation）策略，即 VoiceBank 一开始并不会读取文件名，而是在第一次调用 .wav 文件名获取相关函数时读取。所以在第一次调用相关函数时，请确保 VoiceBank 本身并没有被 const 限定，否则结果将是未定义的。
    \see getWavFileName() const
    \see getWavFileNameRaw() const
*/
    const_cast<VoiceBank *>(this)->lazyLoadWavFileName();
    return wavFilePath;
}

QTextCodec *VoiceBank::getDefaultReadmeTextCodec()
{
    ///返回默认情况下 VoiceBank 读取音源库的 readme.txt 时使用的文本编码。
    /*!
      \return 默认情况下 VoiceBank 读取音源库的 readme.txt 时使用的文本编码
      \see setDefaultReadmeTextCodec(QTextCodec *value)
      \see getDefaultCharacterTextCodec()
    */
    return DefaultReadmeTextCodec;
}

QTextCodec *VoiceBank::getDefaultCharacterTextCodec()
{
    ///返回默认情况下 VoiceBank 读取音源库的 character.txt 时使用的文本编码。
    /*!
      \return 默认情况下 VoiceBank 读取音源库的 character.txt 时使用的文本编码
      \see setDefaultCharacterTextCodec(QTextCodec *value)
      \see getDefaultReadmeTextCodec()
    */
    return DefaultCharacterTextCodec;
}

void VoiceBank::setDefaultReadmeTextCodec(QTextCodec *value)
{
    ///更改默认情况下 VoiceBank 读取音源库的 readme.txt 时使用的文本编码。
    /*!
      该项设置保存于 QSettings 中，默认为 Shift-JIS 。
      \param value 要使用的文本编码。为 nullptr 时的行为是未定义的。
      \see getDefaultReadmeTextCodec()
      \see setDefaultCharacterTextCodec(QTextCodec *value)
    */
    DefaultReadmeTextCodec = value;
    QSettings settings{};
    settings.setValue("DefaultTextCodec/ReadmeFile",DefaultReadmeTextCodec->name());
    LeafLogger::LogMessage(QString("DefaultReadmeTextCodec被设置为%1").arg(QString::fromUtf8(DefaultReadmeTextCodec->name())));
}

void VoiceBank::setDefaultCharacterTextCodec(QTextCodec *value)
{
    ///更改默认情况下 VoiceBank 读取音源库的 character.txt 时使用的文本编码。
    /*!
      该项设置保存于 QSettings 中，默认为 Shift-JIS 。
      \param value 要使用的文本编码。为 nullptr 时的行为是未定义的。
      \see getDefaultCharacterTextCodec()
      \see setDefaultReadmeTextCodec(QTextCodec *value)
    */
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
        if (!textCodecFollowDefault || (textCodecFollowDefault && DefalutIsTextCodecAutoDetect))
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
        if (!textCodecFollowDefault || (textCodecFollowDefault && DefalutIsTextCodecAutoDetect))
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
        if (!textCodecFollowDefault)
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
        if (!textCodecFollowDefault)
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
        if (!textCodecFollowDefault)
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

bool VoiceBank::isTextCodecFollowDefault() const
{
    ///返回该音源库的文本编码是否跟随默认编码
    /*!
      该项设置同时影响所有文本的相关设置。
      \return 该音源库的文本编码是否跟随默认编码
      \see setTextCodecFollowDefault(bool value)
    */
    return textCodecFollowDefault;
}

void VoiceBank::setTextCodecFollowDefault(bool value)
{
    ///设置该音源库的文本编码是否跟随默认编码
    /*!
      该项设置保存于音源库路径下的 leafUTAUQtSettings.json 中。
      \param value 该音源库的文本编码是否跟随默认编码？
      \see isTextCodecFollowDefault() const
    */
    textCodecFollowDefault = value;
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
    ///从路径中读取 VoiceBank
    /*!
      从路径中读取 VoiceBank 的所需信息。您应当在调用本函数之后再使用 VoiceBank 。 VoiceBank 并不对没有读取就进行操作提出警告。
      \todo 对没有读取过的 VoiceBank 执行操作时的检查。
    */
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




QTextCodec *VoiceBank::getCharacterTextCodec() const
{
    ///返回 VoiceBank 读取该音源库的 character.txt 时使用的文本编码。
    /*!
      该项设置保存于音源库路径下的 leafUTAUQtSettings.json 中。
      \return VoiceBank 读取该音源库的 character.txt 时使用的 QTextCodec *
      \see setCharacterTextCodec(QTextCodec *value)
      \see getReadmeTextCodec() const
    */
    return CharacterTextCodec;
}

void VoiceBank::setCharacterTextCodec(QTextCodec *value)
{
    ///更改 VoiceBank 读取该音源库的 character.txt 时使用的文本编码。
    /*!
      \param value 要使用的文本编码。为 nullptr 时将设置为默认编码。
      \see getCharacterTextCodec() const
    */
    if (value){
        CharacterTextCodec = value;
    }
    else
        CharacterTextCodec = DefaultCharacterTextCodec;
}

QTextCodec *VoiceBank::getReadmeTextCodec() const
{
    ///返回 VoiceBank 读取该音源库的 readme.txt 时使用的文本编码。
    /*!
      \return VoiceBank 读取该音源库的 readme.txt 时使用的 QTextCodec *
      \see setReadmeTextCodec(QTextCodec *value)
      \see getCharacterTextCodec() const
    */
    return ReadmeTextCodec;
}

void VoiceBank::setReadmeTextCodec(QTextCodec *value)
{
    ///更改 VoiceBank 读取该音源库的 readme.txt 时使用的文本编码。
    /*!
      该项设置保存于音源库路径下的 leafUTAUQtSettings.json 中。
      \param value 要使用的文本编码。为 nullptr 时将设置为默认编码。
      \see getReadmeTextCodec() const
    */
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
        return tr("<p style=\"color:red\">错误：找不到character.txt中设定的图片文件（%1）。在音源使用过程中将音源区域将不显示图片。</p>").arg(voiceBank->getImagePath());
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

VoiceBank::ErrorState::ErrorState(VoiceBank *voiceBank){
    if (voiceBank)
        this->voiceBank = voiceBank;
}

VoiceBank::ErrorState::~ErrorState(){}

VoiceBank::FileNotExists::FileNotExists():std::runtime_error("File not exists."){}

VoiceBank::FileCanNotOpen::FileCanNotOpen(const QString QFileError):std::runtime_error("File can not open."),_QFileError(QFileError){}

const QString &VoiceBank::FileCanNotOpen::QFileError() const{return _QFileError;}

VoiceBank::WavFileNameNotLoad::WavFileNameNotLoad():std::runtime_error("The name of .wav files not load."){}
