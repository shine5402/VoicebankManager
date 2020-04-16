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

#include "lineeditwithicon.h"

#include <algorithm>

#include <QGuiApplication>
#include <QResizeEvent>
#include <QStyle>
#include <QToolButton>

LineEditWithIcon::LineEditWithIcon(QWidget *parent)
    : QLineEdit(parent)
{
    m_iconButton = new QToolButton(this);
    m_iconButton->setCursor(Qt::ArrowCursor);
    m_iconButton->setStyleSheet("QToolButton {border: none; padding: 2px;}");

    // padding between text and widget borders
    setStyleSheet(QString::fromLatin1("QLineEdit {padding-left: %1px;}").arg(m_iconButton->sizeHint().width()));

    setClearButtonEnabled(true);

    const int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setMaximumHeight(std::max(sizeHint().height(), m_iconButton->sizeHint().height()) + frameWidth * 2);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

LineEditWithIcon::LineEditWithIcon(const QIcon& icon, QWidget* parent) : LineEditWithIcon(parent)
{
    m_iconButton->setIcon(icon);
}

void LineEditWithIcon::setIcon(const QIcon& icon)
{
    m_iconButton->setIcon(icon);
}

void LineEditWithIcon::resizeEvent(QResizeEvent *e)
{
    const int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    const int xPos = QGuiApplication::isLeftToRight()
                     ? frameWidth
                     : (e->size().width() - m_iconButton->sizeHint().width() - frameWidth);
    m_iconButton->move(xPos, (e->size().height() - m_iconButton->sizeHint().height()) / 2);
}

void LineEditWithIcon::keyPressEvent(QKeyEvent *event)
{
    if ((event->modifiers() == Qt::NoModifier) && (event->key() == Qt::Key_Escape)) {
        clear();
    }
    QLineEdit::keyPressEvent(event);
}
