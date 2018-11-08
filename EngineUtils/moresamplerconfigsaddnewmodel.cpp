#include "moresamplerconfigsaddnewmodel.h"

MoresamplerConfigsAddNewModel::MoresamplerConfigsAddNewModel(MoresamplerConfigReader *reader, QObject *parent)
    : QAbstractTableModel(parent),reader(reader)
{
    entryNames.append({tr("（空行）"),tr("（注释）")});
    if (reader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
        entryNames.append(tr("（元标记）"));
    auto allEntryNames = MoresamplerConfig::getAllEntrysName();
    for (auto name : allEntryNames)
    {
        if (reader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
        {
            if (!reader->contains(name))
                entryNames.append(name);
        }
        else
            if (!reader->contains(name) && (MoresamplerConfig::getType(name) == MoresamplerConfig::ConfigType::Analysis || MoresamplerConfig::getType(name) == MoresamplerConfig::ConfigType::Synthesis))
                entryNames.append(name);
    }
}

QVariant MoresamplerConfigsAddNewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal){
            switch (section) {
            case 0:
                return tr("设置项");
            case 1:
                return tr("类型");
            case 2:
                return tr("说明");
            default:
                return QVariant();
            }
        }
        else
        {
            return QString("%1").arg(section + 1);
        }
    }
    else
        return QVariant();
}

int MoresamplerConfigsAddNewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return entryNames.count();
}

int MoresamplerConfigsAddNewModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 3;
}

QVariant MoresamplerConfigsAddNewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ItemDataRole::DisplayRole){
        if (index.column() == 0)
            return entryNames.at(index.row());
        else if (index.column() == 1)
        {
            if (entryNames.at(index.row()) == tr("（空行）") || entryNames.at(index.row()) == tr("（注释）"))
                return entryNames.at(index.row());
            if (entryNames.at(index.row()) == tr("（元标记）"))
                return tr("元标记");
            return MoresamplerConfig::getTypeString(entryNames.at(index.row()));
        }
        else if (index.column() == 2){
            return MoresamplerConfig::getEntryHelp(entryNames.value(index.row()));
        }

    }
    return QVariant();
}
