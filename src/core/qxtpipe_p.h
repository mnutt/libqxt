#include "qxtpipe.h"

struct Connection
{
    QxtPipe * pipe;
    QIODevice::OpenMode mode;
    Qt::ConnectionType connectionType;
};

class QxtPipePrivate:public QObject,public QxtPrivate<QxtPipe>
{
QXT_DECLARE_PUBLIC(QxtPipe)
public:
        QxtPipePrivate()
        {
            lastsender=0;
        }
        QQueue<char> q;
        QList<Connection> connections;
        const QxtPipe * lastsender;
public slots:
        void push (QByteArray data, const QxtPipe * sender );
};

