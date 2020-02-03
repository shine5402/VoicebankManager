#ifndef VOICEBANKCATEGORIESMODEL_H
#define VOICEBANKCATEGORIESMODEL_H

#include <QAbstractListModel>
#include "voicebank.h"
#include "categoriesandlabelslistwidget.h"

class VoicebankCategoryEditorModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VoicebankCategoryEditorModel(Voicebank* voicebank,CategoriesAndLabelsListWidget* totalDataWidget, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    enum customRoles{
        TextRole = Qt::UserRole + 1,
        CheckedRole
    };
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void onCategoriesChanged();
private:
    Voicebank* voicebank = nullptr;
    CategoriesAndLabelsListWidget* totalDataWidget = nullptr;
};

#endif // VOICEBANKCATEGORIESMODEL_H
