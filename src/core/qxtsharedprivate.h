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
\class QxtSharedPrivate QxtSharedPrivate
\ingroup QxtCore
\brief base class for shared data objects using the pimpl idom


combines both, the functionality of QxtPimpl and QSharedData \n
It is assumed you are familiar with QxtPimpl and QSharedData/QSharedDataPointer. If not, please read their documentation before this one. \n


<h4>Major differences to QxtPimpl are:</h4>
    - there is no qxt_p() since there are multiple public classes sharing the same private
    - you have to explicitly create the private in the ctor of your public class using new 
    - The private Data must not be a QxtPrivate  but a QxtSharedPrivate subclass

<h4>Major differences to QSharedData / QSharedDataPointer are:</h4>
    - the actual Data can be a private implementation 
    - instead of QSharedDataPointer<MyData> d; you use QXT_DECLARE_SHARED_PRIVATE(MyData)  and access it via qxt_d().member instead of d->member 
    - The private Data must not be a QSharedData  but a QxtSharedPrivate subclass


<h4>example</h4>
expanding the example from the QSharedDataPointer we get this:
\code
 #ifndef EMPLOYEE_H
 #define EMPLOYEE_H

 #include <QxtSharedPrivate>
 #include <QString>

 class EmployeePrivate;
 class Employee
 {
 public:
     Employee();
     Employee(int id, const QString &name);

     void setId(int id) { d->id = id; }
     void setName(const QString &name);

     int id() const { return d->id; }
     QString name() const;

 private:
     QXT_DECLARE_SHARED_PRIVATE(Employee);
 };


 class EmployeePrivate : public QxtSharedPrivate<Employee>
 {
 public:
     EmployeePrivate();
     EmployeePrivate(const EmployeePrivate &other);
     ~EmployeePrivate();

     int id;
     QString *name;
 };

 #endif

\endcode


note that contrary to QxtPimpl you need to initialise your private data

\code
 Employee::Employee()
 {
     qxt_d = new EmployeePrivate;
 }
\endcode

if you ever really want to define a copy constructor for your public class, remember you must not reinitialise qxt_d as this would defeat the whole point of shared data.  instead just copy it. The underliing QSharedDataPointer will take care of the rest.

\code
 Employee::Employee(const Employee & other)
 {
     qxt_d = other.qxt_d;
 }
\endcode

Also remember you must not delete the private data yourself at any time.
*/

#ifndef QXTSHAREDPRIVATE_H_HEADER_GUARD
#define QXTSHAREDPRIVATE_H_HEADER_GUARD

#include <QSharedData>
#include <QSharedDataPointer>

/*! \relates QxtSharedPrivate
 * Declares that a public class has a related private class.
 *
 * This shuold be put in the private section of the public class. The parameter is the name of the public class.
 */
#define QXT_DECLARE_SHARED_PRIVATE(PUB) QxtSharedPrivateInterface<PUB , PUB##Private > qxt_d;



template <typename PUB>
class QxtSharedPrivateReverseFactory;


template <typename PUB>
class QxtSharedPrivate
{
public:
    QxtSharedPrivate();
    virtual ~QxtSharedPrivate()
    {
    }

/*friend class needs the PVT template. fsck*/
public: 
    QxtSharedPrivateReverseFactory<PUB>* mm_factory_keep_your_hands_of_that;
};

#ifndef QXT_DOXYGEN_RUN

/**
ok this is absolutly wicked. 
we have some kind of dtor delegation here. means QxtSharedPrivateReverseFactory is just there for 
"delegating the destruction" since we want to hide our real dtor from the public interface.
so basic concept: QxtSharedPrivate constructs, QxtSharedPrivateReverseFactory deletes
they are both coupled.
*/

template <typename PUB>
class QxtSharedPrivateReverseFactory : public QSharedData
{
public:
    QxtSharedPrivateReverseFactory(QxtSharedPrivate<PUB>* a):QSharedData()
    {
        pvt = a;
    }
    QxtSharedPrivateReverseFactory(const QxtSharedPrivateReverseFactory &other):QSharedData(other)
    {
        pvt=other.pvt;
    }
    ~QxtSharedPrivateReverseFactory()
    {
        delete pvt;
    }

     QxtSharedPrivate<PUB> * pvt;
};


template <typename PUB>
QxtSharedPrivate<PUB>::QxtSharedPrivate()
{
    mm_factory_keep_your_hands_of_that=new QxtSharedPrivateReverseFactory<PUB>(this);
}



template <typename PUB, typename PVT>
class QxtSharedPrivateInterface 
{
public:
    QxtSharedPrivateInterface()
    {
        pvt=0;
    }
    QxtSharedPrivateInterface(const QxtSharedPrivateInterface &other)
    {
        pvt=other.pvt;
    }
    inline QxtSharedPrivateInterface& operator=( const QxtSharedPrivateInterface & other)
    {
        pvt=other.pvt;
    }
    inline PVT& operator=( PVT * n)
    {
        Q_ASSERT(pvt==0);
        pvt=n->mm_factory_keep_your_hands_of_that;

        Q_ASSERT(dynamic_cast<PVT*>(pvt->pvt)>0);
        return * static_cast <PVT*>(pvt->pvt);
    }
    inline PVT& operator()()
    {
        Q_ASSERT(dynamic_cast<PVT*>(pvt->pvt)>0);
        return * static_cast <PVT*>(pvt->pvt);
    }
    inline const PVT& operator()() const
    {
        Q_ASSERT(dynamic_cast<const PVT*>(pvt->pvt)>0);
        return * static_cast <const PVT*>(pvt->pvt);
    }
private:
    QSharedDataPointer<QxtSharedPrivateReverseFactory<PUB> > pvt;
};

#endif

#endif
