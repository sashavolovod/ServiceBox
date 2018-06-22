#ifndef AESQT_H
#define AESQT_H

#include <QString>
#include <QCryptographicHash>

#include "aes.h"

QString encodeText(const QString &rawText, const QString &key);
QString decodeText(QString &hexEncodedText, const QString &key);

#endif // AESQT_H
