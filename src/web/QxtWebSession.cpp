#include "QxtWebSession.h"
#include <QSqlQuery>
#include <QVariant>
#define SESSTIMOUT "'00:00:10'"
QxtWebSession::QxtWebSession ( QByteArray cookie_m, QSqlDatabase dbf ):QMap<QString,QString>()
        {
        QSqlQuery ("DELETE from `sessions`  WHERE `timeout`<now()",db);

        cookie=cookie_m;
        db=dbf;
        QSqlQuery query("SELECT `key`,`value` FROM `sessions` WHERE `cookie`='"+cookie+"'",db);
        while (query.next()) 
                {
                insert(query.value(0).toString(), query.value(1).toString());
                }

        QSqlQuery ("UPDATE `sessions` SET `timeout`=addtime(now()," SESSTIMOUT " ) WHERE `cookie`='"+cookie+"'",db);
        }
QxtWebSession::~QxtWebSession()
        {
        QSqlQuery ("DELETE from `sessions`  WHERE `cookie`='"+cookie+"'",db);


        QMapIterator<QString, QString> i(*this);
        while (i.hasNext()) 
                {
                i.next();
                QSqlQuery ("INSERT into `sessions` ( `key`, `value` , `timeout` , `cookie`)"
                " VALUES('"+ i.key()+"'  , '"+ i.value()+"' , addtime(now()," SESSTIMOUT  "), '"+cookie+"' ) ",db);
                }

        }




