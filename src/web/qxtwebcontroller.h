#ifndef QxtWebController_H_sapoidnasoas
#define QxtWebController_H_sapoidnasoas

#include <QObject>
#include "qxtwebcore.h"
#include <QTextStream>
#include <cassert>


///default return header
#define HTML_OK  "Status: 200 OK\r\nContent-Type: text/html\r\n\r\n";




class QxtWebController : public QObject
        {
        Q_OBJECT
        public:
                QxtWebController(QString name);

                int invoke(server_t &);


                static QString WebRoot();

        public slots:
		 int index()
                        {
			echo()<<"overwrite the index function of this controller("+objectName()+")";
                        return 404;
                        }

        protected:
                QTextStream & echo();
		QString self();

                server_t SERVER;
                post_t POST;
        private:
                QTextStream *stream_m;


        };


#endif
