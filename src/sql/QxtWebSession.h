#ifndef QXTWEBSESSIONkasdiaodadasdada
#define QXTWEBSESSIONkasdiaodadasdada
#include <QSqlDatabase>
#include <QMap>
class QxtWebSession : public QMap<QString,QString>
        {
        public:
                QxtWebSession ( QByteArray cookie, QSqlDatabase db = QSqlDatabase());
                ~QxtWebSession();

        private:
                QSqlDatabase db;
                QByteArray cookie;
        };



#endif

