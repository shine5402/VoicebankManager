#include "voicebanklabelseditormodel.h"

VoicebankLabelsEditorModel::VoicebankLabelsEditorModel(Voicebank* voicebank, CategoriesAndLabelsListWidget* totalDataWidget, QObject *parent)
    : QAbstractListModel(parent), voicebank(voicebank), totalDataWidget(totalDataWidget)
{
    connect(totalDataWidget,SIGNAL(labelsChanged()),this,SLOT(onLabelsChanged()));
}

int VoicebankLabelsEditorModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return totalDataWidget->getLabels().count();
}

QVariant VoicebankLabelsEditorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TextRole)
    {
        return totalDataWidget->getLabels().at(index.row());
    }
    if (role == CheckStateRole)
    {
        if (voicebank->getLabels().contains(data(index, TextRole).toString()))
            return Qt::Checked;
        else {
            return Qt::Unchecked;
        }
    }
    return QVariant();
}

void VoicebankLabelsEditorModel::onLabelsChanged()
{
    beginResetModel();
    endResetModel();
}

bool VoicebankLabelsEditorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (value.toInt() == Qt::Checked)
        {
            voicebank->addLabel(data(index, TextRole).toString());
        }
        if (value.toInt() == Qt::Unchecked)
        {
            voicebank->removeLabel(data(index, TextRole).toString());
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags VoicebankLabelsEditorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

QHash<int, QByteArray> VoicebankLabelsEditorModel::roleNames() const
{
    auto roleNames = QAbstractItemModel::roleNames();
    roleNames.insert(TextRole,"text");
    roleNames.insert(CheckStateRole,"checkState");
    return roleNames;
}
