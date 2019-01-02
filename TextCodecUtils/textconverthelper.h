#ifndef TEXTCONVERTHELPER_H
#define TEXTCONVERTHELPER_H

#include <QObject>
#include "textcodecconvertdialog.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QCoreApplication>

class TextConvertHelper
{
public:
    bool static processFileTextCodecConvert(const QString& path, QTextCodec *&sourceCodec, QTextCodec *&targetCodec, QWidget* messageBoxParent);
    bool static processFileNameConvert(const QByteArrayList& _fileNameRaw, const QStringList& _filePaths, const QString& title, QTextCodec *&rawCodec, QTextCodec *&targetCodec, QWidget* messageBoxParent);
private:
    bool static backupFile(QFile *file, QWidget *messageBoxParent);
};

#endif // TEXTCONVERTHELPER_H
