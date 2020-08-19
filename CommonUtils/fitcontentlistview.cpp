#include "fitcontentlistview.h"

FitContentListView::FitContentListView(QWidget* parent):QListView (parent)
{
    }

QSize FitContentListView::sizeHint() const
{
    if (!model())
        return QListView::sizeHint();
    //宽度上和内容的sizeHint一致，高度上和所有内容（单个内容 * 内容数量）的sizeHint一致。考虑到大部分情况下内容的高度是一致的，这样子做应该没啥关系。
    return { sizeHintForColumn(0) , static_cast<int>(sizeHintForRow(0) * (model()->rowCount()))};
}

void FitContentListView::setModel(QAbstractItemModel* model)
{
    //在模型变动时相应大小更改
    if (this->model())
        disconnect(this->model(), &QAbstractItemModel::modelReset, this, &FitContentListView::callUpdateGeometry);
    connect(model, &QAbstractItemModel::modelReset, this, &FitContentListView::callUpdateGeometry);
    QListView::setModel(model);
}

void FitContentListView::callUpdateGeometry()
{
    updateGeometry();
}
