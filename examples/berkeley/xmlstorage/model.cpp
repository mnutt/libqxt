#include "model.h"
#include "xml2bdb.h"
#include <QDebug>
#include <QProgressDialog>
#include <QApplication>
#include <QFile>

XmlDbModel::XmlDbModel(QString db):QAbstractItemModel(),QxtBdbTree<XmlNode>()
{
    open(db);
}

XmlDbModel::XmlDbModel():QAbstractItemModel(),QxtBdbTree<XmlNode>()
{
    cache.root()->children=-1;
    cache.root()->node=root();
}
bool XmlDbModel::open  (QString file)
{
    bool p= QxtBdbTree<XmlNode>::open(file);

    cache.root()->children=-1;
    cache.root()->node=root();

    if(canFetchMore(QModelIndex()))
        fetchMore(QModelIndex());
    reset();

    return p;
}

void XmlDbModel::loadXml(QStringList files)
{
    reset();

    QProgressDialog d;
    d.setLabelText("Loading xml files into database.");
    d.show();
    d.setMaximum(files.count());
    for (int i=0;i<files.count();i++)
    {
        QApplication::processEvents ();
        if(d.wasCanceled())
            break;
        QFile file(files.at(i));
        file.open(QIODevice::ReadOnly);
        d.setValue(i);

        Xml2Bdb x;
        x.setDevice(&file);
        x.read(root());
    }

    cache.clear();
    cache.root()->children=-1;
    cache.root()->node=root();

    if(canFetchMore(QModelIndex()))
        fetchMore(QModelIndex());

    reset();
}

int XmlDbModel::columnCount ( const QModelIndex & ) const
{
    return 3;
}

QVariant XmlDbModel::data ( const QModelIndex & index, int role  ) const
{
    Q_ASSERT_X(index.isValid(),Q_FUNC_INFO,"invalid index");

    if(role!=Qt::DisplayRole)
        return QVariant();

    if(index.column()==0)
        return cache.fromVoid(index.internalPointer())->node.value().name;
    if(index.column()==1)
    {
        switch(cache.fromVoid(index.internalPointer())->node.value().type)
        {
            case 0:
                return "NoToken";
            case 2:
                return "StartDocument";
            case 3:
                return "EndDocument";
            case 4:
                return "StartElement";
            case 5:
                return "EndElement";
            case 6:
                return "Characters";
            case 7:
                return "Comment";
            case 8:
                return "DTD";
            case 9:
                return "EntityReference";
            case 10:
                return "ProcessingInstruction";
            case 1:
            default:
                return "Invalid";
        }
    }
    if(index.column()==2)
        return cache.fromVoid(index.internalPointer())->node.value().value;

    return QVariant();

}

QVariant XmlDbModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
    if(orientation!=Qt::Horizontal)
        return QVariant();
    if(role!=Qt::DisplayRole)
        return QVariant();
    if (section==0)
        return "name";
    if (section==1)
        return "type";
    if (section==2)
        return "value";
    return QVariant();
}

QModelIndex XmlDbModel::parent ( const QModelIndex & index ) const
{
    Q_ASSERT_X(index.isValid(),Q_FUNC_INFO,"invalid index");

    QxtLinkedTreeIterator <XmlDbModelCacheItem> it;
    it=cache.fromVoid(index.internalPointer()).parent();
    Q_ASSERT_X(it.isValid(),Q_FUNC_INFO,"invalid iterator inside valid index (wtf?)");

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
    if(!it.isValid())
        return QModelIndex();
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
    if (it->children<0)
        return 0;
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


