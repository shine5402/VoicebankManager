#ifndef CATEGORIESANDLABELSLISTWIDGET_H
#define CATEGORIESANDLABELSLISTWIDGET_H

#include <QWidget>
#include "voicebankhandler.h"
#include "categoriesmodel.h"
#include "labelsmodel.h"

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
    ~CategoriesAndLabelsListWidget();
public slots:
    void removeUnusedCategories();
    void removeUnusedLabels();
    void readCategoriesFromVoicebankHandler();
    void readLabelsFromVoiceBankHandler();
private slots:
private:
    Ui::CategoriesAndLabelsListWidget *ui;
    VoiceBankHandler* handler = nullptr;
    QStringList categories;
    QStringList labels;
    void readSettingsCategoriesAndLabels();
    void saveSettingsCategoriesAndLabels();
    QHash<QString,int> categoriesUsedCount;
    QHash<QString,int> labelsUsedCount;
    CategoriesModel* categoriesModel = new CategoriesModel(this);
    LabelsModel* labelsModel = new LabelsModel(this);
signals:
    void categoriesChanged();
    void labelsChanged();
};

#endif // CATEGORIESANDLABELSLISTWIDGET_H
