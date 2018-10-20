#ifndef MORESAMPLERCONFIG_H
#define MORESAMPLERCONFIG_H

#include <QObject>
#include <QCoreApplication>
#include <QHash>
#include <QVariant>
#include <QStringList>
class MoresamplerConfig
{
public:
    MoresamplerConfig(QString& configString);
    ~MoresamplerConfig();
    enum ConfigType{
        Unknown,Analysis,Synthesis,Output,MetaFlag,Misc,Comment,Blank
    };

    QString getConfigString() const;
    void setConfigString(const QString &value);

    ConfigType getType() const;
    QString getTypeString() const
    {
        return getTypeString(getType());
    }
    static QString getTypeString(QString typeName);
    bool isComment() const{
        return decoration.comment;
    }
    bool isOverride() const{
        return decoration.override;
    }

    QString getValueString() const;
    bool isBlankLine() const{
        return configString.trimmed().isEmpty();
    }

    QString getNameString() const;
    QString getEntryHelp() const;
    class EditMode{
    public:
        enum ValueType{Choices,Integer,Double,String};
        EditMode(ValueType valueType,QStringList choices = QStringList());
        class NotChoicesException : std::runtime_error{
        public:
            NotChoicesException();
        };
        ValueType getValueType() const;
        QStringList getChoices() const;
        virtual ~EditMode();
        virtual bool isValidValue(QVariant value) const = 0;
        virtual QVariant toVariantValueFromString(QString valueString) const = 0;
        virtual QString toStringFromVariantValue(QVariant value) const = 0;
    protected:
        QStringList choices;
        ValueType valueType;
    };
    class DoubleEditMode : public EditMode{
    public:
        DoubleEditMode();
        virtual bool isValidValue(QVariant value) const override;
        virtual QVariant toVariantValueFromString(QString valueString) const override;
        virtual QString toStringFromVariantValue(QVariant value) const override;
    };
    class PositiveDoubleEditMode : public DoubleEditMode{
    public:
        PositiveDoubleEditMode();
        virtual bool isValidValue(QVariant value) const override;
    };
    class IntegerEditMode : public EditMode{
    public:
        IntegerEditMode();
        virtual bool isValidValue(QVariant value) const override;
        virtual QVariant toVariantValueFromString(QString valueString) const override;
        virtual QString toStringFromVariantValue(QVariant value) const override;
    };
    class PositiveIntegerEditMode : public IntegerEditMode{
    public:
        PositiveIntegerEditMode();
        virtual bool isValidValue(QVariant value) const override;
    };
    class StringEditMode : public EditMode{
    public:
        StringEditMode();
        virtual bool isValidValue(QVariant value) const override;
        virtual QVariant toVariantValueFromString(QString valueString) const override;
         virtual QString toStringFromVariantValue(QVariant value) const override;
    };
    class ChoicesEditMode : public EditMode{
    public:
        ChoicesEditMode(QStringList choices);
        virtual bool isValidValue(QVariant value) const override;
        virtual QVariant toVariantValueFromString(QString valueString) const override;
         virtual QString toStringFromVariantValue(QVariant value) const override;
    };
    EditMode* getEditMode();
    QVariant getValue() const;
    void setValue(const QVariant &value);
    class ValueNotValidException : std::runtime_error{
    public:
        ValueNotValidException();
    };
    bool canEdit() const{
        return editMode;
    }
    void setOverride(bool isOverride){
        decoration.override = isOverride;
    }
    static QStringList getAllEntrysName();
    static QString getEntryHelp(const QString& configName);
    bool isMetaFlag() const{
        return type == ConfigType::MetaFlag;
    }
    QString toString() const;
    bool isValidValue() const;
    static ConfigType getType(const QString &configName);
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

    static QString getTypeString(const ConfigType& type);
    static EditMode* getEditMode(const QString& configName);
    QString valueString;
    QVariant value;
    QString nameString;
    static const QHash<QString,QString> entryHelps;
    EditMode* editMode = nullptr;
};

#endif // MORESAMPLERCONFIG_H
