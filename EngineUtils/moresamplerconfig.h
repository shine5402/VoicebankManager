#ifndef MORESAMPLERCONFIG_H
#define MORESAMPLERCONFIG_H

#include <QObject>
#include <QCoreApplication>
class MoresamplerConfig
{
public:
    MoresamplerConfig(QString& configString);
    enum ConfigType{
        Analysis,Synthesis,Output,MetaFlag,Misc,Unknown
    };

    QString getConfigString() const;
    void setConfigString(const QString &value);

    ConfigType getType() const;
    QString getTypeString() const
    {
        return getTypeString(getType());
    }
    bool isComment() const{
        return decoration.comment;
    }
    bool isOverride() const{
        return decoration.override;
    }
    void setValueString(const QString &value);

    QString getValueString() const;
    bool isBlankLine() const{
        return configString.trimmed().isEmpty();
    }

private:
    struct ConfigDecoration
    {
        bool override = false;
        bool comment = false;
    };
    void processString();
    QString configString;
    ConfigDecoration decoration{};
    ConfigType type{};
    static ConfigType getTypeByTypeName(const QString &name);
    static QString getTypeString(ConfigType type);
    QString valueString;
};

#endif // MORESAMPLERCONFIG_H
