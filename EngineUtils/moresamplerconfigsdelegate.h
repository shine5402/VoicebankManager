#ifndef MORESAMPLERCONFIGSDELEGATE_H
#define MORESAMPLERCONFIGSDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QItemEditorFactory>
class MoresamplerConfigsDelegate : public QStyledItemDelegate
{
public:
    explicit MoresamplerConfigsDelegate(QObject *parent = nullptr);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MORESAMPLERCONFIGSDELEGATE_H
