#include "aesqt.h"

const uint8_t iv[] = { 0xf0, 0xe1, 0xd2, 0xc3, 0xb4, 0xa5, 0x96,
              0x87, 0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x5e, 0xaf };

inline int getAlignedSize(int currSize, int alignment) {
        int padding = (alignment - currSize % alignment) % alignment;
        return currSize + padding;
}

QString encodeText(const QString &rawText, const QString &key) {
        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(key.toUtf8());
        QByteArray keyData = hash.result();

        const ushort *rawData = rawText.utf16();
        void *rawDataVoid = (void*)rawData;

        const char *rawDataChar = static_cast<const char *>(rawDataVoid);

        QByteArray inputData;
        // ushort is 2*uint8_t + 1 byte for '\0'
        inputData.append(rawDataChar, rawText.size() * 2 + 1);

        const int length = inputData.size();
        int encryptionLength = getAlignedSize(length, 16);

        inputData.resize(encryptionLength);

        struct AES_ctx ctx;
        AES_init_ctx_iv(&ctx, (const uint8_t*)keyData.data(), iv);

        AES_CBC_encrypt_buffer(&ctx, (uint8_t*)inputData.data(), inputData.size());

        QByteArray data(inputData.data(), encryptionLength);
        QString hex = QString::fromLatin1(data.toHex());
        return hex;
    }

QString decodeText(QString &hexEncodedText, const QString &key)
{
        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(key.toUtf8());
        QByteArray keyData = hash.result();

        const int length = hexEncodedText.size();
        int encryptionLength = getAlignedSize(length, 16);

        // QByteArray encodingBuffer(encryptionLength, 0);

        QByteArray encodedText = QByteArray::fromHex(hexEncodedText.toLatin1());
        encodedText.resize(encryptionLength);

        struct AES_ctx ctx;
        AES_init_ctx_iv(&ctx, (const uint8_t*)keyData.data(), iv);
        AES_CBC_decrypt_buffer(&ctx, (uint8_t*)encodedText.data(),encodedText.size());

        encodedText.append("\0\0");
        void *data = encodedText.data();
        const ushort *decodedData = static_cast<const ushort *>(data);
        QString result = QString::fromUtf16(decodedData);
        return result;
}
