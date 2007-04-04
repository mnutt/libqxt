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
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/

/**
\class QxtSqlPackageModel QxtSqlPackageModel

\ingroup sql

\brief  provides a read-only data model for QxtSqlPackage result..
*/



#ifndef QXTSQLTABLEMODEL_H
#define QXTSQLTABLEMODEL_H
#include <QAbstractTableModel>
#include <QxtSql/QxtSqlPackage>
#include <Qxt/qxtglobal.h>
#include <QHash>


class QXT_SQL_EXPORT QxtSqlPackageModel : public  QAbstractTableModel
{
public:
/// \reimp
QxtSqlPackageModel  (QObject * parent = 0 );



/// set the data for the model. do this before any access
void setQuery(QxtSqlPackage a) ;


/// \reimp
int rowCount ( const QModelIndex &  = QModelIndex()) const ;
/// \reimp
int columnCount ( const QModelIndex  & = QModelIndex() ) const ;
/// \reimp
QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
/// \reimp
QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

private:

QxtSqlPackage pack;
};


#endif



