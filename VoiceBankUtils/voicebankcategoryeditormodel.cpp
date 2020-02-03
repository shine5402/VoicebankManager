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

    if (role == TextRole){
        return totalDataWidget->getCategories().at(index.row());
    }
    if (role == CheckedRole)
    {
        return data(index, TextRole).toString() == voicebank->getCategory();
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
        if (role == CheckedRole)
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

QHash<int, QByteArray> VoicebankCategoryEditorModel::roleNames() const
{
    auto roleNames = QAbstractItemModel::roleNames();
    roleNames.insert(TextRole,"text");
    roleNames.insert(CheckedRole,"checked");
    return roleNames;
}
