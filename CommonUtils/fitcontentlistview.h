#ifndef FITCONTENTLISTVIEW_H
#define FITCONTENTLISTVIEW_H
//Some code are from QBittorrent.
#include <QListView>

class FitContentListView : public QListView
{
public:
    FitContentListView(QWidget* parent = nullptr);
    QSize sizeHint() const override;
};

#endif // FITCONTENTLISTVIEW_H
