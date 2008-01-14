#include "qxtstdio.h"
#include <QSocketNotifier>
#include <QQueue>

class QxtStdioPrivate : public QObject,public QxtPrivate<QxtStdio>
{
    Q_OBJECT

public:
    QXT_DECLARE_PUBLIC(QxtStdio);
private:
    QSocketNotifier * notify;
    QQueue<char> inbuffer;
private slots:
    void activated(int );
};




