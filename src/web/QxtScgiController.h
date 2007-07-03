#ifndef QxtScgiController_H_sapoidnasoas
#define QxtScgiController_H_sapoidnasoas

#include <QObject>
#include "QxtScgiApplication.h"
#include <QTextStream>
#include <cassert>

class QxtScgiApplication;
class QTcpSocket;
class QxtScgiController : public QObject
        {
        Q_OBJECT
        public:
                QxtScgiController(QString name,QxtScgiApplication *parent);

                int invoke(QTcpSocket * ,server_t &);

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
                QTextStream & echo()
                        {
                        assert(stream_m);
                        return *stream_m;
                        }
                server_t SERVER;
        private:
                QTextStream *stream_m;


        };


#endif
