#ifndef VOICEBANKTABLEMODEL_H
#define VOICEBANKTABLEMODEL_H
#include <QAbstractTableModel>
#include "voicebankhandler.h"
#include <QIcon>
#include <public_defines.h>
class VoicebankTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit VoicebankTableModel(VoicebankHandler *parent);
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        if (parent.isValid())
            return 0;
        return TableColumns::Count;
    }
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override{
        if (parent.isValid())
            return 0;
        else
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
    void clearEmitter();
signals:
    void sortDone();
public slots:
    void newDataEmitter(Voicebank *voiceBank);
    void dataChangedEmitter(Voicebank *voiceBank);
private:
    static int iconSize;
    VoicebankHandler* voicebankHandler = nullptr;
};

#endif // VOICEBANKTABLEMODEL_H
