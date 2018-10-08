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
    type = getTypeByName(string);
    auto splitted = string.split(" ",QString::SplitBehavior::SkipEmptyParts);
    valueString = splitted.at(1);
}

MoresamplerConfig::ConfigType MoresamplerConfig::getTypeByName(const QString& name)
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

QString MoresamplerConfig::getTypeString(MoresamplerConfig::ConfigType type)
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
}

QString MoresamplerConfig::getValueString() const
{
    return valueString;
}

void MoresamplerConfig::setValueString(const QString &value)
{
    valueString = value;
}
