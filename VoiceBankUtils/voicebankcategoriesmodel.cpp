#include "voicebankcategoriesmodel.h"

VoicebankCategoriesModel::VoicebankCategoriesModel(Voicebank* voicebank, CategoriesAndLabelsListWidget* totalDataWidget, QObject *parent)
    : QAbstractListModel(parent), voicebank(voicebank), totalDataWidget(totalDataWidget)
{
     connect(totalDataWidget,SIGNAL(categoriesChanged()),this,SLOT(onCategoriesChanged()));
}

int VoicebankCategoriesModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || !voicebank)
        return 0;
    return totalDataWidget->getCategories().count();
}

QVariant VoicebankCategoriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::ItemDataRole::DisplayRole){
            return totalDataWidget->getCategories().at(index.row());
    }
    return QVariant();
}

void VoicebankCategoriesModel::onCategoriesChanged()
{
    beginResetModel();
    endResetModel();
}

