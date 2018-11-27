#ifndef QCHARDET_H
#define QCHARDET_H

#include <QObject>
#include <QTextCodec>
#include "public_defines.h"

class QChardet
{
public:
    //explicit QChardet(QObject *parent = nullptr);
    static QTextCodec *encodingForByteArray(QByteArray string, float *confidence = nullptr);
};

#endif // QCHARDET_H
