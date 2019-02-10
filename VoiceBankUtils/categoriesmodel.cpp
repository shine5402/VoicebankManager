#include "categoriesmodel.h"
#include "categoriesandlabelslistwidget.h"
CategoriesModel::CategoriesModel(CategoriesAndLabelsListWidget *parent)
    : QAbstractListModel(parent),dataSource(parent)
{
    connect(parent,SIGNAL(categoriesChanged()),this,SLOT(onCategoriesChanged()));
}

int CategoriesModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return dataSource->categories.count() + 2;
}

QVariant CategoriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ItemDataRole::DisplayRole){
        if (index.row() > 1)
            return QString("%1 (%2)").arg(dataSource->categories.at(index.row() - 2)).arg(dataSource->categoriesUsedCount.value(dataSource->categories.at(index.row() - 2)));
        else if (index.row() == 1)
            return tr("未分类 (%1)").arg(dataSource->getNoCategoriesCount());
        else if (index.row() == 0)
            return tr("全部 (%1)").arg(dataSource->handler->count());
    }
    return QVariant();
}

void CategoriesModel::onCategoriesChanged()
{
    beginResetModel();
    endResetModel();
}
