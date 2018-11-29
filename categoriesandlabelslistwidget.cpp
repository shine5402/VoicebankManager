#include "categoriesandlabelslistwidget.h"
#include "ui_categoriesandlabelslistwidget.h"

CategoriesAndLabelsListWidget::CategoriesAndLabelsListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoriesAndLabelsListWidget)
{
    ui->setupUi(this);
}

CategoriesAndLabelsListWidget::~CategoriesAndLabelsListWidget()
{
    delete ui;
}
