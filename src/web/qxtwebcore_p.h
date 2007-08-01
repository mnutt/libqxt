#include "qxtwebcore.h"
#include <QTextStream>
#include <qxtstdio.h>

class QxtScgiController;
class QxtWebCorePrivate : public QObject,public QxtPrivate<QxtWebCore>
	{
	Q_OBJECT
	QXT_DECLARE_PUBLIC(QxtWebCore);

	public:
		QxtWebCorePrivate(QObject *parent = 0);
                void init();

        private slots:
                void request(server_t a);
                void startup();
        private:
                QxtRPCPeer * peer;
	};
