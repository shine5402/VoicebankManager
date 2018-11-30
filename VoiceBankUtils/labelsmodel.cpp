#include "labelsmodel.h"
#include "categoriesandlabelslistwidget.h"
LabelsModel::LabelsModel(CategoriesAndLabelsListWidget *parent)
    : QAbstractListModel(parent),dataSource(parent)
{
    connect(parent,SIGNAL(labelsChanged()),this,SLOT(onLabelsChanged()));
}

int LabelsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return dataSource->labels.count();
}

QVariant LabelsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::ItemDataRole::DisplayRole)
        return QString("%1 (%2)").arg(dataSource->labels.at(index.row())).arg(dataSource->labelsUsedCount.value(dataSource->labels.at(index.row())));
    return QVariant();
}

void LabelsModel::onLabelsChanged()
{
    beginResetModel();
    endResetModel();
}
