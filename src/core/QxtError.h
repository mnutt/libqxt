/*******************************************************************
Qt extended Library 
Copyright (C) 2006 Arvid Picciani
released under the Terms of LGPL (see the LICENSE file)
*******************************************************************/

#ifndef QXTERROR_H
#define QXTERROR_H

#include <Qxt/qxtglobal.h>
#include <Qxt/qxtnamespace.h>

/**
\class QxtError QxtError

\ingroup core

\brief Information about Errors ocuring inside Qxt

might add more features in future.
*/

/*! \relates QxtError
droping an error inside a function that returns QxtError


short for return  QxtError(__FILE__,__LINE__,x);
*/
#define QXT_DROP(x) return QxtError(__FILE__,__LINE__,x);


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
#define QXT_DROP_F(call) {QxtError error_sds = call; if (error_sds != Qxt::NoError )return error_sds; }

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
    QxtError(char * file, long line, Qxt::ErrorCode errorcode);
    Qxt::ErrorCode errorCode() const;
    long line() const;
    char * file() const;
    operator Qxt::ErrorCode();

private:
    Qxt::ErrorCode errorcode_m;
    long line_m;
    char * file_m;
};

#endif
