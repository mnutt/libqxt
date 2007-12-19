/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
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
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QxtLinkedTree_H_Guard_pklandlkasmndlkasd
#define QxtLinkedTree_H_Guard_pklandlkasmndlkasd

#include <qxtsharedprivate.h>



template<class T>
class QxtLinkedTree;

template<class T>
class QxtLinkedTreeIterator;

template<class T>
class QxtLinkedTreeItem
{
    QxtLinkedTreeItem (T tt)
    {
        t=tt;
        next=0;
        previous=0;
        parent=0;
        child=0;
    }

    friend class QxtLinkedTree<T>;
    friend class QxtLinkedTreeIterator<T>;
    QxtLinkedTreeItem * next;
    QxtLinkedTreeItem * previous;
    QxtLinkedTreeItem * parent;
    QxtLinkedTreeItem * child;
    T t;
    ///TODO: somehow notify all iterators when one deletes this. so they can be made invalid instead of undefined.
};




///FIXME: nested would be cooler but c++ has no typdefs with templates and doxygen doesnt undertsand nested templates
template<class T>
class QxtLinkedTreeIterator
{
public:
    QxtLinkedTreeIterator();
    QxtLinkedTreeIterator(const QxtLinkedTreeIterator<T> & other);
    QxtLinkedTreeIterator & operator= ( const QxtLinkedTreeIterator<T> & other );

    QxtLinkedTreeIterator    parent   () const;
    QxtLinkedTreeIterator    next     () const;
    QxtLinkedTreeIterator    previous () const;
    QxtLinkedTreeIterator    child    () const;

    bool isValid() const;

    T & operator* () const;
    T * operator-> () const;
    operator T() const;

    QxtLinkedTreeIterator    operator + ( int j ) const;
    QxtLinkedTreeIterator &  operator ++ ();
    QxtLinkedTreeIterator &  operator ++ (int);
    QxtLinkedTreeIterator &  operator += ( int j );

    QxtLinkedTreeIterator    operator - ( int j ) const;
    QxtLinkedTreeIterator &  operator -- ();
    QxtLinkedTreeIterator &  operator -- (int);
    QxtLinkedTreeIterator &  operator -= ( int j );

    bool operator== ( const QxtLinkedTreeIterator<T> & other ) const;
    bool operator!= ( const QxtLinkedTreeIterator<T> & other ) const;

    QxtLinkedTreeIterator erase  () const;
    QxtLinkedTreeIterator append (const T & value) const;

private:
    friend class QxtLinkedTree<T>;

    QxtLinkedTreeIterator(QxtLinkedTreeItem<T> * t);
    QxtLinkedTreeItem<T> *item;
};






template<class T>
class QxtLinkedTree
{
public:


    QxtLinkedTree(T t);

    QxtLinkedTreeIterator<T> begin();

    #if 0
    QxtLinkedTreeIterator insert ( iterator before, const T & value );
    #endif

private:
    QxtSharedPrivate< QxtLinkedTreeItem<T> >  qxt_d;
};






template<class T>
QxtLinkedTreeIterator<T>::QxtLinkedTreeIterator()
{
    item=0;
}

template<class T>
QxtLinkedTreeIterator<T>::QxtLinkedTreeIterator(const QxtLinkedTreeIterator<T> & other)
{
    item=other.item;
}

template<class T>
class QxtLinkedTreeIterator<T> & QxtLinkedTreeIterator<T>::operator= ( const QxtLinkedTreeIterator<T> & other )
{
    item=other.item;
    return *this;
}



template<class T>
class QxtLinkedTreeIterator<T> QxtLinkedTreeIterator<T>::parent   () const
{
    return QxtLinkedTreeIterator<T>(item->parent);
}

template<class T>
class QxtLinkedTreeIterator<T> QxtLinkedTreeIterator<T>::next     () const
{
    return QxtLinkedTreeIterator<T>(item->next);
}

template<class T>
class QxtLinkedTreeIterator<T> QxtLinkedTreeIterator<T>::previous () const
{
    return QxtLinkedTreeIterator<T>(item->previous);
}

template<class T>
class QxtLinkedTreeIterator<T> QxtLinkedTreeIterator<T>::child    () const
{
    return QxtLinkedTreeIterator<T>(item->child);
}

template<class T>
bool  QxtLinkedTreeIterator<T>::isValid() const
{
    return (item!=0);
}



template<class T>
T &  QxtLinkedTreeIterator<T>::operator* () const
{
    Q_ASSERT_X(item,Q_FUNC_INFO,"iterator out of range");
    return item->t;
}

template<class T>
T *  QxtLinkedTreeIterator<T>::operator-> () const
{
    Q_ASSERT_X(item,Q_FUNC_INFO,"iterator out of range");
    return &item->t;
}

template<class T>
QxtLinkedTreeIterator<T>::operator T () const
{
    Q_ASSERT_X(item,Q_FUNC_INFO,"iterator out of range");
    return item->t;
}


template<class T>
QxtLinkedTreeIterator<T>::QxtLinkedTreeIterator(QxtLinkedTreeItem<T> * t)
{
    item=t;
}



template<class T>
class QxtLinkedTreeIterator<T>   QxtLinkedTreeIterator<T>::operator + ( int j ) const
{
    QxtLinkedTreeItem<T>  * m=item;
    for (int i=0;i<j;i++)
    {
        m=m->next;
        if(m==0)
            return QxtLinkedTreeIterator<T>();
    }
    return QxtLinkedTreeIterator<T>(m);
}

template<class T>
class QxtLinkedTreeIterator<T> &  QxtLinkedTreeIterator<T>::operator ++ ()
{
    *this= QxtLinkedTreeIterator<T>(item->next);
    return *this;
}

template<class T>
class QxtLinkedTreeIterator<T> &  QxtLinkedTreeIterator<T>::operator ++ (int)
{
    *this= QxtLinkedTreeIterator<T>(item->next);
    return *this;
}

template<class T>
class QxtLinkedTreeIterator<T> &  QxtLinkedTreeIterator<T>::operator += ( int j )
{
    *this=*this+j;
    return *this;
}

template<class T>
class QxtLinkedTreeIterator<T>   QxtLinkedTreeIterator<T>::operator - ( int j ) const
{
    QxtLinkedTreeItem<T>  * m=item;
    for (int i=0;i<j;i++)
    {
        m=m->previous;
        if(m==0)
            return QxtLinkedTreeIterator<T>();
    }
    return QxtLinkedTreeIterator<T>(m);
}

template<class T>
class QxtLinkedTreeIterator<T> &  QxtLinkedTreeIterator<T>::operator -- ()
{
    *this= QxtLinkedTreeIterator<T>(item->previous);
    return *this;
}

template<class T>
class QxtLinkedTreeIterator<T> &  QxtLinkedTreeIterator<T>::operator -- (int)
{
    *this= QxtLinkedTreeIterator<T>(item->previous);
    return *this;

}

template<class T>
class QxtLinkedTreeIterator<T> &  QxtLinkedTreeIterator<T>::operator -= ( int j )
{
    *this=*this-j;
    return *this;
}


template<class T>
bool QxtLinkedTreeIterator<T>::operator== ( const QxtLinkedTreeIterator<T> & other ) const
{
    return (other.item==item);
}

template<class T>
bool QxtLinkedTreeIterator<T>::operator!= ( const QxtLinkedTreeIterator<T> & other ) const
{
    return (other.item!=item);
}




template<class T>
class QxtLinkedTreeIterator<T>  QxtLinkedTreeIterator<T>::erase  () const
{
    QxtLinkedTreeItem <T> node= item;
    QxtLinkedTreeItem <T> parent= item->parent;
    QxtLinkedTreeItem <T> next= node->next;


    Q_ASSERT_X(parent,Q_FUNC_INFO,"removing root node not supported yet.");

    if(parent->child==node)
    {
        parent->child=node->next;
    }
    else 
    {
        QxtLinkedTreeItem <T> * n=parent->child;
        while(n->next!=node)
        {
            Q_ASSERT_X(n->next!=0,Q_FUNC_INFO,"reached end of chain and didn't find the node requested for removal.");
            n=n->next;
        }
        n->next=node->next;
    }
    delete node;
    item=0;
    return QxtLinkedTreeIterator<T>(next);
}

template<class T>
class QxtLinkedTreeIterator<T>  QxtLinkedTreeIterator<T>::append (const T & value ) const
{
    QxtLinkedTreeItem <T> * parent= item;
    Q_ASSERT_X(parent,Q_FUNC_INFO,"invalid iterator");

    QxtLinkedTreeItem<T> *node = new QxtLinkedTreeItem<T>(value);

    if(parent->child==0)
    {
        parent->child=node;
        node->parent=parent;
        node->previous=0;
        return QxtLinkedTreeIterator<T>(node);
    }

    QxtLinkedTreeItem <T> * n=parent->child;
    while(n->next!=0)
        n=n->next;
    n->next=node;
    node->parent=parent;
    node->previous=n;
    return QxtLinkedTreeIterator<T>(node);
}














template<class T>
QxtLinkedTree<T>::QxtLinkedTree(T t)
{
    qxt_d=new QxtLinkedTreeItem<T>(t);
}

template<class T>
class QxtLinkedTreeIterator<T> QxtLinkedTree<T>::begin  ()
{
    return QxtLinkedTreeIterator<T>(&qxt_d());
}





#endif
