#ifndef QxtAbstractWebConnector_header_guards_oaksndoapsid
#define QxtAbstractWebConnector_header_guards_oaksndoapsid


#include <QByteArray>
#include <QHostAddress>

#include "qxtwebcore.h"


class QxtAbstractWebConnector : public QObject
        {
        Q_OBJECT
        public:
                virtual int  start (quint16 port,const QHostAddress & address)=0;


                virtual QIODevice * socket()=0;
                virtual void sendHeader(server_t &)=0;

                virtual void close()=0;
        signals:
                void incomming(server_t &);
                void aboutToClose();
        };


#endif
