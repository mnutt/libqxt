#ifndef QxtScgiController_H_sapoidnasoas
#define QxtScgiController_H_sapoidnasoas

#include <QObject>
#include "QxtScgiApplication.h"
#include <QTextStream>
#include <cassert>


///default return header
#define HTML_OK  "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n";




class QxtScgiApplication;
class QTcpSocket;
class QxtScgiController : public QObject
        {
        Q_OBJECT
        public:
                QxtScgiController(QString name);

                int invoke(QTcpSocket * ,server_t &);


                static QString WebRoot();

        public slots:
		 int index()
                        {
			echo()<<"Status: 404 NOT FOUND\r\n";
			echo()<<"Content-Type: text/html\r\n";
			echo()<<"\r\n\r\n";
			echo()<<"overwrite the index function of this controller("+objectName()+")";
                        return 0;
                        }

        protected:
                QTextStream & echo();
                QTcpSocket * socket();
		QString self();

                server_t SERVER;
                post_t POST;
        private:
                QTextStream *stream_m;
                QTcpSocket *socket_m;


        };


#endif
