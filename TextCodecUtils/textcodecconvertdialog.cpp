#include "textcodecconvertdialog.h"
#include "ui_textcodecconvertdialog.h"

TextCodecConvertDialog::TextCodecConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextCodecConvertDialog)
{
    ui->setupUi(this);
}

TextCodecConvertDialog::TextCodecConvertDialog(QString shownFileName, QByteArray source, QTextCodec *sourceCodec, QTextCodec *targetCodec, bool isShowSystemDecodePreView, QWidget *parent) :TextCodecConvertDialog(parent)
{
    setShownFileName(shownFileName);
    setSourceTextCodec(sourceCodec);
    setSource(source);
    setTargetTextCodec(targetCodec);
    reDecodeAndReEncodeSource();
    ui->showSystemTextCodecCheckBox->setChecked(isShowSystemDecodePreView);
}

TextCodecConvertDialog::~TextCodecConvertDialog()
{
    delete ui;
}

void TextCodecConvertDialog::reDecodeAndReEncodeSource()
{
    reDecodeSource();
    reEncodeSource();
}

void TextCodecConvertDialog::setSource(QByteArray text, bool shouldReGen)
{
    source = text;
    if (shouldReGen)
        reDecodeAndReEncodeSource();
}
void TextCodecConvertDialog::setTargetTextCodec(QTextCodec *codec,bool shouldEmit)
{
    if (codec)
    {
        ui->targetTextCodecComboBox->setCurrentText(codec->name());
        targetCodec = codec;
    }
    if (shouldEmit)
        emit targetTextCodecModified();
}

void TextCodecConvertDialog::setSourceTextCodec(QTextCodec *codec,bool shouldEmit)
{
    if (codec)
    {
        ui->sourceTextCodecComboBox->setCurrentText(codec->name());
        targetCodec = codec;
    }
    if (shouldEmit)
        emit sourceTextCodecModified();
}

void TextCodecConvertDialog::on_sourceTextCodecComboBox_currentTextChanged(const QString &arg1)
{
    auto codec = QTextCodec::codecForName(arg1.toUtf8());
    if (codec){
        sourceCodec = codec;
        reDecodeAndReEncodeSource();
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
    if (!ui->showSystemTextCodecCheckBox->isChecked())
        ui->targetTextBrowser->setText(reDecodeString);
    else
    {
        auto systemDecodeString = getDecodedString(QTextCodec::codecForLocale(), encodedTargetByteArray);
        auto preview = tr("<h4>以%1进行解码的预览：</h4><pre>%2</pre><h4>使用系统编码重解码后的预览</h4><pre>%3</pre>").arg(QString::fromUtf8(targetCodec->name())).arg(reDecodeString).arg(systemDecodeString);
        ui->targetTextBrowser->setText(preview);
    }
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
    setWindowTitle(tr("对%1进行编码转换").arg(name));
}

void TextCodecConvertDialog::on_availableCodecButton_source_clicked()
{
    AvailableTextCodecDialog::onAvailbaleCodecButtonClicked(ui->sourceTextCodecComboBox);
}

void TextCodecConvertDialog::on_availableCodecButton_target_clicked()
{
    AvailableTextCodecDialog::onAvailbaleCodecButtonClicked(ui->targetTextCodecComboBox);
}

void TextCodecConvertDialog::on_showSystemTextCodecCheckBox_stateChanged(int)
{
    reEncodeSource();
}
