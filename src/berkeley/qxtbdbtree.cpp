/****************************************************************************
 **
 ** Copyright (C) Qxt Foundation. Some rights reserved.
 **
 ** This file is part of the QxtBerkeley module of the Qxt library.
 **
 ** This library is free software; you can redistribute it and/or modify it
 ** under the terms of the Common Public License, version 1.0, as published
 ** by IBM, and/or under the terms of the GNU Lesser General Public License,
 ** version 2.1, as published by the Free Software Foundation.
 **
 ** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
 ** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 ** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
 ** FITNESS FOR A PARTICULAR PURPOSE.
 **
 ** You should have received a copy of the CPL and the LGPL along with this
 ** file. See the LICENSE file and the cpl1.0.txt/lgpl-2.1.txt files
 ** included with the source distribution for more information.
 ** If you did not receive a copy of the licenses, contact the Qxt Foundation.
 **
 ** <http://libqxt.org>  <foundation@libqxt.org>
 **
 ****************************************************************************/
#include "qxtbdbtree.h"





/*!
    \class QxtBdbTree QxtBdbTree
    \inmodule QxtBerkeley
    \brief template berkeley container for tree structured data

    the template argument must be registered with the qt meta system.
    You may not touch the file while a QxtBdbTree instance is running on it.

    examples usage:
    \code
    QxtBdbTree<QString> db("test.db");
    db.root().append("fooooo").append("bla");
    db.dumpTree(); //try this if you are unsure, how the data will look like
    \endcode



    There is an extensive example in /examples/berkeley/xmlstorage


    All functions of this class are thread safe.
    Calling open() multiple times is undefined.
    An Iterator may only be used from one thread at once, but you can have multiple iterators.



    \todo {implicitshared}
    \sa QxtBdbTreeIterator
*/
/*!


\fn QxtBdbTree<T>::QxtBdbTree()
Constructs an invalid QxtBdbTree


\fn QxtBdbTree<T>::QxtBdbTree (QString file)
Constructs a QxtBdbTree, and opens the file specified as its database.


\fn bool QxtBdbTree<T>::open  (QString file)
opens the specified file.

returns true on success and false on failure.
\bold {Note:} a sanity check is performed before opening the file.

\fn void QxtBdbTree<T>::clear()
Erase all records. This does not delete the unerlieing file.


\fn bool QxtBdbTree<T>::flush()
flushes the unerlieing DB file. all changes are synced to disk.


\fn QxtBdbTreeIterator<T> QxtBdbTree<T>::root() const
returns the rootnode

which is, similar to QAbstractItemModel, invalid and has no data itself.

\fn void QxtBdbTree<T>::dumpTree() const
outputs the contents of the database as flat file, and as iterateable tree onto qDebug().
This function assumes, the class used for Template initialisation implements the QDebug<< operator

*/



/*!
    \class QxtBdbTreeIterator QxtBdbtree
    \inmodule QxtBerkeley
    \brief tree iterator on QxtBdbtree


    \todo {implicitshared}
    \sa QxtBdbTree

*/

/*!
\fn QxtBdbTreeIterator<T>::QxtBdbTreeIterator()
constructs an invalid QxtBdbTreeIterator

It's an error to use this to iterate, access data, etc..

\fn QxtBdbTreeIterator<T>::~QxtBdbTreeIterator()
destructs the iterator.

The underlying cursors will be closed.


\fn QxtBdbTreeIterator<T>::QxtBdbTreeIterator(const QxtBdbTreeIterator<T> & other)
copies the iterator.

The underlying cursor is duped, meaning the position will be copied, but the copy can be used independently

\fn QxtBdbTreeIterator<T> & QxtBdbTreeIterator<T>::operator= ( const QxtBdbTreeIterator<T> & other )
copies the iterator.

The underlying cursor is duped, meaning the position will be copied, but the copy can be used independently


\fn bool QxtBdbTreeIterator<T>::isValid() const
return true if the iterato seems to point to a valid location.

calls to value() might fail anyway (but not crash), in case of concurrent access.
If you want to be 100% sure value() will return valid data, while using multiple threads, then you have to track changes yourself.

\fn QxtBdbTreeIterator<T>::operator T() const
\sa value()

\fn T QxtBdbTreeIterator<T>::value()
returns the value, the iterator is currently pointing to.
It is an error to call value() when isValid() returns false.
In case an database error ocures,like the item been deleted, value() will return a default constructed T

\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::parent   () const
returns the parent of this item, or an invalid QxtBdbTreeIterator if this is the root item.

\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::next     () const
returns the next sibling of this item, or an invalid QxtBdbTreeIterator if this is the last one.


\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::previous () const
returns the previous sibling of this item, or an invalid QxtBdbTreeIterator if this is the last one.


\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::child    () const
returns the first child of this item, or an invalid QxtBdbTreeIterator if there are none.


\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::operator + ( int j ) const
returns an iterator, \a j items next to this one.
if there is no such item, the returned iterator is invalid
\sa next()

\fn QxtBdbTreeIterator<T> &  QxtBdbTreeIterator<T>::operator ++ ()
this prefix operator increments the item by one.
if there are no more items, the iterator becomes invalid.

\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::operator ++ (int)
this postfix operator makes a copy of the item, then increments itself and returns the copy.
if there are no more items, the iterator becomes invalid.

\fn QxtBdbTreeIterator<T> &  QxtBdbTreeIterator<T>::operator += ( int j )
increments the item by \a
if there are no more items, the iterator becomes invalid.

\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::operator - ( int j ) const
returns an iterator, \a j previous next to this one.
if there is no such item, the returnediterator is invalid
\sa previous()

\fn QxtBdbTreeIterator<T> &  QxtBdbTreeIterator<T>::operator -- ()
this prefix operator decrements the item by one.
if there are no more items, the iterator becomes invalid.

\fn QxtBdbTreeIterator<T>    QxtBdbTreeIterator<T>::operator -- (int)
this postfix operator makes a copy of the item, then decrements itself and returns the copy.
if there are no more items, the iterator becomes invalid.

\fn QxtBdbTreeIterator<T> &  QxtBdbTreeIterator<T>::operator -= ( int j )
decrements the item by \a
if there are no more items, the iterator becomes invalid.

\fn QxtBdbTreeIterator<T>   QxtBdbTreeIterator<T>::append (const T & t )
appends an item to the children of this one, and returns an iterator to it.
if insertion fails, an invalid iterator is returned.
*/


