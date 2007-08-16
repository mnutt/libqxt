#include "qxtfcgiconnector.h"
#include <QTcpSocket>
#include <QTcpServer>


#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"
#include <QMetaType>
#include <QThread>
#include "qxtstdstreambufdevice.h"

Q_DECLARE_METATYPE(FCGX_Request)

// Maximum number of bytes allowed to be read from stdin
static const unsigned long STDIN_MAX = 1000000;


class QxtFcgiConnectorPrivate : public QThread,public QxtPrivate<QxtFcgiConnector>
        {
        QXT_DECLARE_PUBLIC(QxtFcgiConnector);
        Q_OBJECT
        public:
                QxtFcgiConnectorPrivate();
                void run();

                QxtStdStreambufDevice * io;

                bool open;

        signals:
                void close_ss();

                

        };


