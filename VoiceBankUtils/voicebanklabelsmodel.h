#ifndef VOICEBANKLABELSMODEL_H
#define VOICEBANKLABELSMODEL_H

#include <QAbstractListModel>
#include "voicebank.h"
#include "categoriesandlabelslistwidget.h"

class VoicebankLabelsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VoicebankLabelsModel(Voicebank* voicebank,CategoriesAndLabelsListWidget* totalDataWidget,QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    void onLabelsChanged();
private:
    Voicebank* voicebank = nullptr;
    CategoriesAndLabelsListWidget* totalDataWidget = nullptr;
};

#endif // VOICEBANKLABELSMODEL_H
