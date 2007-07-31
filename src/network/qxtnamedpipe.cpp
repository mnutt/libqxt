#include "qxtnamedpipe.h"
#ifdef Q_OS_UNIX
#    include <fcntl.h>
class QxtNamedPipePrivate : public QxtPrivate<QxtNamedPipe> {
public:
    QxtNamedPipePrivate(){}
    QXT_DECLARE_PUBLIC(QxtNamedPipe);

    QString pipeName;
    int fd;
};

QxtNamedPipe::QxtNamedPipe(const QString& name, QObject* parent) : QAbstractSocket(QAbstractSocket::UnknownSocketType, parent) {
    QXT_INIT_PRIVATE(QxtNamedPipe);
    qxt_d().pipeName = name;
    qxt_d().fd = 0;
}

bool QxtNamedPipe::open(QIODevice::OpenMode mode) 
        {
        int m = O_RDWR;

        if(!(mode & QIODevice::ReadOnly))          ///FIXME: what?
                 m = O_WRONLY;
        else if(!(mode & QIODevice::WriteOnly)) 
                m = O_RDONLY;
        qxt_d().fd = ::open(qPrintable(qxt_d().pipeName), m);

        if(qxt_d().fd != 0) 
                {
                setSocketDescriptor(qxt_d().fd, QAbstractSocket::ConnectedState, mode);
                setOpenMode ( mode);
                return true;
                } 
        else 
                {
                return false;
                }
        }

bool QxtNamedPipe::open(const QString& name, QIODevice::OpenMode mode) {
    qxt_d().pipeName = name;
    return QxtNamedPipe::open(mode);
}

void QxtNamedPipe::close() {
    if(qxt_d().fd) ::close(qxt_d().fd);
   setOpenMode(QIODevice::NotOpen);
}

QByteArray QxtNamedPipe::readAvailableBytes() {
    char ch;
    QByteArray rv;
    while(getChar(&ch)) rv += ch;
    return rv;
}
#else
#    error "No Windows implementation for QxtNamedPipe"
#endif

