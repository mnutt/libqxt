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
    QxtLinkedTreeItem * next;
    QxtLinkedTreeItem * previous;
    QxtLinkedTreeItem * parent;
    QxtLinkedTreeItem * child;
    T t;
    ///TODO: somehow notify all iterators when one deletes this. so they can be made invalid instead of undefined.
};


template<class T>
class QxtLinkedTree
{
public:

    class iterator
    {
    public:
        iterator();
        iterator(const iterator & other);
        iterator & operator= ( const iterator & other );

        iterator    parent   () const;
        iterator    next     () const;
        iterator    previous () const;
        iterator    child    () const;

        bool isValid() const;

        T & operator* () const;
        T * operator-> () const;
        operator T() const;

        iterator    operator + ( int j ) const;
        iterator &  operator ++ ();
        iterator &  operator ++ (int);
        iterator &  operator += ( int j );

        iterator    operator - ( int j ) const;
        iterator &  operator -- ();
        iterator &  operator -- (int);
        iterator &  operator -= ( int j );

        bool operator== ( const iterator & other ) const;
        bool operator!= ( const iterator & other ) const;

        iterator erase  () const;
        iterator append (const T & value) const;

    private:
        friend class QxtLinkedTree<T>;

        iterator(QxtLinkedTreeItem<T> * t);
        QxtLinkedTreeItem<T> *item;
    };




    QxtLinkedTree(T t);

    iterator begin  ();

    #if 0
    iterator insert ( iterator before, const T & value );
    #endif

private:
    QxtSharedPrivate< QxtLinkedTreeItem<T> >  qxt_d;
};









template<class T>
QxtLinkedTree<T>::iterator::iterator()
{
    item=0;
}

template<class T>
QxtLinkedTree<T>::iterator::iterator(const iterator & other)
{
    item=other.item;
}

template<class T>
class QxtLinkedTree<T>::iterator & QxtLinkedTree<T>::iterator::operator= ( const iterator & other )
{
    item=other.item;
    return *this;
}



template<class T>
class QxtLinkedTree<T>::iterator QxtLinkedTree<T>::iterator::parent   () const
{
    return iterator(item->parent);
}

template<class T>
class QxtLinkedTree<T>::iterator QxtLinkedTree<T>::iterator::next     () const
{
    return iterator(item->next);
}

template<class T>
class QxtLinkedTree<T>::iterator QxtLinkedTree<T>::iterator::previous () const
{
    return iterator(item->previous);
}

template<class T>
class QxtLinkedTree<T>::iterator QxtLinkedTree<T>::iterator::child    () const
{
    return iterator(item->child);
}

template<class T>
bool  QxtLinkedTree<T>::iterator::isValid() const
{
    return (item!=0);
}



template<class T>
T &  QxtLinkedTree<T>::iterator::operator* () const
{
    Q_ASSERT_X(item,Q_FUNC_INFO,"iterator out of range");
    return item->t;
}

template<class T>
T *  QxtLinkedTree<T>::iterator::operator-> () const
{
    Q_ASSERT_X(item,Q_FUNC_INFO,"iterator out of range");
    return &item->t;
}

template<class T>
QxtLinkedTree<T>::iterator::operator T () const
{
    Q_ASSERT_X(item,Q_FUNC_INFO,"iterator out of range");
    return item->t;
}


template<class T>
QxtLinkedTree<T>::iterator::iterator(QxtLinkedTreeItem<T> * t)
{
    item=t;
}



template<class T>
class QxtLinkedTree<T>::iterator    QxtLinkedTree<T>::iterator::operator + ( int j ) const
{
    QxtLinkedTreeItem<T>  * m=item;
    for (int i=0;i<j;i++)
    {
        m=m->next;
        if(m==0)
            return iterator();
    }
    return iterator(m);
}

template<class T>
class QxtLinkedTree<T>::iterator &  QxtLinkedTree<T>::iterator::operator ++ ()
{
    *this= iterator(item->next);
    return *this;
}

template<class T>
class QxtLinkedTree<T>::iterator &  QxtLinkedTree<T>::iterator::operator ++ (int)
{
    *this= iterator(item->next);
    return *this;
}

template<class T>
class QxtLinkedTree<T>::iterator &  QxtLinkedTree<T>::iterator::operator += ( int j )
{
    *this=*this+j;
    return *this;
}

template<class T>
class QxtLinkedTree<T>::iterator   QxtLinkedTree<T>::iterator::operator - ( int j ) const
{
    QxtLinkedTreeItem<T>  * m=item;
    for (int i=0;i<j;i++)
    {
        m=m->previous;
        if(m==0)
            return iterator();
    }
    return iterator(m);
}

template<class T>
class QxtLinkedTree<T>::iterator &  QxtLinkedTree<T>::iterator::operator -- ()
{
    *this= iterator(item->previous);
    return *this;
}

template<class T>
class QxtLinkedTree<T>::iterator &  QxtLinkedTree<T>::iterator::operator -- (int)
{
    *this= iterator(item->previous);
    return *this;

}

template<class T>
class QxtLinkedTree<T>::iterator &  QxtLinkedTree<T>::iterator::operator -= ( int j )
{
    *this=*this-j;
    return *this;
}


template<class T>
bool QxtLinkedTree<T>::iterator::operator== ( const iterator & other ) const
{
    return (other.item==item);
}

template<class T>
bool QxtLinkedTree<T>::iterator::operator!= ( const iterator & other ) const
{
    return (other.item!=item);
}




template<class T>
class QxtLinkedTree<T>::iterator  QxtLinkedTree<T>::iterator::erase  () const
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
    return iterator(next);
}

template<class T>
class QxtLinkedTree<T>::iterator  QxtLinkedTree<T>::iterator::append (const T & value ) const
{
    QxtLinkedTreeItem <T> * parent= item;
    Q_ASSERT_X(parent,Q_FUNC_INFO,"invalid iterator");

    QxtLinkedTreeItem<T> *node = new QxtLinkedTreeItem<T>(value);

    if(parent->child==0)
    {
        parent->child=node;
        node->parent=parent;
        node->previous=0;
        return iterator(node);
    }

    QxtLinkedTreeItem <T> * n=parent->child;
    while(n->next!=0)
        n=n->next;
    n->next=node;
    node->parent=parent;
    node->previous=n;
    return iterator(node);
}














template<class T>
QxtLinkedTree<T>::QxtLinkedTree(T t)
{
    qxt_d=new QxtLinkedTreeItem<T>(t);
}

template<class T>
class QxtLinkedTree<T>::iterator QxtLinkedTree<T>::begin  ()
{
    return iterator(&qxt_d());
}





#endif
