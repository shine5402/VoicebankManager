#ifndef MORESAMPLERCONFIGSADDNEWMODEL_H
#define MORESAMPLERCONFIGSADDNEWMODEL_H

#include <QAbstractTableModel>
#include "moresamplerconfig.h"
#include "moresamplerconfigreader.h"
#include <public_defines.h>
class MoresamplerConfigsAddNewModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MoresamplerConfigsAddNewModel(MoresamplerConfigReader* reader,QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QStringList entryNames;
    MoresamplerConfigReader* reader = nullptr;
};

#endif // MORESAMPLERCONFIGSADDNEWMODEL_H
