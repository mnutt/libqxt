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

#ifndef QXTTUPLE_H
#define QXTTUPLE_H
#include <qxttypelist.h>

namespace QxtType
{

template<typename QXT_TYPELIST, int QXT_INDEX, int QXT_STEP=0, bool QXT_END=(QXT_INDEX==QXT_STEP), bool QXT_ERROR=(QXT_TYPELIST::length==0)>
struct get
    {
        typedef typename get<typename QXT_TYPELIST::tail, QXT_INDEX, QXT_STEP+1>::type type;
    };

template<typename QXT_TYPELIST, int QXT_INDEX, int QXT_STEP>
struct get<QXT_TYPELIST, QXT_INDEX, QXT_STEP, false, true>
    {}; // does not define type

template<typename QXT_TYPELIST, int QXT_INDEX, int QXT_STEP, bool QXT_ERROR>
struct get<QXT_TYPELIST, QXT_INDEX, QXT_STEP, true, QXT_ERROR>
    {
        typedef typename QXT_TYPELIST::head type;
    };

template<typename QXT_TYPELIST, bool QXT_LONG=false> class QxtTuple;
template<typename QXT_TYPELIST, int QXT_INDEX, bool QXT_LONG, bool EXT=(QXT_INDEX>8)> struct QxtTupleValue;

template<typename QXT_TYPELIST, int QXT_INDEX> struct QxtTupleValue<QXT_TYPELIST, QXT_INDEX, true, true>
{
    static typename get<QXT_TYPELIST, QXT_INDEX>::type value(QxtTuple<QXT_TYPELIST,true>* t)
    {
        return QxtTupleValue<typename QXT_TYPELIST::extend, QXT_INDEX-9, QXT_TYPELIST::extend::extends>::value(&t->extend);
    }

    static void setValue(QxtTuple<QXT_TYPELIST,true>* t, typename get<QXT_TYPELIST, QXT_INDEX>::type val)
    {
        QxtTupleValue<typename QXT_TYPELIST::extend, QXT_INDEX-9, QXT_TYPELIST::extend::extends>::setValue(&t->extend, val);
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 0, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 0>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t1;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 0>::type val)
    {
        t->t1 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 1, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 1>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t2;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 1>::type val)
    {
        t->t2 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 2, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 2>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t3;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 2>::type val)
    {
        t->t3 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 3, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 3>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t4;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 3>::type val)
    {
        t->t4 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 4, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 4>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t5;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 4>::type val)
    {
        t->t5 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 5, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 5>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t6;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 5>::type val)
    {
        t->t6 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 6, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 6>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t7;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 6>::type val)
    {
        t->t7 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 7, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 7>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t8;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 7>::type val)
    {
        t->t8 = val;
    }
};

template<typename QXT_TYPELIST, bool QXT_LONG> struct QxtTupleValue<QXT_TYPELIST, 8, QXT_LONG, false>
{
    static typename get<QXT_TYPELIST, 8>::type value(QxtTuple<QXT_TYPELIST,QXT_LONG>* t)
    {
        return t->t9;
    }
    static void setValue(QxtTuple<QXT_TYPELIST,QXT_LONG>* t, typename get<QXT_TYPELIST, 8>::type val)
    {
        t->t9 = val;
    }
};

//-----------------------------------------------------------------------------------------------

template<typename QXT_TYPELIST>
/**
\class QxtTuple QxtTuple

\ingroup QxtCore

\brief Arbitrary-length templated list

Tuples and cons pairs are both pretty common template metaprogramming hacks. This set of classes
attempts to implement a healthy balance between the two. Tuples generally are implemented with a
fixed length; cons pairs have a lot of overhead and require a ton of typing. As with all template
metaprograms, it may take a while to compile.

It is recommended to use the convenience macros to create tuples, but you can construct the
QxtTypeList template yourself if you desire; this may be preferable if you want to write generic
functions that use tuples.

----- example:
\code
#include <QxtTuple.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    Qxt7Tuple(bool, char, short, int, long long, float, double) tuple;

    tuple.setValue<0>(true);
    tuple.setValue<1>('a');
    tuple.setValue<2>(32767);
    tuple.setValue<3>(1234567);
    tuple.setValue<4>(987654321);
    tuple.setValue<5>(1.414);
    tuple.setValue<6>(3.14159265);

    cout << 0 << "=" << tuple.value<0>() << endl;
    cout << 1 << "=" << tuple.value<1>() << endl;
    cout << 2 << "=" << tuple.value<2>() << endl;
    cout << 3 << "=" << tuple.value<3>() << endl;
    cout << 4 << "=" << tuple.value<4>() << endl;
    cout << 5 << "=" << tuple.value<5>() << endl;
    cout << 6 << "=" << tuple.value<6>() << endl;
}
\endcode
*/

class QxtTuple<QXT_TYPELIST,false>
{
public:
    template<int QXT_INDEX> typename get<QXT_TYPELIST, QXT_INDEX>::type value()
    {
        return QxtTupleValue<QXT_TYPELIST, QXT_INDEX, false>::value(this);
    }
    template<int QXT_INDEX> void setValue(typename get<QXT_TYPELIST, QXT_INDEX>::type val)
    {
        QxtTupleValue<QXT_TYPELIST, QXT_INDEX, false>::setValue(this, val);
    }
    bool operator<(const QxtTuple<QXT_TYPELIST,false>& other)
    {
        if (t1 < other.t1) return true;
        if (t2 < other.t2) return true;
        if (t3 < other.t3) return true;
        if (t4 < other.t4) return true;
        if (t5 < other.t5) return true;
        if (t6 < other.t6) return true;
        if (t7 < other.t7) return true;
        if (t8 < other.t8) return true;
        if (t9 < other.t9) return true;
        return false;
    }
    bool operator==(const QxtTuple<QXT_TYPELIST,false>& other)
    {
        if (t1 != other.t1) return false;
        if (t2 != other.t2) return false;
        if (t3 != other.t3) return false;
        if (t4 != other.t4) return false;
        if (t5 != other.t5) return false;
        if (t6 != other.t6) return false;
        if (t7 != other.t7) return false;
        if (t8 != other.t8) return false;
        if (t9 != other.t9) return false;
        return true;
    }
    bool operator>=(const QxtTuple<QXT_TYPELIST,false>& other)
    {
        return !(*this < other);
    }
    bool operator<=(const QxtTuple<QXT_TYPELIST,false>& other)
    {
        if (t1 <= other.t1) return true;
        if (t2 <= other.t2) return true;
        if (t3 <= other.t3) return true;
        if (t4 <= other.t4) return true;
        if (t5 <= other.t5) return true;
        if (t6 <= other.t6) return true;
        if (t7 <= other.t7) return true;
        if (t8 <= other.t8) return true;
        if (t9 <= other.t9) return true;
        return false;
    }
    bool operator>(const QxtTuple<QXT_TYPELIST,false>& other)
    {
        return !(*this <= other);
    }
    bool operator!=(const QxtTuple<QXT_TYPELIST,false>& other)
    {
        return !(*this == other);
    }


// if only we could get away with making these protected
    typename get<QXT_TYPELIST, 0>::type t1;
    typename get<QXT_TYPELIST, 1>::type t2;
    typename get<QXT_TYPELIST, 2>::type t3;
    typename get<QXT_TYPELIST, 3>::type t4;
    typename get<QXT_TYPELIST, 4>::type t5;
    typename get<QXT_TYPELIST, 5>::type t6;
    typename get<QXT_TYPELIST, 6>::type t7;
    typename get<QXT_TYPELIST, 7>::type t8;
    typename get<QXT_TYPELIST, 8>::type t9;
};

//-----------------------------------------------------------------------------------------------

template<typename QXT_TYPELIST>
class QxtTuple<QXT_TYPELIST,true>
{
public:
    template<int QXT_INDEX> typename get<QXT_TYPELIST, QXT_INDEX>::type value()
    {
        return QxtTupleValue<QXT_TYPELIST, QXT_INDEX, true>::value(this);
    }
    template<int QXT_INDEX> void setValue(typename get<QXT_TYPELIST, QXT_INDEX>::type val)
    {
        QxtTupleValue<QXT_TYPELIST, QXT_INDEX, true>::setValue(this, val);
    }
    bool operator<(const QxtTuple<QXT_TYPELIST,true>& other)
    {
        if (t1 < other.t1) return true;
        if (t2 < other.t2) return true;
        if (t3 < other.t3) return true;
        if (t4 < other.t4) return true;
        if (t5 < other.t5) return true;
        if (t6 < other.t6) return true;
        if (t7 < other.t7) return true;
        if (t8 < other.t8) return true;
        if (t9 < other.t9) return true;
        if (extend < other.extend) return true;
        return false;
    }
    bool operator==(const QxtTuple<QXT_TYPELIST,true>& other)
    {
        if (t1 != other.t1) return false;
        if (t2 != other.t2) return false;
        if (t3 != other.t3) return false;
        if (t4 != other.t4) return false;
        if (t5 != other.t5) return false;
        if (t6 != other.t6) return false;
        if (t7 != other.t7) return false;
        if (t8 != other.t8) return false;
        if (t9 != other.t9) return false;
        if (extend != other.extend) return false;
        return true;
    }
    bool operator>=(const QxtTuple<QXT_TYPELIST,true>& other)
    {
        return !(*this < other);
    }
    bool operator<=(const QxtTuple<QXT_TYPELIST,true>& other)
    {
        if (t1 <= other.t1) return true;
        if (t2 <= other.t2) return true;
        if (t3 <= other.t3) return true;
        if (t4 <= other.t4) return true;
        if (t5 <= other.t5) return true;
        if (t6 <= other.t6) return true;
        if (t7 <= other.t7) return true;
        if (t8 <= other.t8) return true;
        if (t9 <= other.t9) return true;
        if (extend <= other.extend) return true;
        return false;
    }
    bool operator>(const QxtTuple<QXT_TYPELIST,true>& other)
    {
        return !(*this <= other);
    }
    bool operator!=(const QxtTuple<QXT_TYPELIST,true>& other)
    {
        return !(*this == other);
    }

// if only we could get away with making these protected
    typename get<QXT_TYPELIST, 0>::type t1;
    typename get<QXT_TYPELIST, 1>::type t2;
    typename get<QXT_TYPELIST, 2>::type t3;
    typename get<QXT_TYPELIST, 3>::type t4;
    typename get<QXT_TYPELIST, 4>::type t5;
    typename get<QXT_TYPELIST, 5>::type t6;
    typename get<QXT_TYPELIST, 6>::type t7;
    typename get<QXT_TYPELIST, 7>::type t8;
    typename get<QXT_TYPELIST, 8>::type t9;
    QxtTuple<typename QXT_TYPELIST::extend> extend;
};

}

#ifndef QXT_NO_USING
using QxtType::QxtTuple;
#endif

#ifndef QXT_NO_MACROS
/*! \relates QxtTuple
 * Declares a one-column tuple.
 */
#define Qxt1Tuple(a) QxtTuple<QxtTypeList<a > >

/*! \relates QxtTuple
 * Declares a two-column tuple, similar to QPair.
 */
#define Qxt2Tuple(a, b) QxtTuple<QxtTypeList<a, b > >

/*! \relates QxtTuple
 * Declares a three-column tuple, similar to QxtTriple.
 */
#define Qxt3Tuple(a, b, c) QxtTuple<QxtTypeList<a, b, c > >

/*! \relates QxtTuple
 * Declares a four-column tuple.
 */
#define Qxt4Tuple(a, b, c, d) QxtTuple<QxtTypeList<a, b, c, d > >

/*! \relates QxtTuple
 * Declares a five-column tuple.
 */
#define Qxt5Tuple(a, b, c, d, e) QxtTuple<QxtTypeList<a, b, c, d, e > >

/*! \relates QxtTuple
 * Declares a six-column tuple.
 */
#define Qxt6Tuple(a, b, c, d, e, f) QxtTuple<QxtTypeList<a, b, c, d, e, f > >

/*! \relates QxtTuple
 * Declares a seven-column tuple.
 */
#define Qxt7Tuple(a, b, c, d, e, f, g) QxtTuple<QxtTypeList<a, b, c, d, e, f, g > >

/*! \relates QxtTuple
 * Declares an eight-column tuple.
 */
#define Qxt8Tuple(a, b, c, d, e, f, g, h) QxtTuple<QxtTypeList<a, b, c, d, e, f, g, h > >

/*! \relates QxtTuple
 * Declares a nine-column tuple.
 */
#define Qxt9Tuple(a, b, c, d, e, f, g, h, i) QxtTuple<QxtTypeList<a, b, c, d, e, f, g, h, i > >

/*! \relates QxtTuple
 * Declares an extended tuple with ten or more columns. Pay special attention to the syntax of the tenth parameter, which
 * must be a QxtTypeList, not a storage type.
\code
QxtLongTuple(int, int, int, int, int, int, int, int, int, Qxt1TypeList(int)) tuple; // correct way to implement a 10-tuple
QxtLongTuple(int, int, int, int, int, int, int, int, int, int) tuple;              // this will produce a (very long) compile-time error
\endcode
 */
#define QxtLongTuple(a, b, c, d, e, f, g, h, i, extend) QxtTuple<QxtTypeList<a, b, c, d, e, f, g, h, i, extend >, true >

#endif

#endif
