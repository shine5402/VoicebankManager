#ifndef VOICEBANKTABLEMODEL_H
#define VOICEBANKTABLEMODEL_H
#include <QAbstractTableModel>
#include "voicebankhandler.h"
#include <QIcon>
class VoiceBankTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit VoiceBankTableModel(VoiceBankHandler *parent);
    virtual int columnCount(const QModelIndex & = QModelIndex()) const override{
        return TableColumns::Count;
    }
    virtual int rowCount(const QModelIndex & = QModelIndex()) const override{
//        if (!parent.isValid())
//            return 0;
//        else
            return voicebankHandler->count();
    }
    struct TableColumns
    {
        static constexpr int Count = 2;
        static constexpr int Name = 0;
        static constexpr int Path = 1;
    };
    QVariant data(const QModelIndex &index, int role) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    Qt::ItemFlags flags(const QModelIndex &) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void dataChangedEmitter(VoiceBank *voiceBank);
public slots:
    void newDataEmitter(VoiceBank *voiceBank);
private:
    static int iconSize;
    VoiceBankHandler* voicebankHandler = nullptr;
};

#endif // VOICEBANKTABLEMODEL_H
