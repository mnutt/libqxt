#include "qxtstdio.h"
#include <QSocketNotifier>

class QxtStdioPrivate : public QObject,public QxtPrivate<QxtStdio>
{
    Q_OBJECT

public:
    QXT_DECLARE_PUBLIC(QxtStdio);
private:
    QSocketNotifier * notify;
private slots:
    void activated(int );
};




