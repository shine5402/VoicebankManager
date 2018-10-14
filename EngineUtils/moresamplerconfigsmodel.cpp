#include "moresamplerconfigsmodel.h"

MoresamplerConfigsModel::MoresamplerConfigsModel(MoresamplerConfigReader *parent)
    : QAbstractTableModel(parent),configReader(parent)
{
}

QVariant MoresamplerConfigsModel::headerData(int section, Qt::Orientation orientation, int role) const
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



int MoresamplerConfigsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return configReader->getCount();
}

int MoresamplerConfigsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
        return TableColumnsGlobal::Count;
    else
        return TableColumnsVoicebank::Count;
}

QVariant MoresamplerConfigsModel::data(const QModelIndex &index, int role) const
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
                if (!(configReader->getConfig(index.row())->isComment() || configReader->getConfig(index.row())->isBlankLine()))
                    return configReader->getConfig(index.row())->isOverride()?tr(u8"是"):tr(u8"否");
                else
                    return tr(u8"（不支持）");
            case TableColumnsGlobal::Help:
                //return tr(u8"说明");
                return configReader->getConfig(index.row())->getEntryHelp();
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
    if (role == Qt::ItemDataRole::EditRole)
    {
        return configReader->getConfig(index.row())->getValue();
    }
    return QVariant();
}

bool MoresamplerConfigsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        //FIXME:
        if(!(configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == MoresamplerConfigsModel::TableColumnsGlobal::Override))
        {
            try {
                configReader->getConfig(index.row())->setValue(value);
            }
            catch (MoresamplerConfig::ValueNotValidException&) {
                emit ValueToSetIsNotValid();
                return false;
            }
        }
        else
        {
            configReader->getConfig(index.row())->setOverride(value.toString() == tr(u8"是"));
        }
        //
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags MoresamplerConfigsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    if ((configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == TableColumnsGlobal::Value) || ((configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::VoiceBank && index.column() == TableColumnsVoicebank::Value) && (configReader->getConfig(index.row())->getType() != MoresamplerConfig::ConfigType::Blank)) || (configReader->getConfig(index.row())->canEdit() && !configReader->getConfig(index.row())->isComment() && configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == MoresamplerConfigsModel::TableColumnsGlobal::Override))
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

void MoresamplerConfigsModel::removeConfig(int id)
{
    beginRemoveRows(QModelIndex(),id,id);
    configReader->removeConfig(id);
    endRemoveRows();
}
