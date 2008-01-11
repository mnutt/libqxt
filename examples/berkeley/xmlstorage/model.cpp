#include "model.h"
#include "xml2bdb.h"
#include <QDebug>


XmlDbModel::XmlDbModel(QString db):QAbstractItemModel(),QxtBdbTree<XmlNode>()
{
    open(db);
}

XmlDbModel::XmlDbModel():QAbstractItemModel(),QxtBdbTree<XmlNode>()
{
}
bool XmlDbModel::open  (QString file)
{
    bool p= QxtBdbTree<XmlNode>::open(file);

    XmlDbModelCacheItem ci;
    ci.node=root();
    ci.children=-1;

    *cache.root()=ci;
    if(canFetchMore(QModelIndex()))
        fetchMore(QModelIndex());
    reset();

    return p;
}

void XmlDbModel::loadXml(QIODevice * d)
{
    Xml2Bdb x;
    x.setDevice(d);
    x.read(root());

}

int XmlDbModel::columnCount ( const QModelIndex & ) const
{
    return 3;
}

QVariant XmlDbModel::data ( const QModelIndex & index, int role  ) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();

    if(index.column()==0)
        return cache.fromVoid(index.internalPointer())->node.value().name;
    if(index.column()==1)
        return cache.fromVoid(index.internalPointer())->node.value().type;
    if(index.column()==2)
        return cache.fromVoid(index.internalPointer())->node.value().value;

    return QVariant();

}

QModelIndex XmlDbModel::parent ( const QModelIndex & index ) const
{
    QxtLinkedTreeIterator <XmlDbModelCacheItem> it;
    it=cache.fromVoid(index.internalPointer()).parent();
    if(!it.isValid())
        return QModelIndex();
    if(it==cache.root())
        return QModelIndex();

    int row=0;
    QxtLinkedTreeIterator <XmlDbModelCacheItem > et=it;
    --et;
    while(et.isValid())
    {
        --et;
        row++;
    }
    return createIndex(row,0,cache.toVoid (it));
}

QModelIndex XmlDbModel::index ( int row, int column, const QModelIndex & parent ) const
{
    if(canFetchMore(parent))
        const_cast<XmlDbModel*>(this)->fetchMore(parent);

    QxtLinkedTreeIterator <XmlDbModelCacheItem > it;
    if (parent.isValid())
        it=cache.fromVoid(parent.internalPointer()).child();
    else
        it=cache.root().child();
    it+=row;
//     Q_ASSERT(it.isValid());
    return createIndex(row,column,cache.toVoid (it));
}

int XmlDbModel::rowCount ( const QModelIndex & parent ) const
{
    if(canFetchMore(parent))
        const_cast<XmlDbModel*>(this)->fetchMore(parent);

    QxtLinkedTreeIterator <XmlDbModelCacheItem > it;
    if(parent.isValid())
        it=cache.fromVoid(parent.internalPointer());
    else
        it=cache.root();
    return it->children;
}

void XmlDbModel::fetchMore ( const QModelIndex & parent )
{
    QxtLinkedTreeIterator <XmlDbModelCacheItem > itl;
    if(parent.isValid())
        itl=cache.fromVoid(parent.internalPointer());
    else
        itl=cache.root();

    QxtBdbTreeIterator<XmlNode> it=itl->node.child();

    int cc=0;
    while(it.isValid())
    {
        qDebug()<<"+"<<it.value().name;

        XmlDbModelCacheItem ci;
        ci.node=it;
        ci.children=-1;

        itl.append(ci);
        ++it;
        ++cc;
    }
    itl->children=cc;
}

bool XmlDbModel::canFetchMore ( const QModelIndex & parent ) const
{
    QxtLinkedTreeIterator <XmlDbModelCacheItem > itl;
    if(parent.isValid())
        itl=cache.fromVoid(parent.internalPointer());
    else
        itl=cache.root();

    return(itl.child().isValid()!=itl->node.child().isValid());
}


