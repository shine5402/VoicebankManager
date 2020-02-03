#include "voicebankcategoryeditormodel.h"

VoicebankCategoryEditorModel::VoicebankCategoryEditorModel(Voicebank* voicebank, CategoriesAndLabelsListWidget* totalDataWidget, QObject *parent)
    : QAbstractListModel(parent), voicebank(voicebank), totalDataWidget(totalDataWidget)
{
    connect(totalDataWidget,SIGNAL(categoriesChanged()),this,SLOT(onCategoriesChanged()));
}

int VoicebankCategoryEditorModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid() || !voicebank)
        return 0;
    return totalDataWidget->getCategories().count();
}

QVariant VoicebankCategoryEditorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::ItemDataRole::DisplayRole){
        return totalDataWidget->getCategories().at(index.row());
    }
    if (role == Qt::CheckStateRole)
    {
        if (data(index, Qt::DisplayRole).toString() == voicebank->getCategory())
            return Qt::Checked;
        else {
            return Qt::Unchecked;
        }
    }
    return QVariant();
}

void VoicebankCategoryEditorModel::onCategoriesChanged()
{
    beginResetModel();
    endResetModel();
}

bool VoicebankCategoryEditorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::CheckStateRole)
        {
            if (value.toInt() == Qt::Checked)
                voicebank->setCategory(totalDataWidget->getCategories().at(index.row()));
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags VoicebankCategoryEditorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
