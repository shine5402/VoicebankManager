#ifndef FITCONTENTLISTVIEW_H
#define FITCONTENTLISTVIEW_H
//Some code are from qBittorrent.
#include <QListView>

class FitContentListView : public QListView
{
public:
    FitContentListView(QWidget* parent = nullptr);
    QSize sizeHint() const override;
private slots:
    void callUpdateGeometry();
};

#endif // FITCONTENTLISTVIEW_H
