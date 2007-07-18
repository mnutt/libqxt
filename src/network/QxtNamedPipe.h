#ifndef QXTNAMEDPIPE_H
#define QXTNAMEDPIPE_H

#include <QAbstractSocket>
#include <QString>
#include <QByteArray>
#include <qxtpimpl.h>

class QxtNamedPipePrivate;
class QxtNamedPipe : public QAbstractSocket {
Q_OBJECT
public:
    QxtNamedPipe(const QString& name = QString(), QObject* parent = 0);

    bool open(QIODevice::OpenMode mode);
    bool open(const QString& name, QIODevice::OpenMode mode);
    void close();

    QByteArray readAvailableBytes();

private:
    QXT_DECLARE_PRIVATE(QxtNamedPipe);
};

#endif
