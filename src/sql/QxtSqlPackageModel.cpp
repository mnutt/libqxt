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

#include "QxtSqlPackageModel.h"



QxtSqlPackageModel::QxtSqlPackageModel  (QObject * parent ) : QAbstractTableModel(parent)
 {}


void QxtSqlPackageModel::setQuery(QxtSqlPackage a) 
	{
pack =a;

}


int QxtSqlPackageModel::rowCount ( const QModelIndex &  ) const 
	{
	return pack.count();
	}


int QxtSqlPackageModel::columnCount ( const QModelIndex & ) const 
	{
	QxtSqlPackage p =pack;
	return p.hash(0).count();
	}


QVariant QxtSqlPackageModel::data ( const QModelIndex  & index, int role  ) const
	{
	if  (role != Qt::DisplayRole )
        	return QVariant();



	if ((index.row()<0)  || (index.column()<0)  ) return QVariant();
	QxtSqlPackage p =pack;

	return  p.hash(index.row()).values ().at( index.column());


	}


QVariant QxtSqlPackageModel::headerData ( int section, Qt::Orientation orientation, int role  ) const
	{

	if (orientation == Qt::Vertical && role == Qt::DisplayRole) 
		return section;


	if(orientation==Qt::Horizontal && role == Qt::DisplayRole)
		{ 
		QxtSqlPackage p =pack;
		return p.hash(0).keys ().at( section )    ;
		}

    	return QAbstractItemModel::headerData(section, orientation, role);

	}

