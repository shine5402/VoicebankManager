﻿#ifndef MORESAMPLERCONFIGREADER_H
#define MORESAMPLERCONFIGREADER_H

#include <QObject>
#include "moresamplerconfig.h"
#include <QFile>
class MoresamplerConfigReader : public QObject
{
    Q_OBJECT
public:
    enum ConfigFileType{
        Global,VoiceBank
    };
    explicit MoresamplerConfigReader(const QString& configFilePath, const ConfigFileType configFileType,QObject *parent = nullptr);
    void readConfigs();
    int getCount() const{
        return configs.count();
    }
signals:

public slots:
private:
    QString path;
    ConfigFileType configFileType;
    QList<MoresamplerConfig> configs;
};

#endif // MORESAMPLERCONFIGREADER_H
