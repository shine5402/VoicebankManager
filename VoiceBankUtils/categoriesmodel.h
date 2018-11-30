#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H
#include <QAbstractListModel>
class CategoriesAndLabelsListWidget;
class CategoriesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CategoriesModel(CategoriesAndLabelsListWidget *parent);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    void onCategoriesChanged();
private:
    CategoriesAndLabelsListWidget* dataSource;
};

#endif // CATEGORIESMODEL_H
