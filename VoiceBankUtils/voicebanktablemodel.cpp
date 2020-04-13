#include "voicebanktablemodel.h"
int VoicebankTableModel::iconSize = 20;
VoicebankTableModel::VoicebankTableModel(VoicebankHandler *parent) : QAbstractTableModel (parent),voicebankHandler(parent)
{
    connect(parent,SIGNAL(aVoiceBankFirstReadDone(Voicebank*)),this,SLOT(newDataEmitter(Voicebank*)));
    connect(parent,SIGNAL(aVoiceBankReloadDone(Voicebank *)),this,SLOT(dataChangedEmitter(Voicebank*)));
}
void VoicebankTableModel::newDataEmitter(Voicebank* voiceBank){
        beginInsertRows(QModelIndex(),voicebankHandler->getVoiceBankID(voiceBank),voicebankHandler->getVoiceBankID(voiceBank));
        endInsertRows();
}
void VoicebankTableModel::dataChangedEmitter(Voicebank* voiceBank){
    emit dataChanged(index(voicebankHandler->getVoiceBankID(voiceBank),TableColumns::Name),index(voicebankHandler->getVoiceBankID(voiceBank),TableColumns::Path));
}

void VoicebankTableModel::clearEmitter()
{
    if (rowCount() > 0)
    {
        beginRemoveRows(QModelIndex(),0,rowCount()-1);
        endRemoveRows();
    }
}
QVariant VoicebankTableModel::data(const QModelIndex &index, int role) const
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
                return voiceBank->getName().isEmpty()?tr("（%1）").arg(QFileInfo(voiceBank->getPath()).dir().dirName()):voiceBank->getName();
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

void VoicebankTableModel::sort(int column, Qt::SortOrder order)
{
    switch (column) {
    case TableColumns::Name:
        voicebankHandler->sort(VoicebankHandler::SortableInformationID::Name,order);
        emit dataChanged(index(0,0),index(rowCount(),columnCount()));
        emit sortDone();
        break;
    case TableColumns::Path:
        voicebankHandler->sort(VoicebankHandler::SortableInformationID::Path,order);
        emit dataChanged(index(0,0),index(rowCount(),columnCount()));
        emit sortDone();
        break;
    default:
        break;
    }
}

Qt::ItemFlags VoicebankTableModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

QVariant VoicebankTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::ItemDataRole::DisplayRole){
        if (orientation == Qt::Orientation::Horizontal){
            if (section == TableColumns::Name)
                return tr("音源名称");
            else if (section == TableColumns::Path)
                return tr("音源路径");
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
