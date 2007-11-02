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
    - no qxt_p()  since there is not only one single public class 
    - you have to explicitly create the private in the ctor of your public class using new 
    - The private Data must not be a QxtPrivate subclass 

<h4>Major differences to QSharedData / QSharedDataPointer are:</h4>
    - the actual Data can be a private implementation 
    - instead of QSharedDataPointer<MyData> d; you use QXT_DECLARE_SHARED_PRIVATE(MyData)  and access it via qxt_d().member instead of d->member 
    - The private Data must not be a QSharedData subclass 


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


 class EmployeePrivate : public QSharedData
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
#define QXT_DECLARE_SHARED_PRIVATE(PUB) QxtSharedPrivateInterface<PUB##Private> qxt_d;


#ifndef QXT_DOXYGEN_RUN

template <typename PVT>
class QxtSharedPrivateInterfaceData : public QSharedData
{
public:
    QxtSharedPrivateInterfaceData():QSharedData()
    {
        pvt = new PVT;
    }
    QxtSharedPrivateInterfaceData(const QxtSharedPrivateInterfaceData &other):QSharedData(other)
    {
        pvt=other.pvt;
    }
    ~QxtSharedPrivateInterfaceData()
    {
        delete pvt;
    }

    PVT *  pvt;
};


template <typename PVT>
class QxtSharedPrivateInterface 
{
public:
    QxtSharedPrivateInterface()
    {
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
        pvt->pvt=n;
        return *pvt->pvt;
    }
    inline PVT& operator()()
    {
        return *pvt->pvt;
    }
    inline const PVT& operator()() const
    {
        return *pvt->pvt;
    }
private:
    QSharedDataPointer<QxtSharedPrivateInterfaceData<PVT > > pvt;
};

#endif

#endif
