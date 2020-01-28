#include "voicebanklabelsmodel.h"

VoicebankLabelsModel::VoicebankLabelsModel(Voicebank* voicebank, CategoriesAndLabelsListWidget* totalDataWidget, QObject *parent)
    : QAbstractListModel(parent), voicebank(voicebank), totalDataWidget(totalDataWidget)
{
    connect(totalDataWidget,SIGNAL(labelsChanged()),this,SLOT(onLabelsChanged()));
}

int VoicebankLabelsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return totalDataWidget->getLabels().count();
}

QVariant VoicebankLabelsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::ItemDataRole::DisplayRole)
    {
      return totalDataWidget->getLabels().at(index.row());
    }
    return QVariant();
}

void VoicebankLabelsModel::onLabelsChanged()
{
    beginResetModel();
    endResetModel();
}
