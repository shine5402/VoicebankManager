#include "moresamplerconfigsaddnewmodel.h"

MoresamplerConfigsAddNewModel::MoresamplerConfigsAddNewModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    entryNames.append({tr(u8"（空行）"),u8"（注释）",u8"（元标记）"});
    entryNames.append(MoresamplerConfig::getAllEntrysName());
}

QVariant MoresamplerConfigsAddNewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal){
            switch (section) {
            case 0:
                return tr(u8"设置项");
            case 1:
                return tr(u8"说明");
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
    return 2;
}

QVariant MoresamplerConfigsAddNewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ItemDataRole::DisplayRole){
        if (index.column() == 0)
            return entryNames.at(index.row());
        else if (index.column() == 1){
            return MoresamplerConfig::getEntryHelp(entryNames.value(index.row()));
        }

    }
    return QVariant();
}
