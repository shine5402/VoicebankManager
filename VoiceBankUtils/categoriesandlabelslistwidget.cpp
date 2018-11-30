#include "categoriesandlabelslistwidget.h"
#include "ui_categoriesandlabelslistwidget.h"

CategoriesAndLabelsListWidget::CategoriesAndLabelsListWidget(VoiceBankHandler *handler, QWidget *parent) :
    QWidget(parent),ui(new Ui::CategoriesAndLabelsListWidget),handler(handler)
{
    ui->setupUi(this);
    readSettingsCategoriesAndLabels();
    connect(handler,SIGNAL(categoriesChanged()),this,SLOT(readCategoriesFromVoicebankHandler()));
    connect(handler,SIGNAL(labelsChanged()),this,SLOT(readLabelsFromVoiceBankHandler()));
    ui->categoriesListView->setModel(categoriesModel);
    ui->labelListView->setModel(labelsModel);
    readCategoriesFromVoicebankHandler();
    readLabelsFromVoiceBankHandler();
}

CategoriesAndLabelsListWidget::~CategoriesAndLabelsListWidget()
{
    saveSettingsCategoriesAndLabels();
    delete ui;
}

void CategoriesAndLabelsListWidget::readSettingsCategoriesAndLabels()
{
    QSettings settings;
    if (settings.contains("Categories"))
    {
        auto value = settings.value("Categories");
        categories = value.toStringList();
        emit categoriesChanged();
    }
    if (settings.contains("Labels"))
    {
        auto value = settings.value("Labels");
        labels = value.toStringList();
        emit labelsChanged();
    }
}

void CategoriesAndLabelsListWidget::saveSettingsCategoriesAndLabels()
{
    QSettings settings;
    if (!categories.isEmpty())
    {
        settings.setValue("Categories",categories);
    }
    if (!labels.isEmpty())
    {
        settings.setValue("Labels",labels);
    }
}

void CategoriesAndLabelsListWidget::readCategoriesFromVoicebankHandler()
{
    for (int i = 0;i < handler->count();++i)
    {
        categoriesUsedCount.clear();
        auto category = handler->getVoiceBank(i)->getCategory();
        categoriesUsedCount.insert(category,categoriesUsedCount.value(category,0));
        if (!category.isEmpty() && !categories.contains(category))
            categories.append(category);
    }
    emit categoriesChanged();
}

void CategoriesAndLabelsListWidget::readLabelsFromVoiceBankHandler()
{
    for (int i = 0;i < handler->count();++i)
    {
        labelsUsedCount.clear();
        auto labels_vb = handler->getVoiceBank(i)->getLabels();
        for (auto label : labels_vb)
            labelsUsedCount.insert(label,labelsUsedCount.value(label,0));
        if (!labels_vb.isEmpty())
            labels.append(labels_vb);
    }
    emit labelsChanged();
}

void CategoriesAndLabelsListWidget::removeUnusedCategories()
{
    for (auto i = categoriesUsedCount.begin();i != categoriesUsedCount.end();++i)
    {
        if (i.value() == 0)
        {
            categories.removeOne(i.key());
            categoriesUsedCount.remove(i.key());
        }
    }
    emit categoriesChanged();
}

void CategoriesAndLabelsListWidget::removeUnusedLabels()
{
    for (auto i = labelsUsedCount.begin();i != labelsUsedCount.end();++i)
    {
        if (i.value() == 0)
        {
            labels.removeOne(i.key());
            labelsUsedCount.remove(i.key());
        }
    }
    emit labelsChanged();
}
