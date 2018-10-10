#include "moresamplersettingsmodel.h"

MoresamplerSettingsModel::MoresamplerSettingsModel(MoresamplerConfigReader *parent)
    : QAbstractTableModel(parent),configReader(parent)
{
}

QVariant MoresamplerSettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal){
            if (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
                switch (section) {
                //改变此处时注意更改ColumnCount
                case TableColumnsGlobal::Name:
                    return tr(u8"设置项");
                case TableColumnsGlobal::Value:
                    return tr(u8"值");
                case TableColumnsGlobal::Type:
                    return tr(u8"分类");
                case TableColumnsGlobal::Override:
                    return tr(u8"是否覆盖声库配置");
                case TableColumnsGlobal::Help:
                    return tr(u8"说明");
                default:
                    return QVariant();
                }
            else
                switch (section) {
                //改变此处时注意更改ColumnCount
                case TableColumnsVoicebank::Name:
                    return tr(u8"设置项");
                case TableColumnsVoicebank::Value:
                    return tr(u8"值");
                case TableColumnsVoicebank::Type:
                    return tr(u8"分类");
                case TableColumnsVoicebank::Help:
                    return tr(u8"说明");
                default:
                    return QVariant();
                }
        }
        else
        {
            return QString("%1").arg(section);
        }
    }
    else
        return QVariant();
}



int MoresamplerSettingsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return configReader->getCount();
}

int MoresamplerSettingsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
        return TableColumnsGlobal::Count;
    else
        return TableColumnsVoicebank::Count;
}

QVariant MoresamplerSettingsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ItemDataRole::DisplayRole) {
        if (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
            switch (index.column())
            {
            case TableColumnsGlobal::Name:
                // return tr(u8"设置项");
                return configReader->getConfig(index.row())->getNameString();
            case TableColumnsGlobal::Value:
                //return tr(u8"值");
                return configReader->getConfig(index.row())->getValueString();
            case TableColumnsGlobal::Type:
                //return tr(u8"分类");
                return configReader->getConfig(index.row())->getTypeString();
            case TableColumnsGlobal::Override:
                //return tr(u8"是否覆盖声库配置");
                return configReader->getConfig(index.row())->isOverride()?u8"是":u8"否";
            case TableColumnsGlobal::Help:
                //return tr(u8"说明");
                return QVariant();//FIXME: 在此处放置说明
            default:
                return QVariant();
            }
        else
            switch (index.column())
            {
            case TableColumnsVoicebank::Name:
                // return tr(u8"设置项");
                return configReader->getConfig(index.row())->getNameString();
            case TableColumnsVoicebank::Value:
                //return tr(u8"值");
                return configReader->getConfig(index.row())->getValueString();
            case TableColumnsVoicebank::Type:
                //return tr(u8"分类");
                return configReader->getConfig(index.row())->getTypeString();
            case TableColumnsVoicebank::Help:
                //return tr(u8"说明");
                return configReader->getConfig(index.row())->getEntryHelp();
            default:
                return QVariant();
            }
    }
    // FIXME: Implement me!
    return QVariant();
}

bool MoresamplerSettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags MoresamplerSettingsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    if ((configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == TableColumnsGlobal::Value) || (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::VoiceBank && index.column() == TableColumnsVoicebank::Value))
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}
