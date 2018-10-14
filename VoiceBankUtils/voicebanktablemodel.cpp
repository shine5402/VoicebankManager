#include "voicebanktablemodel.h"
int VoiceBankTableModel::iconSize = 20;
VoiceBankTableModel::VoiceBankTableModel(VoiceBankHandler *parent) : QAbstractTableModel (parent),voicebankHandler(parent)
{
    connect(parent,SIGNAL(aVoiceBankReadDone(VoiceBank*)),this,SLOT(newDataEmitter(VoiceBank*)));
}
void VoiceBankTableModel::newDataEmitter(VoiceBank* voiceBank){
    if (voiceBank->isFirstRead())
    {
        beginInsertRows(QModelIndex(),voicebankHandler->getVoiceBankID(voiceBank),voicebankHandler->getVoiceBankID(voiceBank));
        endInsertRows();
    }
}
void VoiceBankTableModel::dataChangedEmitter(VoiceBank* voiceBank){
    emit dataChanged(index(voicebankHandler->getVoiceBankID(voiceBank),TableColumns::Name),index(voicebankHandler->getVoiceBankID(voiceBank),TableColumns::Path));
}

void VoiceBankTableModel::clearEmitter()
{
    if (rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        endRemoveRows();
    }
}
QVariant VoiceBankTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() > voicebankHandler->count())
        return QVariant();
    if (role == Qt::DisplayRole){
        auto voiceBank = voicebankHandler->getVoiceBank(index.row());
        if (voiceBank)
        {
            if (index.column() == TableColumns::Name)
                return voiceBank->getName();
            else if (index.column() == TableColumns::Path)
                return voiceBank->getPath();
            else
                return QVariant();
        }
        else
            return QVariant();
    }
    else if (role == Qt::DecorationRole && index.column() == TableColumns::Name){
        auto voiceBank = voicebankHandler->getVoiceBank(index.row());
        if (voiceBank)
            return QPixmap::fromImage(voicebankHandler->getVoiceBank(index.row())->getImage().scaled(iconSize,iconSize));
        else
            return QVariant();
    }
    else
        return QVariant();
}

void VoiceBankTableModel::sort(int column, Qt::SortOrder order)
{
    switch (column) {
    case TableColumns::Name:
        voicebankHandler->sort(VoiceBankHandler::SortableInformationID::Name,order);
        emit dataChanged(index(0,0),index(rowCount(),columnCount()));
        break;
    case TableColumns::Path:
        voicebankHandler->sort(VoiceBankHandler::SortableInformationID::Path,order);
        emit dataChanged(index(0,0),index(rowCount(),columnCount()));
        break;
    default:
        break;
    }
}

Qt::ItemFlags VoiceBankTableModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

QVariant VoiceBankTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal){
            if (section == TableColumns::Name)
                return tr(u8"音源名称");
            else if (section == TableColumns::Path)
                return tr(u8"音源路径");
            else
                return QVariant();
        }
        else
        {
            return QString("%1").arg(section + 1);
        }
    }
    else
        return QVariant();
}
