/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qxt library.
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of the Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE.
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
**
** <http://libqxt.org>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QXTVIRALADAPTER_H
#define QXTVIRALADAPTER_H

#include <QAbstractItemModel>
#include <QVector>
#include <Viral/SequenceIterator>
#include <QDebug>

template <class T>
class QxtViralAdapterItem
{
public:
    QxtViralAdapterItem():fetched(false),parent(0)
    {
    }
    void fetch()
    {
        if(fetched)return;
        fetched=true;

        for(Viral::SequenceIterator<T> it(m_viral->begin(node));it!=m_viral->end(node);it++)
        {
            QxtViralAdapterItem<T> m;
            m.node=it;
            m.m_viral=m_viral;
            m.parent=this;
            children<<m;
        }
    }
    bool fetched;
    typename T::NodeIndex node;
    QxtViralAdapterItem * parent;
    QVector<QxtViralAdapterItem> children;
    T * m_viral;
};

template <class Q,class V>
class QxtViralAdapter
{

public:
    QxtViralAdapter(Q* qt,V* viral);
    ~QxtViralAdapter(){delete m_viral;}
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;  
private:
    Q * m_qt;
    V * m_viral;
    QxtViralAdapterItem<V> root;
};

template <class Q,class V>
QxtViralAdapter<Q,V>::QxtViralAdapter(Q* qt,V* viral):m_qt(qt),m_viral(viral)
{
    root.node=m_viral->root();
    root.m_viral=m_viral;
}

template <class Q,class V>
QVariant QxtViralAdapter<Q,V>::data(const QModelIndex &index, int role) const
{
    if(role!=Qt::DisplayRole)
        return QVariant();
    QxtViralAdapterItem<V>  *item=static_cast<QxtViralAdapterItem<V>* >(index.internalPointer());
    if(index.column()==0)
        return QString::fromStdString(m_viral->name(item->node));
    return QString::fromStdString(m_viral->value(item->node));
}

template <class Q,class V>
Qt::ItemFlags QxtViralAdapter<Q,V>::flags(const QModelIndex &index) const
{
    QxtViralAdapterItem<V> *item=static_cast<QxtViralAdapterItem<V>* >(index.internalPointer());
    return 0;
}

template <class Q,class V>
QModelIndex QxtViralAdapter<Q,V>::index(int row, int column, const QModelIndex &parent ) const
{
    if(parent.isValid())
    {
        QxtViralAdapterItem<V> *item=static_cast<QxtViralAdapterItem<V>* >(parent.internalPointer());
        Q_ASSERT(item);
        item->fetch();
        if(row>=item->children.count())
            return  QModelIndex(); 
        return m_qt->createIndex(row,column,(void*)&item->children.at(row));
    }
    if (row!=0)
        return  QModelIndex();
    return m_qt->createIndex(row,column,(void*)&root);
}

template <class Q,class V>
QModelIndex QxtViralAdapter<Q,V>::parent(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QModelIndex();
    }
    QxtViralAdapterItem<V> *item=static_cast<QxtViralAdapterItem<V>* >(index.internalPointer());
    if (item==&root)
        return QModelIndex();
    return m_qt->createIndex(0,0,(void*)item->parent);
}

template <class Q,class V>
int QxtViralAdapter<Q,V>::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return 1;
    }
    QxtViralAdapterItem<V> *item=static_cast<QxtViralAdapterItem<V>* >(parent.internalPointer());
    item->fetch();
    return item->children.count();
}

template <class Q,class V>
int QxtViralAdapter<Q,V>::columnCount(const QModelIndex & ) const
{
    return 2;
}

#endif


