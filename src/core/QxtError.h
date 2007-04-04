/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/

#ifndef QXTERROR_H
#define QXTERROR_H

#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

/**
\class QxtError QxtError

\ingroup core

\brief Information about Errors ocuring inside Qxt

*/

/*! \relates QxtError
droping an error inside a function that returns QxtError


short for return  QxtError(__FILE__,__LINE__,x);
*/
#define QXT_DROP(x) return QxtError(__FILE__,__LINE__,x);


/*! \relates QxtError
droping an error inside a function that returns QxtError

aditionaly specifies an errorstring \n

short for return  QxtError(__FILE__,__LINE__,x,s);
*/
#define QXT_DROP_S(x,s) return QxtError(__FILE__,__LINE__,x,s);


/*! \relates QxtError
droping no error inside a function that returns QxtError

short for return QxtError(__FILE__,__LINE__,Qxt::NoError);
*/
#define QXT_DROP_OK return QxtError(__FILE__,__LINE__,Qxt::NoError);


/*! \relates QxtError
forward a drop


drops from this function if the call inside dropped too.
the inner function must return or be a QxtError.

example
\code
QXT_DROP_F(critical_function());
\endcode

*/
#define QXT_DROP_F(call) {QxtError error_sds = call; if (error_sds != Qxt::NoError ) return error_sds; else (void)0; }

/*! \relates QxtError
check for errors

example
\code
QXT_DROP_SCOPE(error,critical_function())
	{
	qDebug()<<error;
	QXT_DROP_F(error);
	};
\endcode

short for  QxtError name = call; if (name != Qxt::NoError )

\warning: the errors name is valid outside the scope
*/
#define QXT_DROP_SCOPE(name,call) QxtError name = call; if (name != Qxt::NoError )


class QXT_CORE_EXPORT QxtError
{
public:
    QxtError(char * file, long line, Qxt::ErrorCode errorcode, char * errorString=0);
    Qxt::ErrorCode errorCode() const;
    long line() const;
    char * file() const;
    char * errorString() const;
    operator Qxt::ErrorCode();

private:
    Qxt::ErrorCode errorcode_m;
    long line_m;
    char * file_m;
    char * errorString_m;
};

#endif
