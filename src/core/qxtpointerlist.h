
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
/**
\class QxtPointerList QxtPointerList

\ingroup QxtCore

\brief a list of pointers to QObjects, that cleans itself


when you add a QObject* to this list, it will be removed from the list when the QObject is deleted.

\sa QPointer

*/



#include <QList>
#include <QObject>

class QxtPointerListDeleter : public QObject
{
    Q_OBJECT
    protected:
        virtual void removeThisObject(QObject * obj)=0;
private slots:
    void removeSender()
    {
        removeThisObject(QObject::sender());
    }
};


template<class T>
class QxtPointerList : public QxtPointerListDeleter, public QList<T*>
{
public:
    ///constructs a new QxtPointerList
    QxtPointerList ():QList<T*>()
    {
    }
    ///destructs the QxtPointerList
    ~QxtPointerList()
    {
        QList<T*>::clear();
    }
    ///\reimp
    QxtPointerList ( const QxtPointerList<T> & other ):QxtPointerListDeleter(),QList<T*>(other)
    {
        foreach(T*t,other)
        {
            QObject::connect(t,SIGNAL(destroyed( QObject * obj )),this,SLOT(removeSender()));
        }
    }
    ///\reimp
    void append ( const T* & value )
    {
        QObject::connect(value,SIGNAL(destroyed( QObject * obj )),this,SLOT(removeSender()));
        QList<T*>::append(value);
    }
    ///\reimp
    void insert ( int i, const T & value )
    {
        QObject::connect(value,SIGNAL(destroyed( QObject * obj )),this,SLOT(removeSender()));
        QList<T*>::insert(i,value);
    }
    ///\reimp
    typename QList<T*>::iterator insert ( typename QList<T*>::iterator before, const T & value )
    {
        QObject::connect(value,SIGNAL(destroyed( QObject * obj )),this,SLOT(removeSender()));
        return QList<T*>::insert(before,value);
    }
    ///\reimp
    QxtPointerList<T> operator+ ( const QxtPointerList<T> & other ) const
    {
        QxtPointerList<T> m=*this;
        m+=other;
        return m;
    }
    ///\reimp
    QxtPointerList<T> & operator+= ( const QxtPointerList<T> & other )
    {
        foreach(T*t,other)
        {
            *this<<t;
        }
        return *this;
    }
    ///\reimp
    QxtPointerList<T> & operator+= ( const T* & value )
    {
        QObject::connect(value,SIGNAL(destroyed( QObject * obj )),this,SLOT(removeSender()));
        QList<T*>::operator+=(value);
        return *this;
    }
    ///\reimp
    QxtPointerList<T> & operator<< ( const QxtPointerList<T> & other )
    {
        *this+=other;
        return *this;
    }
    ///\reimp
    QxtPointerList<T> & operator<< ( const T* & value )
    {
        *this+=value;
        return *this;
    }
    ///\reimp
    QxtPointerList<T> & operator= ( const QxtPointerList<T> & other )
    {
        QList<T*>::clear();
        foreach(T*t,other)
        {
            *this<<t;
        }
        return *this;
    }

protected:
    ///\priv
    virtual void removeThisObject(QObject * obj)
    {
        removeAll(static_cast<T*>(obj));
    }
};



