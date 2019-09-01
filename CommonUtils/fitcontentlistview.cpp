#include "fitcontentlistview.h"

FitContentListView::FitContentListView(QWidget* parent):QListView (parent)
{

}

QSize FitContentListView::sizeHint() const
{
    if (!model())
        return QListView::sizeHint();
    //These codes are from qBittorrent (under GNU GPL v2).
    return {
        // Width should be exactly the width of the content
        sizeHintForColumn(0),
        // Height should be exactly the height of the content
        static_cast<int>(sizeHintForRow(0) * (model()->rowCount() + 0.5)),
    };
}
