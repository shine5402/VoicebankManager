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
            configs.append(MoresamplerConfig(string));
        }
    }
}

void MoresamplerConfigReader::saveConfigs()
{

}
