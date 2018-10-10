#ifndef MORESAMPLERCONFIG_H
#define MORESAMPLERCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QHash>
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

    QString getNameString() const;
    QString getEntryHelp() const;
    class EditMode{
    public:
        enum ValueType{Choices,Integer,Float,String};
        EditMode(ValueType valueType,QStringList choices = QStringList());
        class IsNotChoicesException : std::runtime_error{
        public:
            IsNotChoicesException();
        };
        ValueType getValueType() const;
        QStringList getChoices() const;
        virtual ~EditMode();
        virtual bool isValidValue(QVariant value) const = 0;
    private:
        QStringList choices;
        ValueType valueType;
    };

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
    static QString getTypeString(const ConfigType type);
    static QString getEntryHelp(const QString configName);
    QString valueString;
    QString nameString;
    static const QHash<QString,QString> entryHelps;
};

#endif // MORESAMPLERCONFIG_H
