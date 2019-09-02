#include "categoriesandlabelslistwidget.h"
#include "ui_categoriesandlabelslistwidget.h"
//TODO:标签分类 标签排序
//TODO:标签过多时调整大小

void CategoriesAndLabelsListWidget::resetCurrentAndSelection()
{
    ui->categoriesListView->setCurrentIndex(categoriesModel->index(0,0));
    ui->labelListView->setCurrentIndex(labelsModel->index(0,0));
    ui->categoriesListView->selectionModel()->select(categoriesModel->index(0,0),QItemSelectionModel::SelectCurrent);
    ui->labelListView->selectionModel()->select(labelsModel->index(0,0),QItemSelectionModel::SelectCurrent);
}

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
    QSettings settings;
    selectionStrategy = static_cast<LabelSelectionStrategy>(settings.value("VoiceBankManager/LabelsFilterSelectionStrategy").toInt());
    connect(ui->categoriesListView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this,SLOT(onCategoriesListViewSelectionChangedSignal(const QItemSelection &, const QItemSelection &)));
    connect(ui->labelListView->selectionModel(),SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),this,SLOT(onLabelListViewSelectionChangedSignal(const QItemSelection &, const QItemSelection &)));
    resetCurrentAndSelection();
}

CategoriesAndLabelsListWidget::~CategoriesAndLabelsListWidget()
{
    saveSettingsCategoriesAndLabels();
    QSettings settings;
    settings.setValue("VoiceBankManager/LabelsFilterSelectionStrategy",selectionStrategy);
    delete ui;
}

void CategoriesAndLabelsListWidget::readSettingsCategoriesAndLabels()
{
    QSettings settings;
    if (settings.contains("VoiceBankManager/Categories"))
    {
        auto value = settings.value("VoiceBankManager/Categories");
        categories = value.toStringList();
        for (auto i : categories)
        {
            categoriesUsedCount.insert(i,0);
        }
        emit categoriesChanged();
    }
    if (settings.contains("VoiceBankManager/Labels"))
    {
        auto value = settings.value("VoiceBankManager/Labels");
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
    settings.setValue("VoiceBankManager/Categories",categories);
    settings.setValue("VoiceBankManager/Labels",labels);
}

CategoriesAndLabelsListWidget::LabelSelectionStrategy CategoriesAndLabelsListWidget::getSelectionStrategy() const
{
    return selectionStrategy;
}

void CategoriesAndLabelsListWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
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
    {
        categories.append(category);
        ui->categoriesListView->updateGeometry();
    }
    emit categoriesChanged();
}

void CategoriesAndLabelsListWidget::addLabel(const QString &label)
{
    if (!labels.contains(label))
    {
        labels.append(label);
        ui->labelListView->updateGeometry();
    }
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
    ui->categoriesListView->updateGeometry();
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
    ui->labelListView->updateGeometry();
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

    auto removeUnusedAction = new QAction(tr("清除未使用的标签"),menu);
    menu->setPalette(QGuiApplication::palette());
    connect(removeUnusedAction,SIGNAL(triggered(bool)),this,SLOT(removeUnusedLabels()));
    menu->addAction(removeUnusedAction);

    menu->addSeparator();

    auto multiSelectionStrategyActionGroup = new QActionGroup(this);
    connect(multiSelectionStrategyActionGroup,SIGNAL(triggered(QAction*)),this,SLOT(onMultiSelectionStrategyActionGroupTriggered(QAction*)));

    auto interAction = new QAction(tr("交集"),multiSelectionStrategyActionGroup);
    interAction->setCheckable(true);
    auto unionAction = new QAction(tr("并集"),multiSelectionStrategyActionGroup);
    unionAction->setCheckable(true);

    switch (selectionStrategy) {
    case Intersection:
        interAction->setChecked(true);
        break;
    case Union:
        unionAction->setChecked(true);
    }

    auto multiSelectionStrategyMenu = new QMenu(tr("多选筛选策略"),menu);

    multiSelectionStrategyMenu->addActions(multiSelectionStrategyActionGroup->actions());
    menu->addMenu(multiSelectionStrategyMenu);

    menu->popup(QCursor::pos());
}

void CategoriesAndLabelsListWidget::onMultiSelectionStrategyActionGroupTriggered(QAction* action)
{
    if (action->text() == tr("交集"))
    {
        selectionStrategy = Intersection;
        emit labelSelectionStrategyChanged();
    }
    else if(action->text() == tr("并集"))
    {
        selectionStrategy = Union;
        emit labelSelectionStrategyChanged();
    }
}

void CategoriesAndLabelsListWidget::onCategoriesListViewSelectionChangedSignal(const QItemSelection &, const QItemSelection &)
{
    QStringList currentCategories;
    auto indexes = ui->categoriesListView->selectionModel()->selection().indexes();
    for (auto index : indexes){
        if (index.isValid())
        {
            if (index.row() == 0)
            {
                currentCategories.append("");
            }
            else if (index.row() == 1)
            {
                currentCategories.append(tr("未分类"));
            }
            else
                currentCategories.append(categories.at(index.row() - 2));
        }}
    emit currentCategoriesChanged(currentCategories);
}

void CategoriesAndLabelsListWidget::onLabelListViewSelectionChangedSignal(const QItemSelection &, const QItemSelection &)
{
    QStringList currentLabels;
    auto indexes = ui->labelListView->selectionModel()->selection().indexes();
    for (auto index : indexes)
        if (index.isValid())
        {
            if (index.row() == 0)
            {
                currentLabels.append("");
            }
            else if (index.row() == 1)
            {
                currentLabels.append(tr("无标签"));
            }
            else
                currentLabels.append(labels.at(index.row() - 2));
        }
    emit currentLabelsChanged(currentLabels);
}

void CategoriesAndLabelsListWidget::on_labelCheckBox_stateChanged(int state)
{
    if (state == Qt::CheckState::Unchecked)
    {
        ui->labelListView->selectionModel()->select(labelsModel->index(0),QItemSelectionModel::SelectCurrent);

    }
}

void CategoriesAndLabelsListWidget::on_categoriesCheckBox_stateChanged(int state)
{
    if (state == Qt::CheckState::Unchecked)
    {
        ui->categoriesListView->selectionModel()->select(categoriesModel->index(0),QItemSelectionModel::SelectCurrent);
    }
}
