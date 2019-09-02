#ifndef LABELSMODEL_H
#define LABELSMODEL_H

#include <QAbstractListModel>
class CategoriesAndLabelsListWidget;
class LabelsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LabelsModel(CategoriesAndLabelsListWidget *parent);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void onLabelsChanged();
private:
    CategoriesAndLabelsListWidget* dataSource = nullptr;
};

#endif // LABELSMODEL_H
