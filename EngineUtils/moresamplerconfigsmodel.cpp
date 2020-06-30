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
                    return tr("设置项");
                case TableColumnsGlobal::Value:
                    return tr("值");
                case TableColumnsGlobal::Type:
                    return tr("分类");
                case TableColumnsGlobal::Override:
                    return tr("是否覆盖声库配置");
                case TableColumnsGlobal::Help:
                    return tr("说明");
                default:
                    return QVariant();
                }
            else
                switch (section) {
                //改变此处时注意更改ColumnCount
                case TableColumnsVoicebank::Name:
                    return tr("设置项");
                case TableColumnsVoicebank::Value:
                    return tr("值");
                case TableColumnsVoicebank::Type:
                    return tr("分类");
                case TableColumnsVoicebank::Help:
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


QVariant MoresamplerConfigsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ItemDataRole::DisplayRole) {
        if (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global)
            switch (index.column())
            {
            case TableColumnsGlobal::Name:
                // return tr("设置项");
                return configReader->getConfig(index.row())->getNameString();
            case TableColumnsGlobal::Value:
                //return tr("值");
                return configReader->getConfig(index.row())->getValueString();
            case TableColumnsGlobal::Type:
                //return tr("分类");
                return configReader->getConfig(index.row())->getTypeString();
            case TableColumnsGlobal::Override:
                //return tr("是否覆盖声库配置");
                if (isEditableOverrideColumn(index))
                    return configReader->getConfig(index.row())->isOverride()?tr("是"):tr("否");
                else
                    return tr("（不支持）");
            case TableColumnsGlobal::Help:
                //return tr("说明");
                return configReader->getConfig(index.row())->getEntryHelp();
            default:
                return QVariant();
            }
        else
            switch (index.column())
            {
            case TableColumnsVoicebank::Name:
                // return tr("设置项");
                return configReader->getConfig(index.row())->getNameString();
            case TableColumnsVoicebank::Value:
                //return tr("值");
                return configReader->getConfig(index.row())->getValueString();
            case TableColumnsVoicebank::Type:
                //return tr("分类");
                return configReader->getConfig(index.row())->getTypeString();
            case TableColumnsVoicebank::Help:
                //return tr("说明");
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
        if(!(configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == MoresamplerConfigsModel::TableColumnsGlobal::Override))
        {
            try {
                configReader->getConfig(index.row())->setValue(value);
            }
            catch (MoresamplerConfig::ValueNotValidException&) {
                emit ValueToSetIsNotValid(index.row(),value);
                return false;
            }
        }
        else
        {
            configReader->getConfig(index.row())->setOverride(value.toString() == tr("是"));
        }
        //
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

bool MoresamplerConfigsModel::isValueColumn(const QModelIndex &index) const{
    return (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::VoiceBank && index.column() == TableColumnsVoicebank::Value) || (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == TableColumnsGlobal::Value);
}
bool MoresamplerConfigsModel::isEditableOverrideColumn(const QModelIndex &index) const{
    return (configReader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == MoresamplerConfigsModel::TableColumnsGlobal::Override && (configReader->getConfig(index.row())->getType() == MoresamplerConfig::Analysis || configReader->getConfig(index.row())->getType() == MoresamplerConfig::Synthesis));
}
Qt::ItemFlags MoresamplerConfigsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if ((configReader->getConfig(index.row())->canEdit()) && (isValueColumn(index) || isEditableOverrideColumn(index)))
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;

    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

void MoresamplerConfigsModel::removeConfig(int id)
{
    beginRemoveRows(QModelIndex(),id,id);
    configReader->removeConfig(id);
    endRemoveRows();
}

void MoresamplerConfigsModel::addConfig(QString name)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    configReader->addConfig(name);
    endInsertRows();
}
