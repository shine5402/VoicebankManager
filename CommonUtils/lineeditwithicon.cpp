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
    iconButton = new QToolButton(this);
    iconButton->setCursor(Qt::ArrowCursor);
    iconButton->setStyleSheet("QToolButton {border: none; padding: 2px;}");

    // 让文字的左边距包含iconButton的宽度
    setStyleSheet(QString("QLineEdit {padding-left: %1px;}").arg(iconButton->sizeHint().width()));

    setClearButtonEnabled(true);

    auto frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setMaximumHeight(std::max(sizeHint().height(), iconButton->sizeHint().height()) + frameWidth * 2);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

LineEditWithIcon::LineEditWithIcon(const QIcon& icon, QWidget* parent) : LineEditWithIcon(parent)
{
    iconButton->setIcon(icon);
}

void LineEditWithIcon::setIcon(const QIcon& icon)
{
    iconButton->setIcon(icon);
}

void LineEditWithIcon::resizeEvent(QResizeEvent *event)
{
    //垂直居中iconButton
    auto frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    auto x = QGuiApplication::isLeftToRight() ? frameWidth : (event->size().width() - iconButton->sizeHint().width() - frameWidth);
    iconButton->move(x, (event->size().height() - iconButton->sizeHint().height()) / 2);
}

void LineEditWithIcon::keyPressEvent(QKeyEvent *event)
{
    //按Esc键时清除内容
    if ((event->modifiers() == Qt::NoModifier) && (event->key() == Qt::Key_Escape)) {
        clear();
    }

    QLineEdit::keyPressEvent(event);
}
