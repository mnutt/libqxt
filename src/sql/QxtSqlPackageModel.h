/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

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



