#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <QAbstractItemModel>
#include <QxtBdbTree>
#include <QxtLinkedTree>
#include "node.h"
#include <QStringList>

struct XmlDbModelCacheItem
{
    QxtBdbTreeIterator<XmlNode> node;
    int children;
};


class XmlDbModel : public QAbstractItemModel, public QxtBdbTree<XmlNode>
{
public:
    XmlDbModel(QString db);
    XmlDbModel();
    bool open  (QString file);
    void loadXml (QStringList  files);
    virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual QModelIndex parent ( const QModelIndex & index ) const;
    virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    virtual bool canFetchMore ( const QModelIndex & parent ) const;
    virtual void fetchMore ( const QModelIndex & parent );
private:
    mutable QxtLinkedTree <XmlDbModelCacheItem> cache ;
};

#endif // MODEL_H_INCLUDED
