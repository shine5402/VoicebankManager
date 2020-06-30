//以下文件参考了qBittorrent的相关代码，而参考来源还带有“Copyright (c) 2007 Trolltech ASA <info@trolltech.com>”的声明。

#ifndef LINEEDITWITHICON_H
#define LINEEDITWITHICON_H

#include <QLineEdit>
#include <QIcon>

class QToolButton;

class LineEditWithIcon : public QLineEdit
{
    Q_OBJECT

public:
    LineEditWithIcon(QWidget *parent = nullptr);
    LineEditWithIcon(const QIcon& icon, QWidget *parent = nullptr);
    void setIcon(const QIcon& icon);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QToolButton *iconButton;
};

#endif // LIENEDIT_H
