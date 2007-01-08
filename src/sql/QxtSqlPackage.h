/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

/**
\class QxtSqlPackage QxtSqlPackage

\ingroup sql

\brief full serialiseable QSqlQuery storage 
 

Sometimes you want to set sql results over network or store them into files. QxtSqlPackage can provide you a storage that is still valid after the actual QSqlQuery has been destroyed
for confidence the interface is similiar to QSqlQuery.
*/



#ifndef QXTSQLPACKAGE_H
#define QXTSQLPACKAGE_H
#include <QObject>
#include <QHash>
#include <QList>
#include <QtSql>
#include "QxtDefines.h"



class QXT_DLLEXPORT QxtSqlPackage : public  QObject

{


	Q_OBJECT

	public:
		QxtSqlPackage(QObject *parent = 0);
		QxtSqlPackage( const QxtSqlPackage & other,QObject *parent = 0 );

		///determinates if the package curently points to a valid row
		bool isValid();

		///curent pointer position
		int at();

		/** \brief point to next entry
		
		returns false if there is no next entry.\n
		provided for easy porting from QSqlQuery.

		\code	
		while (query.next())
			{
			}
		\endcode 
		*/
		bool next();
		
		///point to last entry in storage
		bool last();

		///point to first entry in storage
		bool first();

		/** \brief return a cloumn in curent row
		
		in contrast to QSqlQuery you have to provide the name of the key.

		the entry is returned as QString becouse in most cases you need QString anyway, and converting to needed data type is easy.
		\code
		QString name = query.value("name");	
		\endcode 
		*/
		QString value(QString key);

		/** \brief read from QSqlQuery
		
		read out a QSqlQuery and store the result. you may close the query after reading, the data will stay.

		\code
		QxSqlPackage::insert(QSqlQuery::exec("select name,foo,bar from table;"));
		\endcode 
		*/		
 		void insert(QSqlQuery query);

		///Returns the number of rows stored
		int count() const;

		///serialise Data
		QByteArray data() const;

		///deserialise data
		void setData(QByteArray data) ;

		///return a specific row as Hash
		QHash<QString,QString> hash(int index);
		///return the curent row as Hash
		QHash<QString,QString> hash();
		QxtSqlPackage & operator= ( const QxtSqlPackage & other );

	private:
		QList <QHash<QString,QString> > map;
		int record;
};



#endif
