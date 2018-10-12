#include "moresamplerconfigsdelegate.h"

MoresamplerConfigsDelegate::MoresamplerConfigsDelegate(QObject *parent) : QStyledItemDelegate (parent)
{

}

QWidget *MoresamplerConfigsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return nullptr;
//FIXME:
}
