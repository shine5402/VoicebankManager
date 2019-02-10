#include "messagelistwidget.h"
#include "ui_messagelistwidget.h"

MessageListWidget::MessageListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageListWidget)
{
    ui->setupUi(this);
}

MessageListWidget::~MessageListWidget()
{
    delete ui;
}
