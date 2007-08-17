#ifndef QxtFcgiConnector_header_guards_oaksndoapsid
#define QxtFcgiConnector_header_guards_oaksndoapsid


#include <QByteArray>
#include <QHostAddress>
#include <qxtpimpl.h>
#include "qxtabstractwebconnector.h"

class QxtFcgiConnectorPrivate;
class QxtFcgiConnector : public QxtAbstractWebConnector
        {
        Q_OBJECT
        QXT_DECLARE_PRIVATE(QxtFcgiConnector);

        public:
                QxtFcgiConnector();
                virtual int  start (quint16 ,const QHostAddress &);

                virtual QIODevice * socket();
                virtual void sendHeader(server_t &);

                virtual void close();

                virtual QByteArray content(quint64 maxsize);
        };


#endif
