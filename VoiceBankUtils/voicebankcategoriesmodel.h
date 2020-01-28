#ifndef VOICEBANKCATEGORIESMODEL_H
#define VOICEBANKCATEGORIESMODEL_H

#include <QAbstractListModel>
#include "voicebank.h"
#include "categoriesandlabelslistwidget.h"

class VoicebankCategoriesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VoicebankCategoriesModel(Voicebank* voicebank,CategoriesAndLabelsListWidget* totalDataWidget, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void onCategoriesChanged();
private:
    Voicebank* voicebank = nullptr;
    CategoriesAndLabelsListWidget* totalDataWidget = nullptr;
};

#endif // VOICEBANKCATEGORIESMODEL_H
