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

#include "qxtlinkedtree.h"



/**
\class QxtLinkedTree QxtLinkedTree
\ingroup QxtCore
\brief fast Container for tree structured data

this template class can be used to store data easily in a tree structure. \n
Internally it uses the doublelinked list scheme, but adds client/parent links. \n \n

There are no random access functions, you have to use QxtLinkedTree::iterator to access the data. \n
This is very fast and efficient.


\code
QxtLinkedTree<int> tree(1);

QxtLinkedTreeIterator<int> it= tree.begin();
it.append(34);
qDebug()<<it<<it.child(); //returns "1 34"

\endcode

\fn QxtLinkedTree::QxtLinkedTree(T t);
default constructor \n
sets the rootnode to \p t
\fn QxtLinkedTreeIterator QxtLinkedTree::begin  ();
returns an iterator on the root node

\class QxtLinkedTreeIterator QxtLinkedTree
\ingroup QxtCore
\brief fast access to an QxtLinkedTree

\fn QxtLinkedTreeIterator    QxtLinkedTreeIterator::child   () const;
returns an iterator to the first child item of this or an invalid iterator when there are no children

\fn QxtLinkedTreeIterator    QxtLinkedTreeIterator::parent   () const;
returns an iterator to the parent item of this. or an invalid iterator when this is the root node

\fn QxtLinkedTreeIterator    QxtLinkedTreeIterator::previous   () const;
returns an iterator to the previous item of this or an invalid iterator when this is the first one in the next/previous chain

\fn QxtLinkedTreeIterator    QxtLinkedTreeIterator::next   () const;
returns an iterator to the next item of this in the previous/next chain or an invalid iterator when this is the last one

\fn bool    QxtLinkedTreeIterator::isValid   () const;
verfies if this iterator points to a valid location inside the tree \n
an invalid node is decoupled from the iteration. it can not be used for anything anymore.\n
\code
QxtLinkedTree<int> tree(1);
QxtLinkedTreeIterator<int> it= tree.begin();

it++; //invalid. there are no siblings.
it--; //still invalid!
\endcode

\fn T &  QxtLinkedTreeIterator::operator* () const;
Returns a modifiable reference to the current item.
You can change the value of an item by using operator*() on the left side of an assignment, for example:
 if (*it == "Hello")
     *it = "Bonjour";

\fn T   QxtLinkedTreeIterator::operator T () const;
returns a copy of the current item.


\fn QxtLinkedTreeIterator    QxtLinkedTreeIterator:: operator + ( int j ) const;
\fn QxtLinkedTreeIterator &  QxtLinkedTreeIterator::operator ++ ();
\fn QxtLinkedTreeIterator &  QxtLinkedTreeIterator::operator ++ (int);
\fn QxtLinkedTreeIterator &  QxtLinkedTreeIterator::operator += ( int j );

\fn QxtLinkedTreeIterator    QxtLinkedTreeIterator::operator - ( int j ) const;
\fn QxtLinkedTreeIterator &  QxtLinkedTreeIterator::operator -- ();
\fn QxtLinkedTreeIterator &  QxtLinkedTreeIterator::operator -- (int);
\fn QxtLinkedTreeIterator &  QxtLinkedTreeIterator::operator -= ( int j );

\fn bool QxtLinkedTreeIterator::operator== ( const iterator & other ) const;
compares
\fn bool QxtLinkedTreeIterator::operator!= ( const iterator & other ) const;
compares

\fn QxtLinkedTreeIterator QxtLinkedTreeIterator::erase  () const;
deletes the current item. returns an iterator to the next sibling. \n this instance is then invalid.
\fn QxtLinkedTreeIterator QxtLinkedTreeIterator::append (const T & value ) const;
appens an item to the children of this item. returns an iterator to the new item.





private:
    QxtSharedPrivate< QxtLinkedTreeItem<T> >  qxt_d;
};








*/









