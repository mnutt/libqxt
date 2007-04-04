/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>  <coda@bobandgeorge.com>
**
****************************************************************************/

#include "QxtSqlPackage.h"
#include <QBuffer>
#include <QDataStream>


QxtSqlPackage::QxtSqlPackage(QObject *parent) 
	: QObject(parent) 

	{
	record = -1;
	}

QxtSqlPackage::QxtSqlPackage( const QxtSqlPackage & other, QObject *parent )
: QObject(parent)
{
record = -1;

setData(other.data());
}



bool QxtSqlPackage::isValid()
	{
	if ((record >= 0) && (record < map.count()  ))
		return true;
	else
		return false;
	}



int QxtSqlPackage::at()
	{
	return record;
	}


bool QxtSqlPackage::next()
	{
	
	record++;
	if (record > (map.count()-1))
		{
		last();
		return false;
		}

	return true;
	}



bool QxtSqlPackage::last()
	{
	record=map.count()-1;
	if (record >= 0)
		return true;
	else
		return false;
	}

bool QxtSqlPackage::first()
	{
	if (map.count())
		{
		record=0;
		return true;
		}
	else
		{
		record=-1;
		return false;
		}
	
	}



QString QxtSqlPackage::value(QString key)
	{
	if ((record<0) || !map.count()) return QString();

	return map.at(record).value(key);

	}



void QxtSqlPackage::insert(QSqlQuery query)
	{
	map.clear();
	record=-1;


	while (query.next())
		{
		
		QSqlRecord rec =  query.record ();
		QHash<QString,QString> hash;
		
		
		for (int i =0 ; i < rec.count();i++)
				{
				QSqlField f = rec.field(i);
				hash[f.name()]=f.value().toString();
				}
			
		map.append(hash);
		
		}
	
	
	
	}


int QxtSqlPackage::count() const
{
	return map.count();

}


QByteArray QxtSqlPackage::data() const

{

	QBuffer buff;
	buff.open(QBuffer::WriteOnly);
	QDataStream stream(&buff);
	
	stream<<count();
	for (int i=0; i < count();i++)
		stream << map.at(i);
	
	
	buff.close();
	return buff.data()/*.toBase64()*/;
}








void QxtSqlPackage::setData(QByteArray data)

{
// data =  QByteArray::fromBase64(data);

	map.clear();
	record=-1;


	QBuffer buff;
	buff.setData(data);
	buff.open(QBuffer::ReadOnly);
	QDataStream stream(&buff);
	
	int c;
	stream >> c;

	for (int i=0; i<c;i++)
		{
		QHash<QString,QString> hash;
		stream >> hash;
		map.append(hash);
		}
	
	
	
}





QHash<QString,QString> QxtSqlPackage::hash(int index)
{
if (index > count())  
	{
	QHash<QString,QString> a;
	return a;
	}
return map.at(index);
}


QHash<QString,QString> QxtSqlPackage::hash()
{
qDebug()<<record;
return map.at(record);
}


QxtSqlPackage & QxtSqlPackage::operator= ( const QxtSqlPackage & other ) 

{
setData(other.data());
return *this;

}


