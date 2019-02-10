#ifndef MESSAGELISTWIDGET_H
#define MESSAGELISTWIDGET_H

#include <QWidget>

namespace Ui {
    class MessageListWidget;
}

class MessageListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageListWidget(QWidget *parent = nullptr);
    ~MessageListWidget();

private:
    Ui::MessageListWidget *ui;
};

#endif // MESSAGELISTWIDGET_H
