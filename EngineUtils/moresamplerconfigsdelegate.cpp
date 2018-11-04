#include "moresamplerconfigsdelegate.h"

MoresamplerConfigsDelegate::MoresamplerConfigsDelegate(MoresamplerConfigReader *reader, QObject *parent) : QStyledItemDelegate (parent),reader(reader)
{

}

QWidget *MoresamplerConfigsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;
    if (reader->getConfig(index.row())->getEditMode()->getValueType() == MoresamplerConfig::EditMode::ValueType::Choices && ((reader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == MoresamplerConfigsModel::TableColumnsGlobal::Value )|| (reader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::VoiceBank && index.column() == MoresamplerConfigsModel::TableColumnsVoicebank::Value )))
    {
        auto sb = new QComboBox(parent);
        sb->setFrame(false);
        sb->addItems(reader->getConfig(index.row())->getEditMode()->getChoices());
        sb->setCurrentText(reader->getConfig(index.row())->getValueString());
        return sb;
    }
    if (reader->getConfigFileType() == MoresamplerConfigReader::ConfigFileType::Global && index.column() == MoresamplerConfigsModel::TableColumnsGlobal::Override)
    {
        auto sb = new QComboBox(parent);
        sb->setFrame(false);
        sb->addItems({tr("是"),tr("否")});
        sb->setCurrentText(reader->getConfig(index.row())->isOverride()?tr("是"):tr("否"));
        return sb;
    }
        return QStyledItemDelegate::createEditor(parent,option,index);
}
