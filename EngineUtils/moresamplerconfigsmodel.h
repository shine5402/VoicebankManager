#ifndef MORESAMPLERCONFIGSMODEL_H
#define MORESAMPLERCONFIGSMODEL_H

#include <QAbstractTableModel>
#include "moresamplerconfigreader.h"
class MoresamplerConfigsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MoresamplerConfigsModel(MoresamplerConfigReader *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    inline int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    inline int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    struct TableColumnsGlobal{
        constexpr static int Count = 5;
        constexpr static int Name = 0;
        constexpr static int Value = 1;
        constexpr static int Type = 2;
        constexpr static int Override = 3;
        constexpr static int Help = 4;
    };
    struct TableColumnsVoicebank{
        constexpr static int Count = 4;
        constexpr static int Name = 0;
        constexpr static int Value = 1;
        constexpr static int Type = 2;
        constexpr static int Help = 3;
    };

private:
    MoresamplerConfigReader* configReader = nullptr;
};

#endif // MORESAMPLERCONFIGSMODEL_H
