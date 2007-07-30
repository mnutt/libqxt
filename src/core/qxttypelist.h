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
** <http://libqxt.sourceforge.net>  <libqxt@gmail.com>
**
****************************************************************************/
#ifndef QXTTYPELIST_H
#define QXTTYPELIST_H
#include <qxtnull.h>

namespace QxtType {
struct NoExtend {
    typedef QxtNull head;
    enum { length = 0, extends = false };
};

template <typename T1 = QxtNull, typename T2 = QxtNull, typename T3 = QxtNull, typename T4 = QxtNull, typename T5 = QxtNull,
          typename T6 = QxtNull, typename T7 = QxtNull, typename T8 = QxtNull, typename T9 = QxtNull, typename EXTEND = QxtType::NoExtend>
struct QxtTypeList;

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename EXTEND>
struct QxtTypeList {
    typedef T1 head;
    typedef QxtTypeList<T2, T3, T4, T5, T6, T7, T8, T9, NoExtend, EXTEND> tail;
    typedef EXTEND extend;
    enum { length = tail::length + 1, extends = EXTEND::extends };
};

template<typename EXTEND>
struct QxtTypeList<NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, EXTEND> {
    typedef typename EXTEND::head head;
    typedef typename EXTEND::tail tail;
    typedef EXTEND extend;
    enum { length = EXTEND::length, extends = EXTEND::extends };
};

template<>
struct QxtTypeList<NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, NoExtend, QxtType::NoExtend> {
    typedef QxtNull extend;
    enum { length = 0, extends = false };
};
}

#ifndef QXT_NO_USING
using QxtType::QxtTypeList;
#endif

#endif
