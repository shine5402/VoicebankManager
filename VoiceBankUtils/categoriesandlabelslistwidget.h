#ifndef CATEGORIESANDLABELSLISTWIDGET_H
#define CATEGORIESANDLABELSLISTWIDGET_H

#include <QWidget>
#include "voicebankhandler.h"
#include "categoriesmodel.h"
#include "labelsmodel.h"
#include <QMenu>

namespace Ui {
class CategoriesAndLabelsListWidget;
}

class CategoriesAndLabelsListWidget : public QWidget
{
    Q_OBJECT

    friend CategoriesModel;
    friend LabelsModel;

public:
    explicit CategoriesAndLabelsListWidget(VoiceBankHandler *handler,QWidget *parent = nullptr);
    ~CategoriesAndLabelsListWidget() override;
    int getNoCategoriesCount() const;

    int getNoLabelsCount() const;

    QStringList getCategories() const;

    QStringList getLabels() const;

    void addCategory(const QString& category);
    void addLabel(const QString& label);

public slots:
    void removeUnusedCategories();
    void removeUnusedLabels();
    void readCategoriesFromVoicebankHandler();
    void readLabelsFromVoiceBankHandler();

private slots:
    void on_categoriesListView_customContextMenuRequested(const QPoint &);

    void on_labelListView_customContextMenuRequested(const QPoint &);

private:
    Ui::CategoriesAndLabelsListWidget *ui;
    VoiceBankHandler* handler = nullptr;
    QStringList categories;
    QStringList labels;
    void readSettingsCategoriesAndLabels();
    void saveSettingsCategoriesAndLabels();
    QHash<QString,int> categoriesUsedCount;
    QHash<QString,int> labelsUsedCount;
    int noCategoriesCount = 0;
    int noLabelsCount = 0;
    CategoriesModel* categoriesModel = new CategoriesModel(this);
    LabelsModel* labelsModel = new LabelsModel(this);
signals:
    void categoriesChanged();
    void labelsChanged();
};

#endif // CATEGORIESANDLABELSLISTWIDGET_H
