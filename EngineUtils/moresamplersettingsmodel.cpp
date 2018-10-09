#include "moresamplersettingsmodel.h"

MoresamplerSettingsModel::MoresamplerSettingsModel(MoresamplerConfigReader *parent)
    : QAbstractTableModel(parent),configReader(parent)
{
}

QVariant MoresamplerSettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal){
            switch (section) {
            //改变此处时注意更改ColumnCount
            case 0:
                return tr(u8"设置项");
            case 1:
                return tr(u8"值");
            case 2:
                return tr(u8"分类");
            case 3:
                return tr(u8"是否覆盖声库配置");//FIXME: 根据是否为声库配置单独显示
            case 4:
                return tr(u8"注释");
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
    return 5;
}

QVariant MoresamplerSettingsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

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

    return Qt::ItemIsEditable; // FIXME: Implement me!
}
