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
    //    auto _palette = palette();
    //    _palette.setColor(QPalette::ColorRole::Window,QColor("white"));
    //    setPalette(_palette);
    //    ui->frame->setPalette(_palette);
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
        for (auto i : categories)
        {
            categoriesUsedCount.insert(i,0);
        }
        emit categoriesChanged();
    }
    if (settings.contains("Labels"))
    {
        auto value = settings.value("Labels");
        labels = value.toStringList();
        for (auto i : labels)
        {
            labelsUsedCount.insert(i,0);
        }
        emit labelsChanged();
    }
}

void CategoriesAndLabelsListWidget::saveSettingsCategoriesAndLabels()
{
    QSettings settings;
    settings.setValue("Categories",categories);
    settings.setValue("Labels",labels);
}

int CategoriesAndLabelsListWidget::getNoLabelsCount() const
{
    return noLabelsCount;
}

int CategoriesAndLabelsListWidget::getNoCategoriesCount() const
{
    return noCategoriesCount;
}

void CategoriesAndLabelsListWidget::readCategoriesFromVoicebankHandler()
{
    //categoriesUsedCount.clear();
    for (auto it = categoriesUsedCount.begin();it != categoriesUsedCount.end();++it)
    {
        it.value() = 0;
    }
    noCategoriesCount = 0;
    for (int i = 0;i < handler->count();++i)
    {
        auto category = handler->getVoiceBank(i)->getCategory();
        if (!category.isEmpty())
            categoriesUsedCount.insert(category,categoriesUsedCount.value(category,0) + 1);
        if (!category.isEmpty() && !categories.contains(category))
            categories.append(category);
        if (category.isEmpty())
            ++noCategoriesCount;
    }
    emit categoriesChanged();
}

void CategoriesAndLabelsListWidget::readLabelsFromVoiceBankHandler()
{
    //labelsUsedCount.clear();
    for (auto it = labelsUsedCount.begin();it != labelsUsedCount.end();++it)
    {
        it.value() = 0;
    }
    noLabelsCount = 0;
    for (int i = 0;i < handler->count();++i)
    {
        auto labels_vb = handler->getVoiceBank(i)->getLabels();
        for (auto label : labels_vb)
            labelsUsedCount.insert(label,labelsUsedCount.value(label,0) + 1);
        if (!labels_vb.isEmpty()){
            for (auto i : labels_vb)
                if (!labels.contains(i))
                    labels.append(i);
        }
        else
            ++noLabelsCount;
    }
    emit labelsChanged();
}


QStringList CategoriesAndLabelsListWidget::getLabels() const
{
    return labels;
}

void CategoriesAndLabelsListWidget::addCategory(const QString &category)
{
    if (!categories.contains(category))
        categories.append(category);
    emit categoriesChanged();
}

void CategoriesAndLabelsListWidget::addLabel(const QString &label)
{
    if (!labels.contains(label))
        labels.append(label);
    emit labelsChanged();
}

QStringList CategoriesAndLabelsListWidget::getCategories() const
{
    return categories;
}

void CategoriesAndLabelsListWidget::removeUnusedCategories()
{
    QStringList toBeRemoved;
    for (auto i = categoriesUsedCount.begin();i != categoriesUsedCount.end();++i)
    {
        if (i.value() == 0)
        {
            categories.removeOne(i.key());
            //categoriesUsedCount.remove(i.key());
            toBeRemoved.append(i.key());
        }
    }
    for (auto i : toBeRemoved)
        categoriesUsedCount.remove(i);
    emit categoriesChanged();
}

void CategoriesAndLabelsListWidget::removeUnusedLabels()
{
    QStringList toBeRemoved;
    for (auto i = labelsUsedCount.begin();i != labelsUsedCount.end();++i)
    {
        if (i.value() == 0)
        {
            labels.removeOne(i.key());
            //labelsUsedCount.remove(i.key());
            toBeRemoved.append(i.key());
        }
    }
    for (auto i : toBeRemoved)
        labelsUsedCount.remove(i);
    emit labelsChanged();
}

void CategoriesAndLabelsListWidget::on_categoriesListView_customContextMenuRequested(const QPoint &)
{
    auto menu = new QMenu(this);
    auto action = new QAction(tr("清除未使用的分类"),menu);
    menu->setPalette(QGuiApplication::palette());
    connect(action,SIGNAL(triggered(bool)),this,SLOT(removeUnusedCategories()));
    menu->addAction(action);
    menu->popup(QCursor::pos());
}

void CategoriesAndLabelsListWidget::on_labelListView_customContextMenuRequested(const QPoint &)
{
    auto menu = new QMenu(this);
    auto action = new QAction(tr("清除未使用的标签"),menu);
    menu->setPalette(QGuiApplication::palette());
    connect(action,SIGNAL(triggered(bool)),this,SLOT(removeUnusedLabels()));
    menu->addAction(action);
    menu->popup(QCursor::pos());
}
