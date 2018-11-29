#ifndef CATEGORIESANDLABELSLISTWIDGET_H
#define CATEGORIESANDLABELSLISTWIDGET_H

#include <QWidget>

namespace Ui {
class CategoriesAndLabelsListWidget;
}

class CategoriesAndLabelsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriesAndLabelsListWidget(QWidget *parent = nullptr);
    ~CategoriesAndLabelsListWidget();

private slots:
private:
    Ui::CategoriesAndLabelsListWidget *ui;
};

#endif // CATEGORIESANDLABELSLISTWIDGET_H
