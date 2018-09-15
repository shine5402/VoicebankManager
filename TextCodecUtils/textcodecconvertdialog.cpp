#include "textcodecconvertdialog.h"
#include "ui_textcodecconvertdialog.h"

TextCodecConvertDialog::TextCodecConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextCodecConvertDialog)
{
    ui->setupUi(this);
    connect(this,SIGNAL(sourceChanged()),this,SLOT(sourceChangedSlot()));
    connect(this,SIGNAL(sourceTextCodecModified()),this,SLOT(reDecodeSource()));
    connect(this,SIGNAL(targetTextCodecModified()),this,SLOT(reEncodeSource()));
}

TextCodecConvertDialog::~TextCodecConvertDialog()
{
    delete ui;
}

void TextCodecConvertDialog::setSource(QByteArray text)
{
    source = text;
    reDecodeSource();
    reEncodeSource();
}
void TextCodecConvertDialog::setTargetTextCodec(QTextCodec *codec)
{
    if (codec)
    {
        ui->targetTextCodecComboBox->setCurrentText(codec->name());
        sourceCodec = codec;
    }
    emit targetTextCodecModified();
}

void TextCodecConvertDialog::setSourceTextCodec(QTextCodec *codec)
{
    if (codec)
    {
        ui->sourceTextCodecComboBox->setCurrentText(codec->name());
        targetCodec = codec;
    }
    emit sourceTextCodecModified();
}

void TextCodecConvertDialog::on_sourceTextCodecComboBox_currentTextChanged(const QString &arg1)
{
    auto codec = QTextCodec::codecForName(arg1.toUtf8());
    if (codec){
        sourceCodec = codec;
        reDecodeSource();
    }
}


QString TextCodecConvertDialog::getDecodedString(QTextCodec* codec,QByteArray rawData)
{
    QTextDecoder decoder(codec);
    return decoder.toUnicode(rawData);
}
QByteArray TextCodecConvertDialog::getEncodedByteArray(QTextCodec* codec,QString rawData)
{
    QTextEncoder encoder(codec);
    return encoder.fromUnicode(rawData);
}

void TextCodecConvertDialog::reDecodeSource()
{
    auto sourceCodecByteArray = sourceCodec->name();
    decodedSourceString = getDecodedString(sourceCodec,source);
    ui->sourceTextBrowser->setText(decodedSourceString);
    qApp->processEvents();
}
void TextCodecConvertDialog::reEncodeSource()
{
    encodedTargetByteArray = getEncodedByteArray(targetCodec,decodedSourceString);
    auto reDecodeString = getDecodedString(targetCodec, encodedTargetByteArray);
    ui->targetTextBrowser->setText(reDecodeString);
    qApp->processEvents();
}

void TextCodecConvertDialog::on_targetTextCodecComboBox_currentTextChanged(const QString &arg1)
{
    auto codec = QTextCodec::codecForName(arg1.toUtf8());
    if (codec){
        targetCodec = codec;
        reEncodeSource();
    }
}

QTextCodec *TextCodecConvertDialog::getTargetCodec() const
{
    return targetCodec;
}

QTextCodec *TextCodecConvertDialog::getSourceCodec() const
{
    return sourceCodec;
}

QByteArray TextCodecConvertDialog::getEncodedTargetByteArray() const
{
    return encodedTargetByteArray;
}

void TextCodecConvertDialog::setShownFileName(QString name)
{
    setWindowTitle(tr(u8"对%1进行编码转换").arg(name));
}

void TextCodecConvertDialog::on_availableCodecButton_source_clicked()
{
    AvailableTextCodecDialog::onAvailbaleCodecButtonClicked(ui->sourceTextCodecComboBox);
}

void TextCodecConvertDialog::on_availableCodecButton_target_clicked()
{
    AvailableTextCodecDialog::onAvailbaleCodecButtonClicked(ui->targetTextCodecComboBox);
}
