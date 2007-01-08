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

