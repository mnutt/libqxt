#include "qxtviralcsv.h"

#include <Viral/Csv>
#include <Viral/Csv>
#include "qxtviraladapter_p.h"

class QxtViralCsvPrivate :  public QxtPrivate<QxtViralCsv>
{
public:
    Viral::Csv *  csv;
    QxtViralAdapter<QxtViralCsv,Viral::Csv> * viral;
};


QxtViralCsv::QxtViralCsv(QString filename,QChar seperator,bool witheaders ,QObject *parent ):QAbstractItemModel(parent)
{
    QXT_INIT_PRIVATE(QxtViralCsv);
    qxt_d().csv = new Viral::Csv(filename.toStdString(),seperator.toLatin1(),witheaders);
    qxt_d().viral = new QxtViralAdapter<QxtViralCsv,Viral::Csv> (this,qxt_d().csv );
}
QxtViralCsv::~QxtViralCsv()
{
    delete qxt_d().viral;
    delete qxt_d().csv;
}

QVariant QxtViralCsv::data(const QModelIndex &index, int role) const
{
    try
    {
        return qxt_d().viral->data(index,role);
    }
    catch(...)
    {
        return QVariant();
    }
}

Qt::ItemFlags QxtViralCsv::flags(const QModelIndex &index) const
{
    try
    {
        return qxt_d().viral->flags(index);
    }
    catch(...)
    {
        return 0;
    }
}


QModelIndex QxtViralCsv::index(int row, int column, const QModelIndex &parent ) const
{
    try
    {
        return qxt_d().viral->index(row,column,parent);
    }
    catch(...)
    {
        return QModelIndex();
    }
}

QModelIndex QxtViralCsv::parent(const QModelIndex &index) const
{
    try
    {
        return qxt_d().viral->parent(index);
    }
    catch(...)
    {
        return QModelIndex();
    }
}

int QxtViralCsv::rowCount(const QModelIndex &parent ) const
{
    try
    {
        return qxt_d().viral->rowCount(parent);
    }
    catch(...)
    {
        return 0;
    }
}

int QxtViralCsv::columnCount(const QModelIndex & ) const
{
    return 2;
}

QVariant QxtViralCsv::headerData ( int section, Qt::Orientation , int role ) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();
    if(section==0)
        return QString("name");
    return QString("value");
}



