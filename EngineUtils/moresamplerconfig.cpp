#include "moresamplerconfig.h"

MoresamplerConfig::MoresamplerConfig(QString &configString):configString(configString)
{
    processString();
}

QString MoresamplerConfig::getConfigString() const
{
    return configString;
}

void MoresamplerConfig::setConfigString(const QString &value)
{
    configString = value;
    processString();
}

MoresamplerConfig::ConfigType MoresamplerConfig::getType() const
{
    return type;
}

void MoresamplerConfig::processString()
{
    auto string = configString.trimmed();
    if (string.isEmpty())
        return;
    if (string.at(0) == u8"#")
    {
        decoration.comment = true;
        return;
    }
    if (string.at(0) == u8"*")
    {
        string.remove(0,1);
        decoration.override = true;
    }
    auto splitted = string.split(" ",QString::SplitBehavior::SkipEmptyParts);
    nameString = splitted.at(0);
    type = getTypeByTypeName(nameString);
    valueString = splitted.at(1);
}

MoresamplerConfig::ConfigType MoresamplerConfig::getTypeByTypeName(const QString& name)
{
    auto trimmedName = name.trimmed();
    if (trimmedName == "output-sampling-rate" || trimmedName == "output-bit-depth" || trimmedName == "resampler-compatibility")
        return ConfigType::Output;
    if (trimmedName == "synthesis-utau-style-normalization" || trimmedName == "synthesis-loudness-preservation" || trimmedName == "synthesis-duration-extension-method")
        return ConfigType::Synthesis;
    if (trimmedName == "multithread-synthesis" || trimmedName == "auto-update-llsm-mrq" || trimmedName == "dump-log-file")
        return ConfigType::Misc;
    if (trimmedName == "analysis-f0-range-from-path" || trimmedName == "analysis-biased-f0-estimation" || trimmedName == "analysis-f0-min" || trimmedName == "analysis-f0-max" || trimmedName == "load-frq" || trimmedName == "analysis-anti-distortion" || trimmedName == "analysis-noise-reduction" || trimmedName == "analysis-suppress-subharmonics")
        return ConfigType::Analysis;
    if (trimmedName.startsWith("meta-flag-"))
        return ConfigType::MetaFlag;
    return ConfigType::Unknown;
}

QString MoresamplerConfig::getTypeString(const ConfigType type)
{
    switch (type) {
    case ConfigType::Analysis:
        return QCoreApplication::translate("MoresamplerConfig", u8"合成配置");
    case ConfigType::MetaFlag:
        return QCoreApplication::translate("MoresamplerConfig", u8"元标记");
    case ConfigType::Misc:
        return QCoreApplication::translate("MoresamplerConfig", u8"杂项");
    case ConfigType::Output:
        return QCoreApplication::translate("MoresamplerConfig", u8"输出配置");
    case ConfigType::Synthesis:
        return QCoreApplication::translate("MoresamplerConfig", u8"合成配置");
    case ConfigType::Unknown:
        return QCoreApplication::translate("MoresamplerConfig", u8"未知");
    }
    return QCoreApplication::translate("MoresamplerConfig", u8"未知");
}

QString MoresamplerConfig::getEntryHelp(const QString configName)
{
    return entryHelps.value(configName);
}

QString MoresamplerConfig::getNameString() const
{
    return nameString;
}

QString MoresamplerConfig::getEntryHelp() const
{
    return getEntryHelp(getNameString());
}

QString MoresamplerConfig::getValueString() const
{
    return valueString;
}

void MoresamplerConfig::setValueString(const QString &value)
{
    valueString = value;
}
const QHash<QString,QString> MoresamplerConfig::entryHelps{
    {u8"output-sampling-rate",QT_TRANSLATE_NOOP("", u8"输出的 .wav 文件的采样频率")},
    {u8"output-bit-depth",QT_TRANSLATE_NOOP("", u8"输出的 .wav 文件的位深")},
    {u8"resampler-compatibility",QT_TRANSLATE_NOOP("", u8"开启时, 在resampler模式下生成 .wav 文件 （用于与其他wavtool兼容）。此选项将减慢合成。 ")},
    {u8"synthesis-utau-style-normalization",QT_TRANSLATE_NOOP("", u8"对每个音符应用自适应增益，使得当音量为100％时，合成波形的峰值达到最大幅度的一半。full: 对浊音和清音均进行增益； voiced: 只增益浊音；off: 不改变音量。")},
    {u8"synthesis-loudness-preservation",QT_TRANSLATE_NOOP("", u8"基于心理声学响度测量，在修改后使可感知响度保持。")},
    {u8"synthesis-duration-extension-method",QT_TRANSLATE_NOOP("", u8"决定Moresampler如何使音符时间变长。auto: 根据源时长和目标时长自动决定是使用拉伸方式还是循环方式。可使用 e 和 Me flag 来覆盖这一行为。")},
    {u8"multithread-synthesis",QT_TRANSLATE_NOOP("", u8"on: wavtool模式下的合成将多线程运行（将会更快）。full: resampler模式也将在多线程运行。“多线程”意味着将多个线程包装于一个进程中，与同一时间运行多个Moresampler的“多进程”有着本质不同。注意，该特性不被 moresampler-legacy.exe支持。")},
    {u8"auto-update-llsm-mrq",QT_TRANSLATE_NOOP("", u8"检查.wav 文件与对应.llsm 文件和mrq数据项的最后修改时间。如果.wav文件比.llsm要新，则进行重分析。若.wav文件也比mrq数据项要新，则在重分析以生成.llsm文件前进行音高重估计。此特性或许对声库开发者有帮助。 ")},
    {u8"dump-log-file",QT_TRANSLATE_NOOP("", u8"在指定文件路径中输出Debug信息。")},
    {u8"analysis-f0-range-from-path",QT_TRANSLATE_NOOP("", u8"从文件夹名推测音高。例如，如果给定的样本位于一个名为“C_D4”的文件夹下，Moresampler将在接近D4的范围（294 Hz左右）内进行音高分析。")},
    {u8"analysis-biased-f0-estimation",QT_TRANSLATE_NOOP("", u8"在接合音高与浊音行为估计期间增大浊音化概率，随后进行浊音音高修正；旨在提高特异度和降低灵敏度；适用于嘈杂/粗糙的语音，但会降低干净/流畅语音的质量。 ")},
    {u8"analysis-f0-min",QT_TRANSLATE_NOOP("", u8"音高的下界(以Hz为单位)。")},
    {u8"analysis-f0-max",QT_TRANSLATE_NOOP("", u8"音高的上界(以Hz为单位)。")},
    {u8"load-frq",QT_TRANSLATE_NOOP("", u8"strict : 当desc.mrq不可用时，从.frq 文件读取音高数据。on : 使用 .frq 文件的音高数据来修正Moresampler自己对音高的猜测。不管该选项是否开启，结果都会保存至desc.mrq。注意：除非被仔细修正，.frq文件提供的音高数据通常无法足够可靠地使Moresampler运作。")},
    {u8"analysis-anti-distortion",QT_TRANSLATE_NOOP("", u8"on : Moresampler将自动修复由噪声失真或低音量（量化误差）引起的分析错误。这些错误可能造成音高变换后的“尖锐”与“粗糙”的声音。然而此特性（理论上）可能导致轻微模糊。")},
    {u8"analysis-noise-reduction",QT_TRANSLATE_NOOP("", u8"在从.wav文件分析LLSM时自动降噪。更适用于长录音。")},
    {u8"analysis-suppress-subharmonics",QT_TRANSLATE_NOOP("", u8"在分析时自动移除输入中存在的次谐波。对尖亮的声音可能有帮助，但会导致呼吸音的质量降低。")},
};

MoresamplerConfig::EditMode::IsNotChoicesException::IsNotChoicesException() : std::runtime_error(u8"The value of this config is not a \"Choices\".")
{

}

MoresamplerConfig::EditMode::EditMode(MoresamplerConfig::EditMode::ValueType valueType, QStringList choices) : choices(choices),valueType(valueType)
{

}
