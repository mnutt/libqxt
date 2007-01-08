#ifndef QXTSQLQUERY_H
#define QXTSQLQUERY_H
#include <QSqlQuery>
#include <QxtSqlPackage.h>
#include "QxtDefines.h"



class QX_DLLEXPORT QxtSqlQuery : public  QSqlQuery
{
public:
 
QxtSqlQuery ( QSqlResult * result )  : QSqlQuery(result) {}
QxtSqlQuery ( const QString & query = QString(), QSqlDatabase db = QSqlDatabase() )  : QSqlQuery(query,db) {}
QxtSqlQuery ( QSqlDatabase db ) : QSqlQuery(db) {}
QxtSqlQuery ( const QSqlQuery & other ) : QSqlQuery(other) {}

QxtSqlPackage package ()
	{
	


	}
};


#endif

