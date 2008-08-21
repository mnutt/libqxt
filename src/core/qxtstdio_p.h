#include "qxtstdio.h"
#include <QSocketNotifier>

class QxtStdioPrivate : public QObject,public QxtPrivate<QxtStdio>
{
    Q_OBJECT

public:
    QXT_DECLARE_PUBLIC(QxtStdio);
    QxtStdioPrivate()
    {
        notify=0;
        hadeof=false;
    }
    bool hadeof;
private:
    QSocketNotifier * notify;
private Q_SLOTS:
    void activated(int );
};




