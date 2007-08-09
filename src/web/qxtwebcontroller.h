#ifndef QxtWebController_H_sapoidnasoas
#define QxtWebController_H_sapoidnasoas

#include <QObject>
#include <QTextStream>
#include <QVariant>
#include "qxtwebcore.h"

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
        private:
                QTextStream *stream_m;
        };

#endif

