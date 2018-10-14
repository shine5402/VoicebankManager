#ifndef MORESAMPLERCONFIGSADDNEWMODEL_H
#define MORESAMPLERCONFIGSADDNEWMODEL_H

#include <QAbstractTableModel>
#include "moresamplerconfig.h"

class MoresamplerConfigsAddNewModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MoresamplerConfigsAddNewModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QStringList entryNames;
};

#endif // MORESAMPLERCONFIGSADDNEWMODEL_H
