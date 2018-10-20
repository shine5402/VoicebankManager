#include "moresamplerconfigreader.h"

MoresamplerConfigReader::MoresamplerConfigReader(const QString &configFilePath, const ConfigFileType configFileType, QObject *parent) : QObject(parent),path(configFilePath),configFileType(configFileType)
{
    readConfigs();
}

void MoresamplerConfigReader::readConfigs()
{
    auto file = new QFile(path);
    if (file->exists()){
        file->open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text);
        auto fileContent = file->readAll();
        auto fileContentString = QString::fromUtf8(fileContent);
        auto fileContentSingleLine = fileContentString.split("\n");
        for (auto string : fileContentSingleLine)
        {
            configs.append(new MoresamplerConfig(string));
        }
    }
    file->close();
    file->deleteLater();
}

void MoresamplerConfigReader::saveConfigs()
{
    auto file = new QFile(path);
    file->open(QFile::OpenModeFlag::WriteOnly | QFile::OpenModeFlag::Text);
    QString result;
    QTextStream textStream(&result);
    for (auto config : configs)
    {
        textStream << config->toString() << endl;
    }
    result = result.trimmed();
    file->write(result.toUtf8());
    file->close();
    file->deleteLater();
}

MoresamplerConfigReader::~MoresamplerConfigReader()
{
    for (auto i : configs)
    {
        delete i;
    }
}

MoresamplerConfigReader::ConfigFileType MoresamplerConfigReader::getConfigFileType() const
{
    return configFileType;
}

void MoresamplerConfigReader::removeConfig(int id)
{
    configs.removeAt(id);
}

int MoresamplerConfigReader::addConfig(QString &name)
{
    configs.append(new MoresamplerConfig(name));
    return configs.count() - 1;
}

bool MoresamplerConfigReader::contains(QString &name)
{
    for (auto config : configs)
    {
        if (config->getNameString() == name)
            return true;
    }
    return false;
}
