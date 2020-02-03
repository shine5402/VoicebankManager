#include "voicebankcategorylabeleditdialog.h"
#include "ui_voicebankcategorylabeleditdialog.h"
#include <QQmlEngine>
#include <QQmlContext>

VoicebankCategoryLabelEditDialog::VoicebankCategoryLabelEditDialog(VoicebankCategoryEditorModel* model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoicebankCategoryLabelEditDialog), model(model)
{
    ui->setupUi(this);
    ui->quickWidget->engine()->rootContext()->setContextProperty("dataModel",model);
}

VoicebankCategoryLabelEditDialog::~VoicebankCategoryLabelEditDialog()
{
    delete ui;
}
