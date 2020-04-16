/****************************************************************************
**
** Copyright (c) 2007 Trolltech ASA <info@trolltech.com>
**
** Use, modification and distribution is allowed without limitation,
** warranty, liability or support of any kind.
**
** ========
** This is a file copied from qBittorrent with my own modification.
**
****************************************************************************/

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
    void resizeEvent(QResizeEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QToolButton *m_iconButton;
};

#endif // LIENEDIT_H
