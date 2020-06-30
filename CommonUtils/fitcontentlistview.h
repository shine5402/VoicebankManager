#ifndef FITCONTENTLISTVIEW_H
#define FITCONTENTLISTVIEW_H
#include <QListView>
// 本类代码的思路参考自qBittorrent

class FitContentListView : public QListView
{
    Q_OBJECT
public:
    FitContentListView(QWidget* parent = nullptr);
    QSize sizeHint() const override;

private slots:
    void callUpdateGeometry();
};

#endif // FITCONTENTLISTVIEW_H
