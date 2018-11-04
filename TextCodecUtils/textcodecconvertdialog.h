#ifndef TEXTCODECCONVERTDIALOG_H
#define TEXTCODECCONVERTDIALOG_H

#include <QDialog>
#include <QTextCodec>
#include <public_defines.h>
#include "availabletextcodecdialog.h"
#include <public_defines.h>
namespace Ui {
    class TextCodecConvertDialog;
}

class TextCodecConvertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextCodecConvertDialog(QWidget *parent = nullptr);
    TextCodecConvertDialog(QString showFileName, QByteArray source,QTextCodec* sourceCodec,QTextCodec* targetCodec,bool isShowSystemDecodePreView = false,QWidget *parent = nullptr);
    ~TextCodecConvertDialog();
    void setSource(QByteArray text,bool shouldReGen = false);
    void setTargetTextCodec(QTextCodec* codec, bool shouldEmit = false);
    void setSourceTextCodec(QTextCodec* codec,bool shouldEmit = false);
    QString getDecodedString(QTextCodec *codec, QByteArray rawData);
    void setShownFileName(QString name);
    QByteArray getEncodedTargetByteArray() const;
    QTextCodec *getSourceCodec() const;
    QTextCodec *getTargetCodec() const;

    void reDecodeAndReEncodeSource();

signals:
    void targetTextCodecModified();
    void sourceTextCodecModified();
    void sourceChanged();
private slots:
    void on_sourceTextCodecComboBox_currentTextChanged(const QString &arg1);

    void on_targetTextCodecComboBox_currentTextChanged(const QString &arg1);
    void reDecodeSource();
    void reEncodeSource();
    void on_availableCodecButton_source_clicked();

    void on_availableCodecButton_target_clicked();

    void on_showSystemTextCodecCheckBox_stateChanged(int);

private:
    Ui::TextCodecConvertDialog *ui;
    QByteArray source;
    QString decodedSourceString;
    QByteArray encodedTargetByteArray;
    QTextCodec* sourceCodec = QTextCodec::codecForName(defaultTextCodecName);
    QTextCodec* targetCodec = QTextCodec::codecForName(defaultTextCodecName);

    QByteArray getEncodedByteArray(QTextCodec *codec, QString rawData);
};

#endif // TEXTCODECCONVERTDIALOG_H
