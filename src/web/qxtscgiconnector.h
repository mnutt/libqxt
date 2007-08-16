#ifndef QxtScgiConnector_header_guards_oaksndoapsid
#define QxtScgiConnector_header_guards_oaksndoapsid


#include <QByteArray>
#include <QHostAddress>
#include <qxtpimpl.h>
#include "qxtabstractwebconnector.h"

class QxtScgiConnectorPrivate;
class QxtScgiConnector : public QxtAbstractWebConnector
        {
        Q_OBJECT
        QXT_DECLARE_PRIVATE(QxtScgiConnector);

        public:
                QxtScgiConnector();
                virtual int  start (quint16 port,const QHostAddress & address);

                virtual QIODevice * socket();
                virtual void sendHeader(server_t &);

                virtual void close();


        };


#endif
